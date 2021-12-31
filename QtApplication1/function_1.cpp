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
    cmd += ("np.linspace(" + str1 + "," + str2 + "," + str3 + "),");
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
    PyRun_SimpleString("plt.ylabel('PSD')");
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
        cout << CaptureTimesDevice_1 << endl;
        cout << CaptureTimesDevice_2 << endl;
        cout << CaptureTimesDevice_3 << endl;
        float End_1 = Begin + 20 * CaptureTimesDevice_1;
        float End_2 = End_1 + 20 * CaptureTimesDevice_2;
        float End_3 = End_2 + 20 * CaptureTimesDevice_3;

        int ValidLen = 2000 * PacketSize / 3072;

        double* RxBuffer_1 = new double[ValidLen * CaptureTimesDevice_1];
        double* RxBuffer_2 = new double[ValidLen * CaptureTimesDevice_2];
        double* RxBuffer_3 = new double[ValidLen * CaptureTimesDevice_3];


        fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_plan p = fftw_plan_dft_1d(3072, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_complex* in1 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_complex* out1 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_plan p1 = fftw_plan_dft_1d(3072, in1, out1, FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_complex* in2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_complex* out2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * PacketSize);
        fftw_plan p2 = fftw_plan_dft_1d(3072, in2, out2, FFTW_FORWARD, FFTW_ESTIMATE);

        thread th1(SpectrumScan, clntSock_0, Begin, End_1, PacketSize, RxBuffer_1, p, in, out);
        thread th2(SpectrumScan, clntSock_1, End_1, End_2, PacketSize, RxBuffer_2, p1, in1, out1);
        thread th3(SpectrumScan, clntSock_2, End_2, End_3, PacketSize, RxBuffer_3, p2, in2, out2);

        th1.join();
        th2.join();
        th3.join();
        //SpectrumScan(clntSock_0, Begin, End_1, PacketSize, RxBuffer_1, p, in, out);
        //SpectrumScan(clntSock_1, End_1, End_2, PacketSize, RxBuffer_2, p1, in1, out1);
        //SpectrumScan(clntSock_2, End_2, End_3, PacketSize, RxBuffer_3, p2, in2, out2);

        fftw_destroy_plan(p);
        fftw_free(in);
        fftw_free(out);
        fftw_destroy_plan(p1);
        fftw_free(in1);
        fftw_free(out1);
        fftw_destroy_plan(p2);
        fftw_free(in2);
        fftw_free(out2);

        double* RxBufferTotal = new double[ValidLen * (CaptureTimesDevice_1 + CaptureTimesDevice_2 + CaptureTimesDevice_3)];

        memcpy(&RxBufferTotal[0], &RxBuffer_1[0], CaptureTimesDevice_1 * ValidLen * 8);
        memcpy(&RxBufferTotal[ValidLen * CaptureTimesDevice_1], &RxBuffer_2[0], ValidLen * CaptureTimesDevice_2 * 8);
        memcpy(&RxBufferTotal[(ValidLen * CaptureTimesDevice_1) + ValidLen * CaptureTimesDevice_2], &RxBuffer_3[0], CaptureTimesDevice_3 * 2000 * 8);


        Py_Initialize();
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.argv = ['python.py']");
        plot(RxBufferTotal, ValidLen * (CaptureTimesDevice_1 + CaptureTimesDevice_2 + CaptureTimesDevice_3), Begin, End_3);

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

signalContent SignalDetection_noPlot(double* input, float Freq) {

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

    memset(ChangePoint, 0, InBandNum * 2);
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


    //判断信号是否存在
    cout.setf(ios::fixed);
    int SignalNum = SignalEdge.size();
    float Left, Right, SigFreq, SigBand;
    for (j = 0; j < SignalNum; j = j + 2)
    {
        Left = float(SignalEdge[j]) / 100.0;
        Right = float(SignalEdge[j + 1]) / 100.0;
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

signalContent scene1SweepFunc(SOCKET clntSock, float Freq) {

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
    signalContent myreturn = SignalDetection_noPlot(FftRes, Freq);


    /*Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.argv = ['python.py']");
    plot(FftRes, 307200, int(Freq)-10, int(Freq)+10);
    Py_Finalize();*/

    delete[] RecvData, FftRes;
    return myreturn;
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
void  MultiDetectRecognize(SOCKET clntSock_0, SOCKET clntSock_1, SOCKET clntSock_2, float freq, double R, int D,int ModulationFinal[3]) {
    int* RecvData0 = new int[NUM];
    int* RecvData1 = new int[NUM];
    int* RecvData2 = new int[NUM];

    SetSampleRate(clntSock_0, 4000000);
    SetSampleRate(clntSock_1, 4000000);
    SetSampleRate(clntSock_2, 4000000);
    Sleep(200);
    SetFreqAndGain(clntSock_0, freq, 55);
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
    
   /* return modulation;*/
}


void collectOneTimeDate(SOCKET clntSock, int Begin, int End) {
    const int PacketSize = 2048;
    int CaptureTimes = (End - Begin) / 20;
    int CapturePoints = PacketSize;        //一共采集的点数
    if ((End - Begin) % 20)
        CaptureTimes++;
    if (End > Begin)
        cout << "SpectrumScan" << endl;

    SetSampleRate(clntSock, 61440000);
    Sleep(200);
    SetSampleBand(clntSock, 20000000);
    Sleep(200);
    SetFreqAndGain(clntSock, 1000, 30);
    Sleep(200);

    double* final_recv = new double[PacketSize * CaptureTimes];     //存放最后绘图使用的数据
    int* fft_recv = new int[(PacketSize * CaptureTimes) + 1];
    /**totaltime = fft_recv[PacketSize * CaptureTimes];*/
    /*int time = fft_recv[PacketSize * CaptureTimes];*/
    /*int time = *(fft_recv + PacketSize * CaptureTimes);*/
    double* SingelFFTRes = new double[PacketSize];
    int showTime = 10;


    int frequencyLen = 666 * CaptureTimes;
    /*double* datamatrix = new double[PacketSize * CaptureTimes][10];*/
    int ** datamatrix = new int* [showTime]; //开辟行
    for (int i = 0; i < showTime; i++)
        datamatrix[i] = new int[frequencyLen]; //开辟列

    int rows = showTime - 1;

    for (int j = 0; j < showTime; j++) {
        CaptureData_2048(clntSock, Begin, End, (char*)fft_recv);
        /*Sleep(500);*/
        
        short* Ptr = (short*)fft_recv;
        short IQ_data_buffer[PacketSize][2];
        short fftshift_buffer[PacketSize][2];


        for (int i = 0; i < CaptureTimes; i++)
        {
            //split IQ
            for (int jj = 0; jj < PacketSize; jj++)
            {
                IQ_data_buffer[jj][0] = *(Ptr + (2 * PacketSize * i) + 2 * jj);
                IQ_data_buffer[jj][1] = *(Ptr + (2 * PacketSize * i) + 2 * jj + 1);

            }
            //fftshift
            for (int ii = 0; ii < PacketSize / 2; ii++)
            {
                fftshift_buffer[(PacketSize / 2) + ii][0] = IQ_data_buffer[ii][0];
                fftshift_buffer[(PacketSize / 2) + ii][1] = IQ_data_buffer[ii][1];
                fftshift_buffer[ii][0] = IQ_data_buffer[(PacketSize / 2) + ii][0];
                fftshift_buffer[ii][1] = IQ_data_buffer[(PacketSize / 2) + ii][1];
            }
            for (int jj = 0; jj < PacketSize; jj++)
            {
                SingelFFTRes[jj] = sqrt(fftshift_buffer[jj][0] * fftshift_buffer[jj][0] + fftshift_buffer[jj][1] * fftshift_buffer[jj][1]);
            }
            for (int j = 0; j < PacketSize; j++)
            {
                SingelFFTRes[j] = 10 * log10(SingelFFTRes[j]);
            }
            memcpy(&final_recv[666 * i], &SingelFFTRes[690], 8 * 666);

            //memcpy(&final_recv[0], SingelFFTRes,  8*2048);

        }

        /*memcpy(datamatrix[rows], final_recv, PacketSize * CaptureTimes);*/
        cout << "*******************************************************";
        for (int i = 0; i <frequencyLen; i++)
        {
            if (final_recv[i] < 0)
            {
                datamatrix[rows][i] = 0;
                cout << final_recv[i] << endl;
            }
            else
            {
                datamatrix[rows][i] = final_recv[i];
            }        
        }
        rows = rows - 1;
    }

    //memcpy(&final_recv[0], &SingelFFTRes[0], 8 * 2048);
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.argv = ['python.py']");

    /*void plot_dynamic(T * x, int N1, int start, int end, int showTime, V * y, bool equal)*/

    plot_dynamic(datamatrix, 666 * CaptureTimes, (float)Begin * 1000000, (float)End * 1000000, showTime);

    Py_Finalize();
    delete[] final_recv, fft_recv, SingelFFTRes, datamatrix;
}

template<class T, class V = int>
void plot_dynamic(T* x, int N1, int start, int end, int showTime, V* y, bool equal) {
    printf("start");

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("from matplotlib import pyplot as plt");
    PyRun_SimpleString("from numpy.lib.index_tricks import index_exp");
    PyRun_SimpleString("import numpy as np");
    PyRun_SimpleString("from matplotlib import cm as CM");
    PyRun_SimpleString("print ('---import sys---')");
    PyRun_SimpleString("sys.path.append('./')");
    //python中所有数据结构都为pyobject类型
    PyObject* pName, * pModule, * pDict, * pFunc, * pArgs, * preturn, * pdata;

    // 载入名为pytest的脚本  
    pName = PyUnicode_FromString("xtest");
    pModule = PyImport_Import(pName);
    if (!pModule) {
        printf("can't find pytest.py");
        getchar();

    }
    pDict = PyModule_GetDict(pModule);
    if (!pDict) {
        printf("can't find pytest.py");
    }

    // 找出函数名为add的函数  
    printf("----------------------\n");
    pFunc = PyDict_GetItemString(pDict, "plot");
    if (!pFunc || !PyCallable_Check(pFunc)) {
        printf("can't find function [add]");
        getchar();

    }


    PyObject* bigList, * list;//数据是二维数组，bigdata里有showtime个小数组 ， 每个小数组list是一个时刻的频谱图
    bigList = PyList_New(showTime);

    for (int i = 0; i < showTime; i++) {
        //填充小数组
        list = PyList_New(N1);

        for (int j = 0; j < N1; j++) {

            if (PyList_SetItem(list, j, Py_BuildValue("i", (int)x[i][j])) == -1) {
                printf("写入数据失败");
            }
           
        }
        //填充大数组
        if (PyList_SetItem(bigList, i, list) == -1) {
            printf("写入数据失败");
        }
    }

    //// 参数进栈  
    *pArgs;
    pArgs = PyTuple_New(5);

    //  PyObject* Py_BuildValue(char *format, ...)  
    //  把C++的变量转换成一个Python对象。当需要从  
    //  C++传递变量到Python时，就会使用这个函数。此函数  
    //  有点类似C的printf，但格式不同。常用的格式有  
    //  s 表示字符串，  
    //  i 表示整型变量，  
    //  f 表示浮点数，  
    //  O 表示一个Python对象。  

    PyTuple_SetItem(pArgs, 0, bigList);
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", showTime));
    PyTuple_SetItem(pArgs, 2, Py_BuildValue("i", N1));
    PyTuple_SetItem(pArgs, 3, Py_BuildValue("i", start));
    PyTuple_SetItem(pArgs, 4, Py_BuildValue("i", end));

    preturn = PyObject_CallObject(pFunc, pArgs);
    printf("%ld", PyLong_AsLong(preturn));
}

void CaptureData_2048(SOCKET clntSock, int64_t Begin, int64_t End, char* RxBuffer) {
    cout << "capture data start" << endl;
    char str[28] = "saopin 2048        !LEN";
    int* sendBuf = (int*)str;
    sendBuf[5] = Begin;
    sendBuf[6] = End;
    send(clntSock, (const char*)sendBuf, 28, NULL);
    Sleep(100);

    int cyctimes = (End - Begin) / 20;
    int cyc_res = (End - Begin) % 20;
    if (cyc_res)
        cyctimes++;


    int nRecvBuf = 2048 * 1024;//设置socket缓冲大小
    setsockopt(clntSock, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));

    int size = ((cyctimes * 2048) * 4) + 4;
    int RecvSize;

    while (size > 0)
    {
        RecvSize = recv(clntSock, RxBuffer, size, 0);
        if (SOCKET_ERROR == RecvSize)
            cout << "recv error" << endl;
        size = size - RecvSize;
        RxBuffer += RecvSize;
    }               //数据接收完成
    cout << "capture data finished" << endl;

}

int SingleSpectrumScan_2048(SOCKET clntSock, int Begin, int End)
{

    const int PacketSize = 2048;
    int CaptureTimes = (End - Begin) / 20;
    int CapturePoints = PacketSize;        //一共采集的点数
    if ((End - Begin) % 20)
        CaptureTimes++;
    if (End > Begin)
        cout << "SpectrumScan" << endl;

    SetSampleRate(clntSock, 61440000);
    Sleep(200);
    SetSampleBand(clntSock, 20000000);
    Sleep(200);
    SetFreqAndGain(clntSock, 1000, 30);
    Sleep(200);

    double* final_recv = new double[PacketSize * CaptureTimes];     //存放最后绘图使用的数据
    int* fft_recv = new int[PacketSize * CaptureTimes + 1];
    CaptureData_2048(clntSock, Begin, End, (char*)fft_recv);

    int time = (int)fft_recv[PacketSize * CaptureTimes];
    
    short* Ptr = (short*)fft_recv;
    short IQ_data_buffer[PacketSize][2];
    short fftshift_buffer[PacketSize][2];
    double* SingelFFTRes = new double[PacketSize];
    for (int i = 0; i < CaptureTimes; i++)
    {
        //split IQ
        for (int jj = 0; jj < PacketSize; jj++)
        {
            IQ_data_buffer[jj][0] = *(Ptr + (2 * PacketSize * i) + 2 * jj);
            IQ_data_buffer[jj][1] = *(Ptr + (2 * PacketSize * i) + 2 * jj + 1);

        }
        //fftshift
        for (int ii = 0; ii < PacketSize / 2; ii++)
        {
            fftshift_buffer[(PacketSize / 2) + ii][0] = IQ_data_buffer[ii][0];
            fftshift_buffer[(PacketSize / 2) + ii][1] = IQ_data_buffer[ii][1];
            fftshift_buffer[ii][0] = IQ_data_buffer[(PacketSize / 2) + ii][0];
            fftshift_buffer[ii][1] = IQ_data_buffer[(PacketSize / 2) + ii][1];
        }
        for (int jj = 0; jj < PacketSize; jj++)
        {
            SingelFFTRes[jj] = sqrt(fftshift_buffer[jj][0] * fftshift_buffer[jj][0] + fftshift_buffer[jj][1] * fftshift_buffer[jj][1]);
        }
        for (int j = 0; j < PacketSize; j++)
        {
            SingelFFTRes[j] = 10 * log10(SingelFFTRes[j]);
        }
        memcpy(&final_recv[666 * i], &SingelFFTRes[690], 8 * 666);

        //memcpy(&final_recv[0], SingelFFTRes,  8*2048);

    }
    //memcpy(&final_recv[0], &SingelFFTRes[0], 8 * 2048);
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.argv = ['python.py']");
    plot(final_recv, 666 * CaptureTimes, (float)Begin, (float)End);
    Py_Finalize();
    delete[] final_recv, fft_recv, SingelFFTRes;
    return time;

}


int equalSignalGenerate_AMC(SOCKET SrSocket_0) {
    double CYC_1 = 1;
    int out_m[13]{};
    double R = 1;           //使能调制方式识别功能，1为进行调制方式识别。
    int D = 0;
    int* RecvData = new int[200000];

    //测试
    short* recv_data = new short[6144000];
    int* recvdata = new int[3072000];
    double* fftres = new double[3072000];

    //解决二维数组维度不能动态定义的问题
    //allocator<double*> a_1;
    //int rows = 50;
    //allocator<double> b_1;
    //int cols = 3;
    //double ** FX = a_1.allocate(rows);//开辟行
    //for (int i = 0; i < rows; ++i)
    //    *(FX + i) = b_1.allocate(cols);

    double FX[50][3];
    int out_N[4] = { 0,0,0,0 };
    int out_M[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
    int out_n = 0;
    /* int out_m = 0;*/
    int out_n_temp = 0;
    int out_m_temp = 0;
    double c1_temp = 0, c2_temp = 0;
    double c1 = 0, c2 = 0;

    double modulation = 0;
    double flag = -1;

    short* recvdata_temp = (short*)recvdata;
    double Tao[80000];


    const int PacketSize = 50000;

    SetSampleRate(SrSocket_0, 4000000);     //采样率4M
    Sleep(100);
    SetRxFreq(SrSocket_0, 2000);      //频点2.4G
    Sleep(100);
    SetSampleBand(SrSocket_0, 20000000); //设置采样带宽20M
    Sleep(100);



    qDebug("loop begin");
    for (int j = 0; j < CYC_1; j++) {

        CaptureData(
            SrSocket_0, NUM,
            (char*)RecvData); //第二个入参是采集的点数，这个数需要是2048的整数倍，第三个入参是数据保存的数组地址
        double num = 0;
        double modulation = 0;
        //short* recvdata = (short*)RecvData;                 //是否要int转short？
        main_detect_recognize(RecvData, R, D, &num, &modulation, FX[j], Tao);

        //销毁生成的数组

        //cout << "第" << j + 1 << "次采集数据检测结果为：" << endl;

        out_M[int(modulation)] += 1;
        out_m_temp = Max_index(out_M, 13);
        c2_temp = double(out_M[out_m_temp]) / (j + 1);
        qDebug() << "调制方式" << modulation;



        //std::cout << "tiao zhi fang shi pan jue zhi xin du wei" << c2_temp * 100 << "%" << endl;
        //std::cout << "调制方式判决置信度为：" << c2_temp * 100 << '%' << endl;

        Sleep(10);
        std::cout << endl;
    }
   
    delete[]RecvData;
    
    qDebug("loop over");
    return out_m_temp;
}