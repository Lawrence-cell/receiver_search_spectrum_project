//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: detect_recognize.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "detect_recognize.h"
#include "firstfunction2.h"
#include "rt_nonfinite.h"
#include "signal_num_detect_v2.h"
#include <cstring>
#include <string.h>


// Function Definitions
void detect_recognize(const creal_T data[200000], double choose, double *num,
                      double FX[3], double *modulation,double Tao[80000])
{
  static creal_T b_data[200000];
  *modulation = 0.0;
  std::memcpy(&b_data[0], &data[0], 200000U * sizeof(creal_T));
  signal_num_detect_v2(b_data, num, FX,Tao);
  if (choose == 1.0) {
    *modulation = firstfunction2(*(creal_T (*)[200000])&data[0]);
    
  }
  
}

int max_index(int A[], int up) {
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


int peak_detect(double Tao[80000]) {
    double cut1[200];
    int num_detect = 0;
    for (int i = 0; i < 200; i++) {
        cut1[i] = Tao[i * 400 + 200];
    }
    for (int i = 0; i < 200; i++) {
        if (cut1[i] >= 0.09) {
            num_detect += 1;
        }
    }
    return num_detect;
}



int out_N[4] = { 0,0,0,0 };
int out_M[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
int out_n = 0;
int out_m = 0;
double m = 0;
int num1 = 0;
creal_T dcv[200000];
int modulation_c = 0;
double flag = 0;



void main_detect_recognize(int RecvData[], double R,int D, double* num, double* modulation,double FX[3],double Tao[80000]) {
    /*函数说明：
    int RecvData[]为原始采集数据,一般采样率为4M，-40dBm,频点为2GHz
    double R 使能调制方式识别，1为 进行调制方式识别，在main.h中修改
    int D 使能信号个数检测功能， 1为使能信号个数检测,在main.h中修改
    double num 为信号个数，未使能信号个数检测功能时为-1，使能时为0,1,2,3，代表信号个数
    modulation 为调制方式代号，未使能时为-1，使能时代号含义如下：
    switch (int(modulation)) {
          case 0:
              std::cout << "AWGN" << endl; break;
          case 1:
              std::cout << "BPSK" << endl; break;
          case 2:
              std::cout << "QPSK" << endl; break;
          case 3:
              std::cout << "8PSK" << endl; break;
          case 4:
              std::cout << "16APSK" << endl; break;
          case 5:
              std::cout << "OQPSK" << endl; break;
          case 6:
              std::cout << "16QAM" << endl; break;
          case 7:
              std::cout << "32QAM" << endl; break;
          case 8:
              std::cout << "2FSK" << endl; break;
          case 9:
              std::cout << "4FSK" << endl; break;
          case 10:
              std::cout << "8FSK" << endl; break;
          case 11:
              std::cout << "16FSK" << endl; break;
          case 12:
              std::cout << "16PSK" << endl; break;
          default:
              std::cout << "未使能调制方式识别功能！" << endl; break;
              }

         FX和Tao为调试日志，不用管它
    
    
    */

    short* RecvData_temp = (short*)RecvData;
               
        for (int i = 0; i < 200000; i++) {
            dcv[i].re = ((double)(RecvData_temp[i * 2]));
            dcv[i].im = ((double)(RecvData_temp[i * 2 + 1]));

        }
        
        signal_num_detect_v2(dcv, &flag, FX, Tao);
        if (R == 1.0) {
            m = firstfunction2(*(creal_T(*)[200000]) & dcv[0]);

        }
        modulation_c = int(m);
        
        if (modulation_c == 5) {
            num1 = peak_detect(Tao);
            if (num1 == 1) {
                flag = 0;
                modulation_c = 0;
            }
            else { flag = 1; }

        }

        
        if ((modulation_c == 8) || (modulation_c == 9) || (modulation_c == 10) || (modulation_c == 11)) { flag = 1; }
        /*8,9,10,11为FSK */                   
            out_N[int(flag)] += 1;                               
        
            out_M[modulation_c] += 1;
                                 
            
    
    //write_matrix(FX);
    out_n = max_index(out_N, 4);
       
    
        out_m = max_index(out_M, 13);
         
        if (R == 1) {
            *modulation = out_m;
        }else{ *modulation = -1; }
        if (D == 1) {
            *num = flag;
        }
        else { *num = -1; }
        out_M[out_m]=0;
}

