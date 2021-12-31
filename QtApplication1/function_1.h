#pragma once
#include "main_suibian.h"
#include "fftw3.h"
//#include <Python.h>
#include <windows.h>
#include <cmath>
#include <ctime>
#include <vector>
#include <iomanip>
#include <thread>
//
//
using namespace std;

/*************************************************************/
/*****************************库******************************/
/*************************************************************/

#pragma comment(lib,"ws2_32.lib") //socket需要的库

/***********************************************************/
/**************************功能函数**************************/
/***********************************************************/

void pythonInitial();

struct signalContent
{
    int SignalNumber;
    vector<int> SignalEdge;
};


template<class T, class V = int>
void plot(T* x, int N1, int start, int end, V* y = NULL, bool equal = false);
//template<class T, class V = int>
//void plotForMix(T* x0, T* x1, T* x2, T* x3, int N1, V* y = NULL, bool equal = false);

double GetMean(double* nput, int step, int smooth);

double FindMin(double* input, int step);

void FFT(int* input, double* output, int fft_size);

SOCKET CreatSocket(const char* ipAddr);

/*************************************************************/
/***************************接口函数***************************/
/*************************************************************/

void SetFreqAndGain(SOCKET clntSock, float Freq, int32_t Gain);

void SetRxFreq(SOCKET clntSock, float Freq);

void SetTxFreq(SOCKET clntSock, float Freq);

void SetGain(SOCKET clntSock, int32_t Gain);

void SetAttenuation(SOCKET clntSock, int32_t Attenuation);

void SetSampleRate(SOCKET clntSock, int32_t SampleRate);

void SetSampleBand(SOCKET clntSock, int32_t SampleBand);

void SetTxBand(SOCKET clntSock, int32_t SampleBand);

void CaptureData(SOCKET clntSock, int32_t SampleNum, char* RxBuffer);

void CaptureDataMs(SOCKET clntSock, int32_t Ms, char* RxBuffer);

void SendSignel(SOCKET clntSock, int32_t SampleRate, int32_t SampleBand, float TxFreq, int32_t Attenuation, int32_t SignalType);

void SpectrumScan(SOCKET clntSock, int32_t Begin, int32_t End, int PacketSize, double* RxBuffer, fftw_plan p, fftw_complex* in, fftw_complex* out);

void SingleSpectrumScan(SOCKET clntSock, float Begin, float End, int PacketSize);

void MultiDeviceScanMix(SOCKET clntSock_0, SOCKET clntSock_1, SOCKET clntSock_2, float Begin, float End, int PacketSize);

void MultiDeviceScanCont(SOCKET clntSock_1, SOCKET clntSock_2, SOCKET clntSock_3, float Begin, float End, int PacketSize);

signalContent SignalDetection(double* input, float Freq);

signalContent SingleDeviceDetection(SOCKET clntSock, float Freq);

void SingleDetectRecognize(SOCKET clntSock, float freq,double R,int D);

void MultiDetectRecognize(SOCKET clntSock_0, SOCKET clntSock_1, SOCKET clntSock_2, float freq, double R, int D,int ModulationFinal[3]);

void collectOneTimeDate(SOCKET clntSock, int Begin, int End);

template<class T, class V = int>
void plot_dynamic(T* x, int N1, int start, int end, int showTime, V* y = NULL, bool equal = false);

void CaptureData_2048(SOCKET clntSock, int64_t Begin, int64_t End, char* RxBuffer);

int SingleSpectrumScan_2048(SOCKET clntSock, int Begin, int End);

int equalSignalGenerate_AMC(SOCKET Socket_0);

signalContent scene1SweepFunc(SOCKET clntSock, float Freq);

signalContent SignalDetection_noPlot(double* input, float Freq);
