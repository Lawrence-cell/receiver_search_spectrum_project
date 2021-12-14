#pragma once
#define MAIN_H
#define NUM 200000  //输入数据长度
#define CYC 1      //循环采集数据次数

//Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

//采集数据
#include <math.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "detect_recognize.h"
#include "detect_recognize_terminate.h"
#include "rt_nonfinite.h"
#include <string.h>
#include <fstream>


void detect_recognize(const creal_T data[200000], double choose, double* num,
    double FX[3], double* modulation, double Tao[80000]);

void main_detect_recognize(int RecvData[], double R, int D, double* num, double* modulation,double FX[3],double Tao[80000]);

void write_hang(double Tao[80000]);

void write_matrix(double FX[CYC][3]);

int Max_index(int A[], int up);

int Peak_detect(double Tao[80000]);

