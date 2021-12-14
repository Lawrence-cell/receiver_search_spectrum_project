#include "function_1.h"
#include <sstream>
#include<iostream>
#include<fstream>
#include <Python.h>
#include <QDebug>

using namespace std;

/*************************************************************/
/***************************功能函数***************************/
/*************************************************************/
template<class T>
string arr_to_string_list(T* arr, int N) {
    string s = "[";
    for (int i = 0; i < N; ++i) {
        s += to_string(arr[i]);
        if (i != N - 1) s += ",";
    }
    s += "]";
    return s;
}

template<class T, class V = int>
void plot(T* x, int N1, int start, int end, V* y, bool equal) {
    PyRun_SimpleString("import matplotlib.pyplot as plt");
    PyRun_SimpleString("import numpy as np");
    if (equal) {
        PyRun_SimpleString("plt.axis(\"equal\")");
    }
    stringstream ss1;
    ss1 << start;
    string str1 = ss1.str();
    stringstream ss2;
    ss2 << end;
    string str2 = ss2.str();
    stringstream ss3;
    ss3 << N1;
    string str3 = ss3.str();

    string cmd = "plt.plot(";
    //cmd += ("np.linspace(" + str1 + "," + str2 + "," + str3 + "),");
    string s1 = arr_to_string_list(x, N1);
    if (y != NULL) {
        string s2 = arr_to_string_list(y, N1);
        cmd += (s1 + "," + s2 + ")");
        PyRun_SimpleString(cmd.c_str());
    }
    else {
        cmd += (s1 + ")");
        PyRun_SimpleString(cmd.c_str());
    }

    PyRun_SimpleString("plt.xlabel('Freq(MHz)')");
    PyRun_SimpleString("plt.ylabel('Psd')");
    PyRun_SimpleString("plt.show()");
}


void pythonInitial() {
    Py_Initialize(); //初始化Python环境
    string path = ".";
    string chdir_cmd = string("sys.path.append(\"") + path + "\")";
    const char* cstr_cmd = chdir_cmd.c_str();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(cstr_cmd);
}

//获取均值，用来做平滑
double GetMean(double* input, int Step, int Smooth) {
    double sum = 0;
    for (int mean = -(Step / 2); mean < Step / 2; mean++)
    {
        sum += input[mean];
    }
    sum = sum / Smooth;
    return sum;
}

//寻找序列最小值
double FindMin(double* input, int Step) {
    double min = input[0];
    for (int Count = 0; Count < Step; Count++)
    {
        if (input[Count] < min)
        {
            min = input[Count];
        }
    }
    return min;
}

void FFT(int* input, double* output, int fft_size) {
    fftw_complex* in, * out;
    fftw_plan p;
    int N = fft_size, i = 0, j = 0;
    short* data = (short*)input;
    int count;

    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
    for (i = 0; i < N; i++)
    {
        in[i][0] = data[i * 2];
        in[i][1] = data[i * 2 + 1];
    }
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p); /* repeat as needed*/
    fftw_destroy_plan(p);
    fftw_free(in);

    /*FFTShift*/
    for (j = int(N / 2); j < N; j++)
    {
        count = j - int(N / 2);
        output[count] = sqrt(out[j][0] * out[j][0] + out[j][1] * out[j][1]);
    }
    for (j = 0; j<int(N / 2); j++)
    {
        count = j + int(N / 2);
        output[count] = sqrt(out[j][0] * out[j][0] + out[j][1] * out[j][1]);
    }
    fftw_free(out);
}


//通过IP地址创建socket套接字
SOCKET CreatSocket(const char* IpAddr) {
    WSADATA wsaData;
    //WSAStartup(MAKEWORD(2, 2), &wsaData);
    WSAStartup(0x0202, &wsaData);

    SOCKET clntSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.S_un.S_addr = inet_addr(IpAddr);
    sockAddr.sin_port = htons(7);
    connect(clntSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    return clntSock;
}


void write_hang(double Tao[80000]) {
    ofstream ocout;
    ocout.open("Tao.txt");
    for (int i = 0; i < 80000; i++)
    {
        ocout << Tao[i];
        ocout << ',';
    }
    ocout.close();
}
//
void write_matrix(double FX[CYC][3]) {
    ofstream ocout;
    ocout.open("FX_log.txt");
    ocout << "TH4=0.06," << '\t' << "TH8=0.16;" << '\t' << "Th10=0.15;" << endl;
    for (int i = 0; i < CYC; i++)
    {
        ocout << FX[i][0] << ',\t' << '\t' << FX[i][1] << ',\t' << '\t' << FX[i][2] << ';' << endl;
    }
    ocout.close();
}

int Max_index(int A[], int up) {
    int max_temp = A[0];
    int index = 0;
    for (int i = 0; i < up; i++) {
        if (A[i] >= max_temp) {
            max_temp = A[i];
            index = i;
        }

    }
    return index;
}
int Peak_detect(double Tao[80000]) {
    double cut1[200];
    int num_detect = 0;
    for (int i = 0; i < 200; i++) {
        cut1[i] = Tao[i * 400 + 200];
    }
    for (int i = 0; i < 200; i++) {
        if (cut1[i] >= 0.05) {
            num_detect += 1;
        }
    }
    return num_detect;
}


/*************************************************************/
/***************************接口函数***************************/
/*************************************************************/

//同时设置增益和频点
void SetFreqAndGain(SOCKET clntSock, float Freq, int32_t Gain) {
    char str[28] = "set the freq & gain!FREQGAI";
    int* sendBuf = (int*)str;
    sendBuf[5] = int(Freq*10);
    sendBuf[6] = Gain;
    send(clntSock, (const char*)sendBuf, 28, NULL);
}

//设置频点
void SetRxFreq(SOCKET clntSock, float Freq) {
    char str[24] = "set the freq only  !FRE";
    int* sendBuf = (int*)str;
    sendBuf[5] = int(Freq * 10);
    send(clntSock, (const char*)sendBuf, 24, NULL);
}

//设置发送频点
void SetTxFreq(SOCKET clntSock, float Freq) {
    char str[24] = "set the txfreq only!FRE";
    int* sendBuf = (int*)str;
    sendBuf[5] = int(Freq * 10);
    send(clntSock, (const char*)sendBuf, 24, NULL);
}

//设置增益
void SetGain(SOCKET clntSock, int32_t Gain) {
    char str[24] = "set the gain only  !GAI";
    int* sendBuf = (int*)str;
    sendBuf[5] = Gain;
    send(clntSock, (const char*)sendBuf, 24, NULL);
}

//设置发送衰减
void SetAttenuation(SOCKET clntSock, int32_t Attenuation) {
    char str[24] = "set the tx attenuat!ATT";
    int* sendBuf = (int*)str;
    sendBuf[5] = Attenuation;
    send(clntSock, (const char*)sendBuf, 24, NULL);
}

//设置采样率
void SetSampleRate(SOCKET clntSock, int32_t SampleRate) {
    char str[24] = "set the sample rate!RAT";
    int* sendBuf = (int*)str;
    sendBuf[5] = SampleRate;
    send(clntSock, (const char*)sendBuf, 24, NULL);
}

//设置采样带宽
void SetSampleBand(SOCKET clntSock, int32_t SampleBand) {
    char str[24] = "set the signal band!BND";
    int* sendBuf = (int*)str;
    sendBuf[5] = SampleBand;
    send(clntSock, (const char*)sendBuf, 24, NULL);
}

//设置发送带宽
void SetTxBand(SOCKET clntSock, int32_t SampleBand) {
    char str[24] = "set the transv band!BND";
    int* sendBuf = (int*)str;
    sendBuf[5] = SampleBand;
    send(clntSock, (const char*)sendBuf, 24, NULL);
}


//按点数采集数据
void CaptureData(SOCKET clntSock, int32_t SampleNum, char* RxBuffer) {
    qDebug() << "first function" << endl;
    char str[24] = "capture data points!LEN";
    int* sendBuf = (int*)str;
    sendBuf[5] = SampleNum;
    send(clntSock, (const char*)sendBuf, 24, NULL);
    Sleep(500);

    int nRecvBuf = 2048 * 1024;//设置socket缓冲大小
    setsockopt(clntSock, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));

    int size = SampleNum * 4;
    int RecvSize;

    while (size > 0)
    {
        RecvSize = recv(clntSock, RxBuffer, size, 0);
        if (SOCKET_ERROR == RecvSize)
            qDebug() << "error" << endl;
        size = size - RecvSize;
        RxBuffer += RecvSize;
    }

    qDebug() << "first function over" << endl;
}

//按毫秒数采集信号，forLTE
void CaptureDataMs(SOCKET clntSock, int32_t Ms, char* RxBuffer) {
    char str[24] = "capture data ms    !LEN";
    int* sendBuf = (int*)str;
    sendBuf[5] = Ms;
    send(clntSock, (const char*)sendBuf, 24, NULL);
    Sleep(500);

    int nRecvBuf = 2048 * 1024;//设置socket缓冲大小
    setsockopt(clntSock, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));

    int size = Ms * 30720 * 4;
    int RecvSize;

    while (size > 0)
    {
        RecvSize = recv(clntSock, RxBuffer, size, 0);
        if (SOCKET_ERROR == RecvSize)
            cout << "recv error" << endl;
        size = size - RecvSize;
        RxBuffer += RecvSize;
    }
}

//控制SR发送信号
void SendSignel(SOCKET clntSock, int32_t SampleRate, int32_t SampleBand, float TxFreq, int32_t Attenuation, int32_t SignalType) {
    SetSampleRate(clntSock,SampleRate);
    Sleep(200);
    SetTxBand(clntSock,SampleBand);
    Sleep(200);
    SetTxFreq(clntSock,TxFreq);
    Sleep(200);
    SetAttenuation(clntSock,Attenuation);
    Sleep(200);
    SetGain(clntSock,  60);
    Sleep(200);

    char str[24] = "send signal        !TYP";
    int* sendBuf = (int*)str;
    sendBuf[5] = SignalType;
   /* while (1) {
        send(clntSock, (const char*)sendBuf, 24, NULL);
    }*/
    send(clntSock, (const char*)sendBuf, 24, NULL);
    //Sleep(500);
}
//保存采样数据
void DataSave(SOCKET clntSock, int32_t Begin, int32_t End, int PacketSize, double* RxBuffer, fftw_plan p, fftw_complex* in, fftw_complex* out) {

    //判断Begin和End的大小关系是否合法
    if (End > Begin) {
        cout << "SpectrumScan" << Begin << End << endl;
        SetSampleRate(clntSock, 30720000);
        Sleep(100);
        //设置一个等待时间，防止网口卡住
        SetSampleBand(clntSock, 20000000);
        Sleep(100);
        SetTxFreq(clntSock, 70);

        //计算需要采集多少次
        short CaptureTimes = ceil(float(End - Begin) / 20.0);
        float BeginFreq = Begin + 10;
        //计算带内有效点数，比如30.72MHz采样率，20MHz带宽，采集3072个点，实际只用中间2000个点
        int ValidLen = 2000 * PacketSize / 3072;
        int StartPoint = (PacketSize - ValidLen) / 2;

        int* SingelData = new int[PacketSize];
        double* SingelFFTRes = new double[PacketSize];
        int RxBufferStart = 0;
        int i, ii, jj, count;

        for (i = 0; i < CaptureTimes; i++) {
            Sleep(100);
            SetFreqAndGain(clntSock, BeginFreq, 30);//设置增益和频点
            Sleep(300);
            CaptureData(clntSock, PacketSize, (char*)SingelData);
            short* data = (short*)SingelData;

            for (ii = 0; ii < PacketSize; ii++)
            {
                in[ii][0] = data[ii * 2];
                in[ii][1] = data[ii * 2 + 1];
            }
            fftw_execute(p); /* repeat as needed*/

            BeginFreq += 20;
        }
        delete[] SingelData, SingelFFTRes;
    }
    else {
        cout << "Begin and End invalid" << endl;
    }
    return;
}
//扫频代码
void SpectrumScan(SOCKET clntSock, int32_t Begin, int32_t End, int PacketSize, double* RxBuffer, fftw_plan p, fftw_complex* in, fftw_complex* out) {

    //判断Begin和End的大小关系是否合法
    if (End > Begin) {
        cout << "SpectrumScan" << Begin << End << endl;
        SetSampleRate(clntSock, 30720000);
        Sleep(100);
        //设置一个等待时间，防止网口卡住
        SetSampleBand(clntSock, 20000000);
        Sleep(100);
        SetTxFreq(clntSock, 70);

        //计算需要采集多少次
        short CaptureTimes = ceil(float(End - Begin) / 20.0);
        float BeginFreq = Begin + 10;
        //计算带内有效点数，比如30.72MHz采样率，20MHz带宽，采集3072个点，实际只用中间2000个点
        int ValidLen = 2000 * PacketSize / 3072;
        int StartPoint = (PacketSize - ValidLen) / 2;

        int* SingelData = new int[PacketSize];
        double* SingelFFTRes = new double[PacketSize];
        int RxBufferStart = 0;
        int i, ii, jj, count;

        for (i = 0; i < CaptureTimes; i++) {
            Sleep(100);
            SetFreqAndGain(clntSock, BeginFreq, 30);//设置增益和频点
            Sleep(300);
            CaptureData(clntSock, PacketSize, (char*)SingelData);
            short* data = (short*)SingelData;

            for (ii = 0; ii < PacketSize; ii++)
            {
                in[ii][0] = data[ii * 2];
                in[ii][1] = data[ii * 2 + 1];
            }
            fftw_execute(p); /* repeat as needed*/

            //FFTShift
            for (jj = int(PacketSize / 2); jj < PacketSize; jj++)
            {
                count = jj - int(PacketSize / 2);
                SingelFFTRes[count] = sqrt(out[jj][0] * out[jj][0] + out[jj][1] * out[jj][1]);
            }
            for (jj = 0; jj<int(PacketSize / 2); jj++)
            {
                count = jj + int(PacketSize / 2);
                SingelFFTRes[count] = sqrt(out[jj][0] * out[jj][0] + out[jj][1] * out[jj][1]);
            }

            //求功率谱
            for (int j = 0; j < PacketSize; j++)
            {
                SingelFFTRes[j] = 10 * log10(SingelFFTRes[j]);
            }

            if ((int(End - Begin) % 20) != 0 && i == CaptureTimes - 1) {
                //当最后一次需要采集的数据不满20MHz带宽时，计算出实际需要的点数
                ValidLen = (int(End - BeginFreq + 10) % 20) * ValidLen / 20;
            }

            //将每次扫频采集的结果按顺序复制到最终返回的数组中，形成拼接效果
            memcpy(&RxBuffer[RxBufferStart], &SingelFFTRes[StartPoint], ValidLen * 8);
            RxBufferStart += ValidLen;

            BeginFreq += 20;
        }
        delete[] SingelData, SingelFFTRes;
    }
    else {
        cout << "Begin and End invalid" << endl;
    }
    return;
}

//单设备扫频
void SingleSpectrumScan(SOCKET clntSock, float Begin, float End, int PacketSize) {
    
    float CaptureTimes = (End - Begin) / 20.0;
    int CapturePoints = 2000 * CaptureTimes;
    
    double* RxBuffer = new double[CapturePoints];
    fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
    fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
    fftw_plan p = fftw_plan_dft_1d(PacketSize, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    SpectrumScan(clntSock, Begin, End, PacketSize, RxBuffer, p, in, out);

    fftw_destroy_plan(p);
    //fftw_free(in);
    fftw_free(out);

    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.argv = ['python.py']");
    plot(RxBuffer, CapturePoints, Begin, End);
    Py_Finalize();

    delete[] RxBuffer;
}


//多设备扫频衔接
void MultiDeviceScanCont(SOCKET clntSock_0, SOCKET clntSock_1, SOCKET clntSock_2, float Begin, float End, int PacketSize) {
    if (End > Begin) {

        //计算需要采集的次数
        float CaptureTimes = (End - Begin) / 20.0;
        short CaptureTimesInt = ceil(CaptureTimes);
        float CaptureTimesFra = CaptureTimesInt - CaptureTimes;
        short CaptureTimesSingle = CaptureTimesInt / 3;
        short CaptureTimesBonus = CaptureTimesInt % 3;
        short CaptureTimesDevice_1 = CaptureTimesSingle + ((CaptureTimesBonus > 0) ? 1 : 0);
        short CaptureTimesDevice_2 = CaptureTimesSingle + ((CaptureTimesBonus > 1) ? 1 : 0);
        short CaptureTimesDevice_3 = CaptureTimesSingle;

        float End_1 = Begin + 20 * CaptureTimesDevice_1;
        float End_2 = End_1 + 20 * CaptureTimesDevice_2;
        float End_3 = End_2 + 20 * CaptureTimesDevice_3;

        int ValidLen = 2000 * PacketSize / 3072;

        double* RxBuffer_1 = new double[ValidLen * CaptureTimesDevice_1];
        double* RxBuffer_2 = new double[ValidLen * CaptureTimesDevice_2];
        double* RxBuffer_3 = new double[ValidLen * CaptureTimesDevice_3];


        fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_plan p = fftw_plan_dft_1d(6144, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_complex* in1 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_complex* out1 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_plan p1 = fftw_plan_dft_1d(6144, in1, out1, FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_complex* in2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_complex* out2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_plan p2 = fftw_plan_dft_1d(6144, in2, out2, FFTW_FORWARD, FFTW_ESTIMATE);

        thread th1(SpectrumScan, clntSock_0, Begin, End_1, PacketSize, RxBuffer_1, p, in, out);
        thread th2(SpectrumScan, clntSock_1, End_1, End_2, PacketSize, RxBuffer_2, p1, in1, out1);
        thread th3(SpectrumScan, clntSock_2, End_2, End_3, PacketSize, RxBuffer_3, p2, in2, out2);

        th1.join();
        th2.join();
        th3.join();

        fftw_destroy_plan(p);
        fftw_free(in);
        fftw_free(out);
        fftw_destroy_plan(p1);
        fftw_free(in1);
        fftw_free(out1);
        fftw_destroy_plan(p2);
        fftw_free(in2);
        fftw_free(out2);

        double* RxBufferTotal = new double[ValidLen * CaptureTimes];

        memcpy(&RxBufferTotal[0], &RxBuffer_1[0], ValidLen * CaptureTimesDevice_1);
        memcpy(&RxBufferTotal[ValidLen * CaptureTimesDevice_1], &RxBuffer_2[0], ValidLen * CaptureTimesDevice_2);
        memcpy(&RxBufferTotal[ValidLen * CaptureTimesDevice_2], &RxBuffer_3[0], ValidLen * (CaptureTimes - CaptureTimesDevice_1 - CaptureTimesDevice_2));

        Py_Initialize();
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.argv = ['python.py']");
        plot(RxBufferTotal, ValidLen * CaptureTimes,Begin,End);
        Py_Finalize();

        delete[] RxBuffer_1, RxBuffer_2, RxBuffer_3, RxBufferTotal;

    }
    else {
        cout << "Begin and End value invalid" << endl;
    }
    return;
}

//多设备扫频融合
void MultiDeviceScanMix(SOCKET clntSock_0, SOCKET clntSock_1, SOCKET clntSock_2, float Begin, float End, int PacketSize) {
    if (End > Begin) {
        cout << "MultiDeviceScanMix" << "  Begin  " << Begin << "  End  " << End << endl;

        //计算需要采集的次数
        float CaptureTimes = float(End - Begin) / 20;
        short CaptureTimesInt = ceil(CaptureTimes);
        float CaptureTimesFra = CaptureTimesInt - CaptureTimes;

        int ValidLen = 2000 * PacketSize / 3072;
        int PointLen = ValidLen * CaptureTimes;

        double* RxBuffer_1 = new double[PointLen];
        double* RxBuffer_2 = new double[PointLen];
        double* RxBuffer_3 = new double[PointLen];
        double* RxBufferTotal = new double[PointLen];

        fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_plan p = fftw_plan_dft_1d(PacketSize, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_complex* in1 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_complex* out1 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_plan p1 = fftw_plan_dft_1d(PacketSize, in1, out1, FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_complex* in2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_complex* out2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_plan p2 = fftw_plan_dft_1d(PacketSize, in2, out2, FFTW_FORWARD, FFTW_ESTIMATE);

        thread th1(SpectrumScan, clntSock_0, Begin, End, PacketSize, RxBuffer_1, p, in, out);
        thread th2(SpectrumScan, clntSock_1, Begin, End, PacketSize, RxBuffer_2, p1, in1, out1);
        thread th3(SpectrumScan, clntSock_2, Begin, End, PacketSize, RxBuffer_3, p2, in2, out2);

        th1.join();
        th2.join();
        th3.join();

        fftw_destroy_plan(p);
        fftw_free(in);
        fftw_free(out);
        fftw_destroy_plan(p1);
        fftw_free(in1);
        fftw_free(out1);
        fftw_destroy_plan(p2);
        fftw_free(in2);
        fftw_free(out2);

        for (int i = 0; i < PointLen; i++)
        {
            RxBufferTotal[i] = (RxBuffer_1[i] + RxBuffer_2[i] + RxBuffer_3[i]) / 3;
        }

        Py_Initialize();
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.argv = ['python.py']");
        plot(RxBufferTotal, PointLen,Begin,End);
        Py_Finalize();

        delete[] RxBuffer_1, RxBuffer_2, RxBuffer_3, RxBufferTotal;

    }
    else {
        cout << "Begin and End value invalid" << endl;
    }
    return;
}


//信号检测
signalContent SignalDetection(double* input, float Freq) {

    int data_size = 307200;
    int SmoothNum = 3072;
    int times = 100;
    int InBandNum = 2000;

    double* ResSmoothFirst = new double[SmoothNum];
    double* ResSmoothSecond = new double[SmoothNum];
    double* ResSplit = new double[InBandNum];

    double* NoiseBase = new double[InBandNum / 10];
    double* NoiseAfterXianSu = new double[InBandNum / 10];
    double* NoiseLinespace = new double[InBandNum];
    double* NoiseCancel = new double[InBandNum];
    double* ThreasholdShow = new double[InBandNum];

    short* ChangePoint = new short[InBandNum];
    vector<int> SignalEdge;

    int j = 0;
    
    for (j = 0; j < data_size; j++)
    {
        input[j] = input[j] / data_size;
    }
    //求功率谱
    for (j = 0; j < data_size; j++)
    {
        input[j] = 10 * log10(input[j]);
    }
    //第一次平滑
    for (j = 0; j < data_size / 100; j++)
    {
        ResSmoothFirst[j] = GetMean(&input[j * 100 + 50], 100, 100);
    }
    for (j = 0; j < data_size / 100; j++)
    {
        ResSmoothSecond[j] = ResSmoothFirst[j];
    }
    //第二次平滑
    ResSmoothSecond[j] = ResSmoothFirst[j];
    for (j = 10; j < data_size / 100 - 10; j++)
    {
        ResSmoothSecond[j] = GetMean(&ResSmoothFirst[j], 10, 10);
    }
    //取出带内有效点
    int EdgePoint = (SmoothNum - InBandNum) / 2;
    for (j = 0; j < InBandNum; j++)
    {
        ResSplit[j] = ResSmoothSecond[j + EdgePoint];
    }
    //噪底估计
    for (j = 0; j < InBandNum / 10; j++)
    {
        NoiseBase[j] = FindMin(&ResSplit[j * 10], 10);
    }
    for (j = 1; j < InBandNum / 10; j++)
    {
        if (NoiseBase[j] - NoiseBase[j - 1] > 0.4)
        {
            NoiseBase[j] = NoiseBase[j - 1];
        }
    }
    //噪底插值
    int tempIndex;
    for (j = 0; j < InBandNum; j++)
    {
        tempIndex = int(j / 10);
        NoiseLinespace[j] = NoiseBase[tempIndex];// +((NoiseBase[int(j / 10) + 1] - NoiseBase[int(j / 10)]) * (j % 10) / 10);
    }
    //噪底消除
    for (j = 0; j < InBandNum; j++)
    {
        NoiseCancel[j] = ResSplit[j] - NoiseLinespace[j];
    }

    memset(ChangePoint, 0, InBandNum*2);
    for (j = 0; j < InBandNum; j++)
    {
        if (NoiseCancel[j] > 3)
        {
            ChangePoint[j] = 1;
        }
    }
    for (j = 0; j < InBandNum - 1; j++)
    {
        if (ChangePoint[j] + ChangePoint[j + 1] == 1)
        {
            SignalEdge.push_back(j);
        }
    }


    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.argv = ['python.py']");

    double* xaxis = new double[InBandNum];
    double* p = xaxis;
    for (int j = 0; j < 2000; j++ ) {
       
        *p = short(int(Freq) - 10);
        p = p + 1;
    }
    plot(NoiseCancel, 2000, int(Freq)-10, int(Freq)+10);
    Py_Finalize();

    //判断信号是否存在
    cout.setf(ios::fixed);
    int SignalNum = SignalEdge.size();
    float Left, Right, SigFreq, SigBand;
    for (j = 0; j < SignalNum; j = j + 2)
    {
        Left = float(SignalEdge[j]) /100.0;
        Right = float(SignalEdge[j + 1]) /100.0;
        SigFreq = (Right + Left) / 2 + Freq - 10.0;
        SigBand = Right - Left;
        cout << "Signal: " << j / 2 + 1 << " Freq at: " << fixed << setprecision(3) << SigFreq << " BandWidth: " << fixed << setprecision(3) << SigBand << endl;
    }

    signalContent sigContent;
    sigContent.SignalNumber = (float)SignalNum;
    sigContent.SignalEdge = SignalEdge;

       


    delete[] ResSmoothFirst, ResSmoothSecond, ResSplit, NoiseBase, NoiseAfterXianSu, NoiseLinespace, NoiseCancel, ThreasholdShow;

    return sigContent;

}




//单设备信号检测
signalContent SingleDeviceDetection(SOCKET clntSock, float Freq) {
    
    int* RecvData = new int[307200];
    double* FftRes = new double[307200];
    int data_size = 307200;

    SetSampleRate(clntSock, 30720000);
    Sleep(200);
    SetSampleBand(clntSock, 20000000);
    Sleep(200);
    SetFreqAndGain(clntSock, Freq, 30);
    Sleep(200);


    CaptureDataMs(clntSock, 10, (char*)RecvData);
    FFT(RecvData, FftRes, data_size);
    signalContent myreturn =  SignalDetection(FftRes, Freq);


    /*Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.argv = ['python.py']");
    plot(FftRes, 307200, int(Freq)-10, int(Freq)+10);
    Py_Finalize();*/

    delete[] RecvData, FftRes;
    return myreturn;
}

//单设备信号识别
void SingleDetectRecognize(SOCKET clntSock, float freq, double R, int D) {
    int* RecvData = new int[NUM];
    
    SetSampleRate(clntSock, 4000000);
    Sleep(200);
    SetFreqAndGain(clntSock,freq,30);
    Sleep(200);
    CaptureData(clntSock, NUM,(char*)RecvData); //第二个入参是采集的点数，这个数需要是2048的整数倍，第三个入参是数据保存的数组地址
    
    double num = 0;
    double modulation = 0;
    double* Tao = new double[80000];
    double FX[3];

    main_detect_recognize(RecvData, R, D, &num, &modulation, FX, Tao);

    string ModuList[13] = {"AWGN","BPSK","QPSK","8PSK","16APSK","OQPSK","16QAM","32QAM","2FSK","4FSK","8FSK","16FSK","16PSK"};


    if (D == 1)
    {
        cout << "detect  " << num << "  signals" << endl;
    }

    if (R == 1) {
        if (0 <= int(modulation) <= 12) {
            cout << "Modulation:  " << ModuList[int(modulation)] << endl;
        }
        else {
            cout << "Modulation can not be recognized！" << endl;
        }
    }
}

//多设备信号检测
double *  MultiDetectRecognize(SOCKET clntSock_0, SOCKET clntSock_1, SOCKET clntSock_2, float freq, double R, int D,int ModulationFinal[3]) {
    int* RecvData0 = new int[NUM];
    int* RecvData1 = new int[NUM];
    int* RecvData2 = new int[NUM];

    SetSampleRate(clntSock_0, 4000000);
    SetSampleRate(clntSock_1, 4000000);
    SetSampleRate(clntSock_2, 4000000);
    Sleep(200);
    SetFreqAndGain(clntSock_0, freq, 30);
    SetFreqAndGain(clntSock_1, freq, 30);
    SetFreqAndGain(clntSock_2, freq, 30);
    Sleep(200);
    CaptureData(clntSock_0, NUM, (char*)RecvData0);
    CaptureData(clntSock_1, NUM, (char*)RecvData1);
    CaptureData(clntSock_2, NUM, (char*)RecvData2);

    double num[3] = { 0,0,0 };
    double modulation[3] = { 0,0,0 };
    double* Tao0 = new double[80000];
    double* Tao1 = new double[80000];
    double* Tao2 = new double[80000];
    double FX0[3], FX1[3], FX2[3];

    main_detect_recognize(RecvData0, R, D, num, modulation, FX0, Tao0);
    main_detect_recognize(RecvData1, R, D, num+1, modulation+1, FX1, Tao1);
    main_detect_recognize(RecvData2, R, D, num+2, modulation+2, FX2, Tao2);

    string ModuList[13] = {"AWGN","BPSK","QPSK","8PSK","16APSK","OQPSK","16QAM","32QAM","2FSK","4FSK","8FSK","16FSK","16PSK"};

    for (int i = 0; i < 3; i++) {
        ModulationFinal[i] = modulation[i];
    }
    
    return modulation;
}
