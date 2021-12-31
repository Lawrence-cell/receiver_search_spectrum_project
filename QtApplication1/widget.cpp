#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsDropShadowEffect>
#include <iostream>
#include "function_1.h"
//#include <fstream>
//#include <stdio.h>
//#include <stdlib.h>
//#include "appinit.h"
//#include <QApplication>
//#include <QFile>
//#include <QFont>
//#include "Dll1.h"
#include <QDebug>
#include <Qstring>
#include <memory>
#include <iomanip>
#include <QPainter>
#include <QPainterPath>
//#include <QLibrary>
//#include"testmain.h"
//#include"windows.h"
//#pragma comment(lib,"./Dll1.lib")
#define length_N   3072000
//clock_t startTime, endTime;

int flag = 0;
int* Recvdata2 = new int[3072000];
short recv_data[6144000];
//SOCKET SrSocket_0 = CreatSocket("192.168.1.47");
//SOCKET SrSocket_1 = CreatSocket("192.168.1.48");
//SOCKET SrSocket_2 = CreatSocket("192.168.1.49");

typedef struct {
    int PCI;
    float Offset;
    int pssIndex;
    int sssIndex;
    const char* Mode;
    const char* cp_type;
    const char* mib_state;
    float BandWidth;
    float Utilization_rate[80];
    int RB_Num;
    int S_LTE_Judge;
    int aaa;
}infoset;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    line = "";
    image = QImage(1200, 1200, QImage::Format_RGB32);
    QColor backColor = qRgb(255, 255, 255);
    image.fill(backColor);
    ui->setupUi(this);
    this->setProperty("canMove",true);
    this->initUi();
    this->initMember();
}

Widget::~Widget()
{
    delete ui;
}

/**********************************************************初始化函数****************************************************************/

void Widget::initUi()
{
    //初始化窗口边框
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor("#444444"));
    shadow->setBlurRadius(16);
    
    ui->w_bg->setGraphicsEffect(shadow);
    //ui->lay_bg->setMargin(12);

    //Logo
    QPixmap logo(":/icons/logo.png");
    ui->lab_logo->setPixmap(logo);

    //itemLogo
    QPixmap item1(":/icons/item_01.png");
    QPixmap item2(":/icons/item_02.png");
//    ui->lab_item_01->setPixmap(item1);
//    ui->lab_item_02->setPixmap(item2);

//    connect(ui->btn_main_item_5, &QPushButton::click, ui->sw_main, [=](){
//        ui->sw_main->setCurrentIndex(4);
//    });

//    connect(ui->btn_main_item_11, &QPushButton::click, ui->sw_main, [=](){
//        ui->sw_main->setCurrentIndex(5);
//    });
}

void Widget::initMember()
{
    this->myMbox = new MyMessageBox();
    connect(myMbox,SIGNAL(btnchicked(int)),this,SLOT(changeMboxReturn(int)));

    //最小化到托盘
    QIcon icon = QIcon(":/icons/logo.png");//设置最小图标
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("Peach"); //提示文字
    //添加托盘列表项(还原与退出)
    returnNormal = new QAction(" Show", this);
    returnNormal->setFont(QFont("Arial", 9));
    returnNormal->setObjectName("returnNormal");
    returnNormal->setIcon(QIcon(":/icons/show.png"));
    quitAction = new QAction(" Quit", this);
    quitAction->setFont(QFont("Arial", 9));
    quitAction->setObjectName("quitAction");
    quitAction->setIcon(QIcon(":/icons/out.png"));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));           //绑定槽函数退出
    connect(returnNormal, SIGNAL(triggered()), this, SLOT(showNormal()));   //绑定槽函数还原界面

    //创建托盘菜单(必须先创建动作，后添加菜单项，还可以加入菜单项图标美化)
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(returnNormal);
    trayIconMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayIconMenu);
}

/**********************************************************自定义函数****************************************************************/

void Widget::littleShow()
{
    this->hide();//隐藏主窗口
    trayIcon->show();//显示托盘

    //显示到系统提示框的信息
    QString title="Peach";
    QString text="正自动在后台运行";
    trayIcon->showMessage(title,text,QSystemTrayIcon::Information,3000); //此参数为提示时长
}

/**********************************************************控件槽函数****************************************************************/

void Widget::closeEvent(QCloseEvent *event)
{
    myMbox->setIcon("question");
    myMbox->setBodyText("How to leave?");
    myMbox->setButtonText("Little","Logout");
    myMbox->exec();
    if(mbox_return == 0) {
        event->ignore();
    }else if(mbox_return == 1){
        event->ignore();
        littleShow();
    }
}

void Widget::changeMboxReturn(int num)
{
    this->mbox_return = num;
}

void Widget::on_singleDeviceSweep_Button_clicked() {
    ui->sw_main->setCurrentIndex(7);
    
}


void Widget::on_singleDeviceSweep_TimeTestBtn_clicked()
{
    int totaltime;
    SOCKET SrSocket_0 = CreatSocket("192.168.1.48");
    int startF = ui->singleDeviceSweep_StartText_3->toPlainText().toInt();
    int stopF = ui->singleDeviceSweep_StopText_3->toPlainText().toInt();

    ////精度很高的扫频 无法输出cf bw 扫频范围很大
    //SingleSpectrumScan(SrSocket_0, startF, stopF, 3072);
    //
    
    
    totaltime = SingleSpectrumScan_2048(SrSocket_0, startF, stopF);
    
    ui->TimeTest_result->setText(QString("%1").arg(totaltime));
    closesocket(SrSocket_0);
}


void Widget::on_equalSignalRx_clicked() {
    cout << "equalSignal" << endl;
    SOCKET Socket_0 = CreatSocket("192.168.1.48");
    //**********************************************下为获取调制方式*****************************************************
    int modulation = equalSignalGenerate_AMC(Socket_0);

    
    int outputType = 0;
    string str2 = " ";
    switch (modulation) {
    case 0:
        str2 = str2.append("AWGN");
        outputType = 2; break;
    case 1:
        str2 = str2.append("BPSK"); break;
    case 2:
        str2 = str2.append("QPSK"); 
        outputType = 3; break;
    case 3:
        str2 = str2.append("8PSK"); break;
    case 4:
        str2 = str2.append("16APSK"); break;
    case 5:
        str2 = str2.append("OQPSK"); break;
    case 6:
        str2 = str2.append("16QAM"); 
        outputType = 4; break;
    case 7:
        str2 = str2.append("32QAM"); break;
    case 8:
        str2 = str2.append("2FSK"); break;
    case 9:
        str2 = str2.append("4FSK"); break;
    case 10:
        str2 = str2.append("8FSK"); break;
    case 11:
        str2 = str2.append("16FSK"); break;
    case 12:
        str2 = str2.append("16PSK"); break;
    default:
        std::cout << "modulation judge failed" << endl; break;
    }
    


    signalContent sigContent = SingleDeviceDetection(Socket_0, 2000);
    
    
    float Left, Right, SigFreq, SigBand;
    int BW;
    int CF;

    
  

    //**********************************************下为获取带宽和中心频点*****************************************************

        Left = float(sigContent.SignalEdge[0]) / 100.0;
        Right = float(sigContent.SignalEdge[1]) / 100.0;
        SigFreq = (Right + Left) / 2 + 2000 - 10.0;
        SigBand = Right - Left;

        string str1 = "信号";
        str1 = str1.append(std::to_string(1));
        str1 = str1.append(" ,  频点: ");//拼接字符串
        str1 = str1.append(std::to_string(SigFreq));//拼接字符串
        CF = SigFreq;
        str1 = str1.append(" MHz, 带宽: ");//拼接字符串
        BW = SigBand;
        str1 = str1.append(std::to_string(SigBand));//拼接字符串
        str1 = str1.append(" MHz, 调制方式");//拼接字符串

        str1 = str1.append(str2);
        ui->textBrowser_4->append(QString::fromStdString(str1));


    cout << "start send" << endl;
    //**********************************************下为发送信号****************************************************
    int bandwidth = BW;

    cout << "BW:";
    cout << bandwidth << endl;
    cout << "CF:";
    cout << CF << endl;
    cout << "type";
    cout << outputType << endl;
    

    int fs = ((bandwidth * 1000000) * 4) / 1.2;
    SendSignel(Socket_0, fs, 20000000, CF, 50000, 3);
    /*ui->textBrowser_4->append(QString::fromStdString("信号已发送"));*/
    string str33 = " ";
    str33.append("send success");
    ui->textBrowser_4->append(QString::fromStdString(str33));
    
    closesocket(Socket_0);
}



void Widget::on_averageSweep_clicked() {
    SOCKET Socket_0 = CreatSocket("192.168.1.47");
    SOCKET Socket_1 = CreatSocket("192.168.1.48");
    SOCKET Socket_2 = CreatSocket("192.168.1.49");

    int startF = ui->textEdit_5->toPlainText().toInt();
    int stopF = ui->textEdit_6->toPlainText().toInt();


    MultiDeviceScanMix(Socket_0, Socket_1, Socket_2, startF, stopF, 3072);


    closesocket(Socket_0);
    closesocket(Socket_1);
    closesocket(Socket_2);

}

void Widget::on_contSweep_clicked() {
    SOCKET Socket_0 = CreatSocket("192.168.1.47");
    SOCKET Socket_1 = CreatSocket("192.168.1.48");
    SOCKET Socket_2 = CreatSocket("192.168.1.49");

    int startF = ui->textEdit_11->toPlainText().toInt();
    int stopF = ui->textEdit_16->toPlainText().toInt();
    
    MultiDeviceScanCont(Socket_0, Socket_1, Socket_2, startF, stopF, 3072);

    closesocket(Socket_0);
    closesocket(Socket_1);
    closesocket(Socket_2);
}


void Widget::on_singleDeviceSweep_LaunchBtn_clicked() {
    SOCKET Socket_0 = CreatSocket("192.168.1.48");
    int start_f = ui->singleDeviceSweep_StartText->toPlainText().toInt();
    int stop_f = ui->singleDeviceSweep_StopText->toPlainText().toInt();
    int CF = (start_f + stop_f) / 2;

    //**************************************注释 测试***********************************
    //signalContent sigContent = SingleDeviceDetection(Socket_0, CF);


    //float Left, Right, SigFreq, SigBand;

    //for (int j = 0; j < sigContent.SignalNumber; j = j + 2)
    //{
    //    Left = float(sigContent.SignalEdge[j]) / 100.0;
    //    Right = float(sigContent.SignalEdge[j + 1]) / 100.0;
    //    SigFreq = (Right + Left) / 2 + CF - 10.0;
    //    SigBand = Right - Left;

    //    string str1 = "信号";
    //    str1 = str1.append(std::to_string(j/2 +  1));
    //    str1 = str1.append(" ,  频点: ");//拼接字符串
    //    str1 = str1.append(std::to_string(SigFreq));//拼接字符串
    //    str1 = str1.append(" MHz, 带宽: ");//拼接字符串
    //    str1 = str1.append(std::to_string(SigBand));//拼接字符串
    //    str1 = str1.append(" MHz");//拼接字符串
    //    ui->textBrowser_3->append(QString::fromStdString(str1));
    //}
    /*SingleSpectrumScan(Socket_0, CF - 10, CF + 10, 3072);*/
    //*********************************************TEST WATERFALL*********************************************
    collectOneTimeDate(Socket_0, start_f, stop_f);
    //*********************************************************************************************************
    closesocket(Socket_0);
}


void Widget::on_btn_main_item_1_clicked()
{
    ui->sw_main->setCurrentIndex(0);
    //SOCKET SrSocket_0 = CreatSocket("192.168.1.47");
   // func1();
}

void Widget::on_btn_main_item_2_clicked()
{
    ui->sw_main->setCurrentIndex(1);
  //  Paint();
}

void Widget::on_btn_main_item_3_clicked()
{
    ui->sw_main->setCurrentIndex(2);
}

void Widget::on_btn_main_item_4_clicked()
{
    ui->sw_main->setCurrentIndex(3);
}

void Widget::on_btn_main_item_5_clicked()
{
    ui->sw_main->setCurrentIndex(5);
}

void Widget::on_btn_main_item_6_clicked()
{
    ui->sw_main->setCurrentIndex(6);
}

void Widget::on_btn_logout_clicked()
{
    close();
}

void Widget::on_btn_littleshow_clicked()
{
    showMinimized();
}
    
void Widget::on_pushButton_clicked() {
    //qDebug("1111");
    /*ui->pushButton->setText("检测中...");*/
    func1();
   // ui->pushButton->setText("启动检测");
}



int Widget::func1() {

    //
    
   /* double num;
    double modulation;
    double FX[3];
    double Tao[80000];
    double R = 0;
    int D = 1;
    int RecvData[200000];
    for (int i = 0; i < 200000; i++) {
        RecvData[i] = 0;*/
   // }
   // qDebug("receive data over");
    //ui->textBrowser->setText("111111");
    //函数调用
   /* tadd(RecvData, R, D, &num, &modulation, FX, Tao);*/

    ///////

     //加载Dll部分
    double CYC_1 = ui->spinBox->text().toDouble();
    
    HINSTANCE hDllInst;
    hDllInst = LoadLibrary(L"Dll1.dll"); //调用DLL
    if (hDllInst == NULL)
    {
        qDebug("loaddll failed!");
        return -1;
    }
    else
    {
        qDebug("loaddll success!");
    }
    typedef void (*PLUSFUNC)(int RecvData[], double R, int D, double* num, double* modulation, double FX[3], double Tao[80000]);
    PLUSFUNC dll_detect_recognize = (PLUSFUNC)GetProcAddress(hDllInst, "main_detect_recognize");



    double R = 0;           //使能调制方式识别功能，1为进行调制方式识别。
    int D = 1;

    int* RecvData = new int[200000];


    SOCKET SrSocket_0 = CreatSocket("192.168.1.47");


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
    int out_m = 0;
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
    SetGain(SrSocket_0, 40);
    Sleep(1000);


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
        

            //qDebug() << "检测到" << num << "个信号" ;
            num = (int)num;
            /*ui->label_6->setText(QString("%1").arg(num));*/
            out_N[int(num)] += 1;
            out_n_temp = Max_index(out_N, 4);
            c1_temp = double(out_N[out_n_temp]) / (j + 1);


            //如何将数字与字符串进行拼接
            string str1 = std::to_string(c1_temp * 100);//double -> string
            str1 = str1.append("%");//拼接字符串

            
            //QDebug("xin hao ge shu pan jue zhi xin du %") << c1_temp * 100 << '%' << endl;
            qDebug() << "循环次数 j: " << j;
            
            if (num != 0) //检测到信号
            {
                
                QString str5 = "检测到信号";
                ui->label_5->setText(str5);


                QString str11 = "概率";
                ui->label_7->setText(str11);
               /* QString str8 = "检测概率";
                ui->label_7->setText(str8);*/
                
                ui->label_8->setText(QString::fromStdString(str1));// string -> Qstring
            }
            else {
                QString str = "未检测到信号";
                ui->label_5->setText(str);

                QString str6 = "误检概率";
                ui->label_7->setText(str6);

                string error_Probability = std::to_string((1 - c1_temp) * 100);
                error_Probability = error_Probability.append("%");
                ui->label_8->setText(QString::fromStdString(error_Probability));// string -> Qstring

            }
            
    
        
           
            //std::cout << "tiao zhi fang shi pan jue zhi xin du wei" << c2_temp * 100 << "%" << endl;
            //std::cout << "调制方式判决置信度为：" << c2_temp * 100 << '%' << endl;
        


        Sleep(10);
        std::cout << endl;
    }
    /*for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            b_1.destroy(*(FX + i) + j);
        }
        b_1.deallocate(*(FX + i), cols);
        a_1.destroy(FX + i);
    }
    a_1.deallocate(FX, rows);*/
    delete[]RecvData;
    closesocket(SrSocket_0);
    qDebug("loop over");
    return 0;
}





void Widget::on_pushButton_2_clicked(){
    flag = 1;//正弦波
    qDebug()<<"flag is " << flag;
    ui->label_14->setVisible(false);
    ui->textEdit->setVisible(false);
}

void Widget::on_pushButton_3_clicked(){
    flag = 2;//AWGN
    qDebug() << "flag is " << flag;
    ui->label_14->setVisible(false);
    ui->textEdit->setVisible(false);
}

void Widget::on_pushButton_4_clicked(){
    flag = 3;//QPSK 
    qDebug() << "flag is " << flag;
    ui->label_14->setVisible(true);
    ui->textEdit->setVisible(true);
}


void Widget::on_singleDeviceSweep_StartSweep_clicked() {
    SOCKET Socket_0 = CreatSocket("192.168.1.48");
    int start_f = ui->singleDeviceSweep_StartText->toPlainText().toInt();
    int stop_f = ui->singleDeviceSweep_StopText->toPlainText().toInt();
   /* int CF = (start_f + stop_f) / 2;*///原来版本


    int CF = start_f + 10;

    int n = ( stop_f - start_f) / 20;
    float Left, Right, SigFreq, SigBand;
    
    int catchtime = 0;
    for (int i = 0; i < n; i++)
    {
        signalContent sigContent = scene1SweepFunc(Socket_0, CF);
        
       
        for (int j = 0; j < sigContent.SignalNumber; j = j + 2)
        {
           
           Left = float(sigContent.SignalEdge[j]) / 100.0;
           Right = float(sigContent.SignalEdge[j + 1]) / 100.0;
           SigFreq = (Right + Left) / 2 + CF - 10.0;
           SigBand = Right - Left;
           if (SigBand > 0.2)
           {
               if (SigBand <= 0.28)
               {
                   SigBand = 0.2;
               }
               if (SigBand > 15)
               {
                   SigBand = 20;
               }
               string str1 = "信号";
               str1 = str1.append(std::to_string(catchtime + j / 2 + 1));
               str1 = str1.append(" ,  频点: ");//拼接字符串
               str1 = str1.append(std::to_string(SigFreq));//拼接字符串
               str1 = str1.append(" MHz, 带宽: ");//拼接字符串
               str1 = str1.append(std::to_string(SigBand));//拼接字符串
               str1 = str1.append(" MHz");//拼接字符串
               ui->textBrowser_3->append(QString::fromStdString(str1));
           }
        }
        if (sigContent.SignalNumber != 0)
        {
            catchtime = catchtime + 1;
        }
        CF = CF + 20;
    }
    
    //**************************************************原来版本****************************************************
    //signalContent sigContent = SingleDeviceDetection(Socket_0, CF);


    //float Left, Right, SigFreq, SigBand;

    //for (int j = 0; j < sigContent.SignalNumber; j = j + 2)
    //{
    //    Left = float(sigContent.SignalEdge[j]) / 100.0;
    //    Right = float(sigContent.SignalEdge[j + 1]) / 100.0;
    //    SigFreq = (Right + Left) / 2 + CF - 10.0;
    //    SigBand = Right - Left;

    //    string str1 = "信号";
    //    str1 = str1.append(std::to_string(j/2 +  1));
    //    str1 = str1.append(" ,  频点: ");//拼接字符串
    //    str1 = str1.append(std::to_string(SigFreq));//拼接字符串
    //    str1 = str1.append(" MHz, 带宽: ");//拼接字符串
    //    str1 = str1.append(std::to_string(SigBand));//拼接字符串
    //    str1 = str1.append(" MHz");//拼接字符串
    //    ui->textBrowser_3->append(QString::fromStdString(str1));
    //}
    /*SingleSpectrumScan(Socket_0, CF - 10, CF + 10, 3072);*/
    //**************************************************原来版本****************************************************

    closesocket(Socket_0);
}

void Widget::on_pushButton_5_clicked(){
    flag = 4;//16QAM
    qDebug() << "flag is " << flag;
    ui->label_14->setVisible(true);
    ui->textEdit->setVisible(true);
}

void Widget::on_arbitrarySignalGenerate_LaunchBtn_clicked() {
     SOCKET SrSocket_2 = CreatSocket("192.168.1.48");
    //转换成qstring 再转成 int

     //单位均为MHz
    int bandWidth = ui->textEdit->toPlainText().toInt();
    int fc = ui->textEdit_3->toPlainText().toInt();
    int gain = ui->textEdit_4->toPlainText().toInt();
    

    int fs = ((bandWidth * 1000000) * 4) / 1.2;
    /*qDebug() << fs;
    qDebug() << fc;
    qDebug() << bandWidth;
    qDebug() << gain;*/
    //int d = atoi(->);
    SendSignel(SrSocket_2, fs, 20000000, fc, gain, flag);
   //SendSignel(SrSocket_0, 30720000, 20000000, 1000, 10000, 3);
    closesocket(SrSocket_2);
}

void Widget::on_LTErunButton_clicked(){

    SOCKET SrSocket_0 = CreatSocket("192.168.1.47");

    ui->sw_main->setCurrentIndex(4);
 
    infoset infoset_0;
    //��ȡ100ms����
    int size = sizeof(short);
    FILE* fp = NULL;
    int error = 0;
    error = fopen_s(&fp, "2330_1.txt", "rb");
    //error = fopen_s(&fp, "C:/Users/thunder/Desktop/save_data_2349.8_20210928154235.txt", "rb");
    if (error != 0)
    {
        qDebug("file does not exist.");
    }

    fread(recv_data, size, length_N * 2, fp);
    fclose(fp);

    HINSTANCE hDllInst;
    hDllInst = LoadLibrary(TEXT("LTEdll2.dll")); //����DLL

    typedef int (*PLUSFUNC)(short c[], infoset* b);

    if (NULL == hDllInst) {
        qDebug("LoadLibrary failed!\r\n");

    }
    else {
        qDebug("LoadLibrary success!\r\n");
    }

    PLUSFUNC LTE_Identification = (PLUSFUNC)GetProcAddress(hDllInst, "LTE_Identification"); //GetProcAddressΪ��ȡ�ú����ĵ�ַ

    int CF_LTE = ui->MultiDevice_CFtext->toPlainText().toInt();

    SetSampleRate(SrSocket_0, 30720000);
    Sleep(200);
    SetGain(SrSocket_0, 40);
    Sleep(1000);
    SetRxFreq(SrSocket_0, CF_LTE);
    Sleep(200);
    //CaptureDataMs(SrSocket_0,  200, (char*)Recvdata2);
    //**********************************************************************************************
    CaptureData(SrSocket_0, 3072000, (char*)Recvdata2);
 
    short* recv_data_tmp = (short*)Recvdata2;

    for (int i = 0; i < 6144000; i++) {
        
        recv_data[i] = recv_data_tmp[i];

    }
    //*************************************************************************************************

    int a;
    a = LTE_Identification(recv_data, &infoset_0);
    ui->label_19->setText(QString::number(infoset_0.PCI));
    ui->label_21->setText(QString::number(infoset_0.Offset));
    ui->label_23->setText(QString::number(infoset_0.sssIndex));
    ui->label_25->setText(QString::number(infoset_0.pssIndex));
    ui->label_27->setText(infoset_0.Mode);
    ui->label_28->setText(infoset_0.cp_type);
    ui->label_50->setText(infoset_0.mib_state);
    ui->label_31->setText(QString::number(infoset_0.BandWidth));


     //如何将数字与字符串进行拼接
    for (int i = 0; i < 80; i++) {
        if (infoset_0.Utilization_rate[i] > 0.001 && infoset_0.Utilization_rate[i] < 1) {
            string str1 = "子帧资源元素利用率：";
            str1 = str1.append(std::to_string(infoset_0.Utilization_rate[i] * 100));
            str1 = str1.append("%");//拼接字符串
            ui->textBrowser->append(QString::fromStdString(str1));
        }
    }
    //delete[]recv_data;
    closesocket(SrSocket_0);
}

void Widget::on_pushButton_7_clicked() {
   SOCKET SrSocket_0 = CreatSocket("192.168.1.47");
   SOCKET SrSocket_1 = CreatSocket("192.168.1.48");
   SOCKET SrSocket_2 = CreatSocket("192.168.1.49");
   
   int Begin = ui->textEdit_5->toPlainText().toInt();
   int End = ui->textEdit_6->toPlainText().toInt();
   MultiDeviceScanMix(SrSocket_0, SrSocket_1, SrSocket_2,  Begin,  End, 3072);
   closesocket(SrSocket_0);
   closesocket(SrSocket_1);
   closesocket(SrSocket_2);
      
}

void Widget::on_pushButton_8_clicked() {
    //MultiDetectRecognize(SrSocket_0, SrSocket_1, SrSocket_2, 1000, 1, 1);
    SOCKET SrSocket_0 = CreatSocket("192.168.1.47");
    SOCKET SrSocket_1 = CreatSocket("192.168.1.48");
    SOCKET SrSocket_2 = CreatSocket("192.168.1.49");
    
 
    int ModulationFinal[3];

    MultiDetectRecognize(SrSocket_0, SrSocket_1, SrSocket_2, 2000, 1, 1, ModulationFinal);
    //qDebug("test");
    string ModuList[13] = { "AWGN","BPSK","QPSK","8PSK","16APSK","OQPSK","16QAM","32QAM","2FSK","4FSK","8FSK","16FSK","16PSK" };

    int a = ModulationFinal[0];
    int b = ModulationFinal[1];
    int c = ModulationFinal[2];

    if (a == b && b == c) {
        ui->label_62->setText(QString::fromStdString(ModuList[a]));
        ui->label_61->setText("100%");
    }
    else if (a != b && a != c && b != c) {
        ui->label_62->setText(QString::fromStdString(ModuList[a]));
        ui->label_61->setText("33%");
    }
    else if (a == b && b != c)
    {
        ui->label_62->setText(QString::fromStdString(ModuList[a]));
        ui->label_61->setText("66%");
    }
    else if (a == c && b != c) {
        ui->label_62->setText(QString::fromStdString(ModuList[a]));
        ui->label_61->setText("66%");
    }
    else if (b == c && b != a) {
        ui->label_62->setText(QString::fromStdString(ModuList[b]));
        ui->label_61->setText("66%");
    }
    ui->label_51->setText(QString::fromStdString(ModuList[a]));
    ui->label_53->setText(QString::fromStdString(ModuList[b]));
    ui->label_56->setText(QString::fromStdString(ModuList[c]));
    closesocket(SrSocket_0);
    closesocket(SrSocket_1);
    closesocket(SrSocket_2);
}


void Widget::on_pushButton_20_clicked() {
    funcPage2();
    /*ui->label_131->setText("3");
    ui->label_134->setText("100.000000%");*/
}

int Widget::funcPage2() {

    //获取循环次数 从界面获得
    double CYC_1 = ui->spinBox_6->text().toDouble();

    HINSTANCE hDllInst;
    hDllInst = LoadLibrary(L"Dll1.dll"); //调用DLL
    if (hDllInst == NULL)
    {
        qDebug("loaddll failed!");
        return -1;
    }
    else
    {
        qDebug("loaddll success!");
    }
    typedef void (*PLUSFUNC)(int RecvData[], double R, int D, double* num, double* modulation, double FX[3], double Tao[80000]);
    PLUSFUNC dll_detect_recognize = (PLUSFUNC)GetProcAddress(hDllInst, "main_detect_recognize");


    

    double R = 0;           //使能调制方式识别功能，1为进行调制方式识别。
    int D = 1;

    int* RecvData = new int[200000];


    SOCKET SrSocket_0 = CreatSocket("192.168.1.47");


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

    double FX[100][3]{};
    int out_N[4] = { 0,0,0,0 };
    int out_M[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
    int out_n = 0;
    int out_m = 0;
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
    SetGain(SrSocket_0, 40);
    Sleep(1000);



    qDebug("loop begin");
    for (int j = 0; j < CYC_1; j++) {
        CaptureData(
            SrSocket_0, NUM,
            (char*)RecvData); //第二个入参是采集的点数，这个数需要是2048的整数倍，第三个入参是数据保存的数组地址
        double num = 0;
        double modulation = 0;
        //short* recvdata = (short*)RecvData;                 //是否要int转short？
        main_detect_recognize (RecvData, R, D, &num, &modulation, FX[j], Tao);

        //销毁生成的数组
        cout << FX[j][0] << endl << FX[j][1] << endl << FX[j][2] << endl;
         
                                          
        //cout << "第" << j + 1 << "次采集数据检测结果为：" << endl;
       

            //qDebug() << "检测到" << num << "个信号" ;
            num = (int)num;
           
            
            out_N[int(num)] += 1;
            out_n_temp = Max_index(out_N, 4);
            c1_temp = double(out_N[out_n_temp]) / (j + 1);

            //如何将数字与字符串进行拼接
            string str1 = std::to_string(c1_temp * 100);//double -> string
            str1 = str1.append("%");//拼接字符串

            ui->label_134->setText(QString::fromStdString(str1));// string -> Qstring
            //QDebug("xin hao ge shu pan jue zhi xin du %") << c1_temp * 100 << '%' << endl;
            qDebug() << "循环次数 j: " << j;
        
       
            //string str2 = std::to_string(c2_temp * 100);//double -> string
            //str2 = str2.append("%");//拼接字符串
           /* ui->label_12->setText(QString::fromStdString(str2));*/
            //std::cout << "tiao zhi fang shi pan jue zhi xin du wei" << c2_temp * 100 << "%" << endl;
            //std::cout << "调制方式判决置信度为：" << c2_temp * 100 << '%' << endl;
        


        Sleep(10);
        std::cout << endl;
    }
    ui->label_131->setText(QString("%1").arg(out_n_temp));
    /*for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            b_1.destroy(*(FX + i) + j);
        }
        b_1.deallocate(*(FX + i), cols);
        a_1.destroy(FX + i);
    }
    a_1.deallocate(FX, rows);*/
    delete[]RecvData;
    closesocket(SrSocket_0);
    qDebug("loop over");
    return 0;
}


void Widget::on_pushButton_19_clicked() {
    funcPage3();
}

int Widget::funcPage3() {
    double CYC_1 = ui->spinBox_5->text().toDouble();
    int out_m[13]{};
    double R = 1;           //使能调制方式识别功能，1为进行调制方式识别。
    int D = 0;
    int* RecvData = new int[200000];


    SOCKET SrSocket_0 = CreatSocket("192.168.1.47");


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
    SetGain(SrSocket_0, 50);
    Sleep(1000);
   /* SetFreqAndGain(SrSocket_0, 2000, 40);
    Sleep(100);*/


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
    string str2 = std::to_string(c2_temp * 100);//double -> string
    str2 = str2.append("%");//拼接字符串
    ui->label_130->setText(QString::fromStdString(str2));

    switch (out_m_temp) {
    case 0:
        ui->label_124->setText("AWGN"); break;
    case 1:
        ui->label_124->setText("BPSK"); break;
    case 2:
        ui->label_124->setText("QPSK"); break;
    case 3:
        ui->label_124->setText("8PSK"); break;
    case 4:
        ui->label_124->setText("16APSK"); break;
    case 5:
        ui->label_124->setText("OQPSK"); break;
    case 6:
        ui->label_124->setText("16QAM"); break;
    case 7:
        ui->label_124->setText("32QAM"); break;
    case 8:
        ui->label_124->setText("2FSK"); break;
    case 9:
        ui->label_124->setText("4FSK"); break;
    case 10:
        ui->label_124->setText("8FSK"); break;
    case 11:
        ui->label_124->setText("16FSK"); break;
    case 12:
        ui->label_124->setText("16PSK"); break;
    default:
        std::cout << "modulation judge failed" << endl; break;

    }
    /*for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            b_1.destroy(*(FX + i) + j);
        }
        b_1.deallocate(*(FX + i), cols);
        a_1.destroy(FX + i);
    }
    a_1.deallocate(FX, rows);*/
    delete[]RecvData;
    closesocket(SrSocket_0);
    qDebug("loop over");
    return 0;
}



void Widget::Paint()
{
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    int pointx = 450, pointy = 450;
    int width = 800, height = 800;
    painter.drawRect(5, 5, 1200 - 10, 1200 - 10);
    painter.drawLine(pointx - width / 2 + 50, pointy, pointx + width / 2 + 100, pointy);
    painter.drawLine(pointx, pointy - height / 2, pointx, pointy + height / 2);

    QList<QPointF>points;   //creatPoints()是一个函数，
   
    QPainterPath path(points[0]);

    for (int i = 0; i < points.size() - 1; ++i)
    {
        QPointF sp = points[i];
        QPointF ep = points[i + 1];
        QPointF c1 = QPointF((sp.x() + ep.x()) / 2, (sp.y() + ep.y()) / 2);
        QPointF c2 = c2;
        path.cubicTo(c1, c2, ep);           //这个函数就是用来绘制曲线的。
        //第一个参数和第二个参数都是控制点（百度贝赛尔曲线）
        //第三个参数endpoint，是这小段曲线的终点
        //起点是按照你的队列顺序的前一个节点
        //这里将c1和c2设置成一样的是因为这小段曲线凹凸性是一样的。
    }
    painter.setRenderHint(QPainter::Antialiasing, true);       //防锯齿
    painter.setPen(QPen(Qt::black, 10));
    painter.translate(450, 450);
    painter.drawPath(path);
}



    
