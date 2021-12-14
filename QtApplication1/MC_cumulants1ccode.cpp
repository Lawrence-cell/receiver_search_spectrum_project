//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: MC_cumulants1ccode.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "MC_cumulants1ccode.h"
#include "detect_recognize_data.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions
//
// 六阶累计量与噪声无关
// MC_CLUMATION Summary of this function goes here
//    Detailed explanation goes here
// Arguments    : const creal_T singal[25000]
//                creal_T *ans_c20
//                creal_T *ans_c40
//                creal_T *ans_c42
//                creal_T *ans_c63
//                creal_T *c63_test
//                creal_T *ans_c80
// Return Type  : void
//
void MC_cumulants1ccode(const creal_T singal[25000], creal_T *ans_c20, creal_T
  *ans_c40, creal_T *ans_c42, creal_T *ans_c63, creal_T *c63_test, creal_T
  *ans_c80)
{
  static creal_T c20[25000];
  static creal_T c21[25000];
  static creal_T c22[25000];
  static creal_T c40[25000];
  static creal_T c41[25000];
  static creal_T c42[25000];
  static creal_T c43[25000];
  static creal_T c60[25000];
  static creal_T c63[25000];
  static creal_T c80[25000];
  double ar;
  double b_c63_test_tmp;
  double b_mean_c21_im;
  double b_mean_c21_re;
  double b_re;
  double b_singal_im;
  double b_singal_re;
  double b_x_im;
  double b_x_re;
  double c63_test_tmp;
  double c_re;
  double c_x_im;
  double c_x_re;
  double im;
  double im_tmp;
  double mean_c20_im;
  double mean_c20_re;
  double mean_c21_im;
  double mean_c21_re;
  double mean_c22_im;
  double mean_c22_re;
  double mean_c40_im;
  double mean_c40_re;
  double mean_c41_im;
  double mean_c41_re;
  double mean_c42_im;
  double mean_c42_re;
  double mean_c63_im;
  double mean_c63_re;
  double re;
  double re_tmp;
  double singal_im;
  double singal_re;
  double singal_re_tmp;
  double x_im;
  double x_re;
  int i;

  // 输入：信号signal，signal长度，噪声功率
  // 输出：6阶比四阶累积量判决式
  for (i = 0; i < 25000; i++) {
    mean_c42_re = singal[i].re;
    re = singal[i].im;
    singal_re = mean_c42_re * mean_c42_re - re * re;
    c20[i].re = singal_re;
    b_re = mean_c42_re * re;
    singal_im = b_re + b_re;
    c20[i].im = singal_im;

    // 计算y*y
    b_re = re * -re;
    c21[i].re = mean_c42_re * mean_c42_re - b_re;
    im = mean_c42_re * -re;
    c21[i].im = im + re * mean_c42_re;

    // 计算y*conj(y)
    b_singal_re = singal_re * mean_c42_re - singal_im * -re;
    b_singal_im = singal_re * -re + singal_im * mean_c42_re;
    c42[i].re = b_singal_re * mean_c42_re - b_singal_im * -re;
    c42[i].im = b_singal_re * -re + b_singal_im * mean_c42_re;

    // 计算  |y|^4
    // c63
    c22[i].re = mean_c42_re * mean_c42_re - -re * -re;
    c22[i].im = mean_c42_re * -re + -re * mean_c42_re;

    // 计算conj(y)*conj(y)
    singal_re_tmp = singal_re * mean_c42_re - singal_im * re;
    singal_im = singal_re * re + singal_im * mean_c42_re;
    c40[i].re = singal_re_tmp * mean_c42_re - singal_im * re;
    c40[i].im = singal_re_tmp * re + singal_im * mean_c42_re;

    // 计算y^4
    c41[i].re = singal_re_tmp * mean_c42_re - singal_im * -re;
    c41[i].im = singal_re_tmp * -re + singal_im * mean_c42_re;

    // 计算  (y)^3*conj(y)
    b_singal_re = mean_c42_re * mean_c42_re - b_re;
    b_singal_im = im + re * mean_c42_re;
    singal_re = b_singal_re * mean_c42_re - b_singal_im * -re;
    b_singal_im = b_singal_re * -re + b_singal_im * mean_c42_re;
    c43[i].re = singal_re * mean_c42_re - b_singal_im * -re;
    c43[i].im = singal_re * -re + b_singal_im * mean_c42_re;

    // 计算 y*(conj(y))^3
    b_singal_re = singal_re_tmp * mean_c42_re - singal_im * -re;
    b_singal_im = singal_re_tmp * -re + singal_im * mean_c42_re;
    singal_re = b_singal_re * mean_c42_re - b_singal_im * -re;
    b_singal_im = b_singal_re * -re + b_singal_im * mean_c42_re;
    c63[i].re = singal_re * mean_c42_re - b_singal_im * -re;
    c63[i].im = singal_re * -re + b_singal_im * mean_c42_re;

    // 计算  |y|^6
    b_singal_re = singal_re_tmp * mean_c42_re - singal_im * re;
    b_singal_im = singal_re_tmp * re + singal_im * mean_c42_re;
    singal_re = b_singal_re * mean_c42_re - b_singal_im * re;
    b_singal_im = b_singal_re * re + b_singal_im * mean_c42_re;
    b_singal_re = singal_re * mean_c42_re - b_singal_im * re;
    b_singal_im = singal_re * re + b_singal_im * mean_c42_re;
    singal_re = b_singal_re * mean_c42_re - b_singal_im * re;
    b_singal_im = b_singal_re * re + b_singal_im * mean_c42_re;
    c80[i].re = singal_re * mean_c42_re - b_singal_im * re;
    c80[i].im = singal_re * re + b_singal_im * mean_c42_re;
    b_singal_re = singal_re_tmp * mean_c42_re - singal_im * re;
    b_singal_im = singal_re_tmp * re + singal_im * mean_c42_re;
    singal_re = b_singal_re * mean_c42_re - b_singal_im * re;
    b_singal_im = b_singal_re * re + b_singal_im * mean_c42_re;
    c60[i].re = singal_re * mean_c42_re - b_singal_im * re;
    c60[i].im = singal_re * re + b_singal_im * mean_c42_re;
  }

  x_re = c20[0].re;
  x_im = c20[0].im;
  for (i = 0; i < 24999; i++) {
    x_re += c20[i + 1].re;
    x_im += c20[i + 1].im;
  }

  if (x_im == 0.0) {
    mean_c20_re = x_re / 25000.0;
    mean_c20_im = 0.0;
  } else if (x_re == 0.0) {
    mean_c20_re = 0.0;
    mean_c20_im = x_im / 25000.0;
  } else {
    mean_c20_re = x_re / 25000.0;
    mean_c20_im = x_im / 25000.0;
  }

  // 二阶累积量均值即 C20  E[y^2]
  x_re = c21[0].re;
  x_im = c21[0].im;
  for (i = 0; i < 24999; i++) {
    x_re += c21[i + 1].re;
    x_im += c21[i + 1].im;
  }

  if (x_im == 0.0) {
    mean_c21_re = x_re / 25000.0;
    mean_c21_im = 0.0;
  } else if (x_re == 0.0) {
    mean_c21_re = 0.0;
    mean_c21_im = x_im / 25000.0;
  } else {
    mean_c21_re = x_re / 25000.0;
    mean_c21_im = x_im / 25000.0;
  }

  // 二阶累积量均值即 C21  E[|y|^2]
  x_re = c22[0].re;
  x_im = c22[0].im;
  for (i = 0; i < 24999; i++) {
    x_re += c22[i + 1].re;
    x_im += c22[i + 1].im;
  }

  if (x_im == 0.0) {
    mean_c22_re = x_re / 25000.0;
    mean_c22_im = 0.0;
  } else if (x_re == 0.0) {
    mean_c22_re = 0.0;
    mean_c22_im = x_im / 25000.0;
  } else {
    mean_c22_re = x_re / 25000.0;
    mean_c22_im = x_im / 25000.0;
  }

  // 二阶累积量均值即 C22  E[(y*)^2]
  // 二阶累积量 c20均值的平方  (C20)^2
  // 二阶累积量 c21均值的平方  (C21)^2
  x_re = c42[0].re;
  x_im = c42[0].im;
  for (i = 0; i < 24999; i++) {
    x_re += c42[i + 1].re;
    x_im += c42[i + 1].im;
  }

  if (x_im == 0.0) {
    mean_c42_re = x_re / 25000.0;
    mean_c42_im = 0.0;
  } else if (x_re == 0.0) {
    mean_c42_re = 0.0;
    mean_c42_im = x_im / 25000.0;
  } else {
    mean_c42_re = x_re / 25000.0;
    mean_c42_im = x_im / 25000.0;
  }

  //  |y|的4次方的均值
  x_re = c40[0].re;
  x_im = c40[0].im;
  for (i = 0; i < 24999; i++) {
    x_re += c40[i + 1].re;
    x_im += c40[i + 1].im;
  }

  if (x_im == 0.0) {
    mean_c40_re = x_re / 25000.0;
    mean_c40_im = 0.0;
  } else if (x_re == 0.0) {
    mean_c40_re = 0.0;
    mean_c40_im = x_im / 25000.0;
  } else {
    mean_c40_re = x_re / 25000.0;
    mean_c40_im = x_im / 25000.0;
  }

  x_re = c41[0].re;
  x_im = c41[0].im;
  for (i = 0; i < 24999; i++) {
    x_re += c41[i + 1].re;
    x_im += c41[i + 1].im;
  }

  if (x_im == 0.0) {
    mean_c41_re = x_re / 25000.0;
    mean_c41_im = 0.0;
  } else if (x_re == 0.0) {
    mean_c41_re = 0.0;
    mean_c41_im = x_im / 25000.0;
  } else {
    mean_c41_re = x_re / 25000.0;
    mean_c41_im = x_im / 25000.0;
  }

  x_re = c43[0].re;
  x_im = c43[0].im;
  b_x_re = c63[0].re;
  b_x_im = c63[0].im;
  for (i = 0; i < 24999; i++) {
    x_re += c43[i + 1].re;
    x_im += c43[i + 1].im;
    b_x_re += c63[i + 1].re;
    b_x_im += c63[i + 1].im;
  }

  if (b_x_im == 0.0) {
    mean_c63_re = b_x_re / 25000.0;
    mean_c63_im = 0.0;
  } else if (b_x_re == 0.0) {
    mean_c63_re = 0.0;
    mean_c63_im = b_x_im / 25000.0;
  } else {
    mean_c63_re = b_x_re / 25000.0;
    mean_c63_im = b_x_im / 25000.0;
  }

  // |y|的6次方的均值
  b_x_re = c60[0].re;
  b_x_im = c60[0].im;
  c_x_re = c80[0].re;
  c_x_im = c80[0].im;
  for (i = 0; i < 24999; i++) {
    b_x_re += c60[i + 1].re;
    b_x_im += c60[i + 1].im;
    c_x_re += c80[i + 1].re;
    c_x_im += c80[i + 1].im;
  }

  //          mean_c84 = mean(c84);
  // 四阶累计累积量
  b_re = 6.0 * mean_c41_re;
  im = 6.0 * mean_c41_im;
  b_singal_re = 9.0 * mean_c42_re;
  b_singal_im = 9.0 * mean_c42_im;
  re = 18.0 * mean_c20_re;
  singal_re_tmp = 18.0 * mean_c20_im;
  c_re = re * mean_c20_re - singal_re_tmp * mean_c20_im;
  singal_re_tmp = re * mean_c20_im + singal_re_tmp * mean_c20_re;
  singal_im = 12.0 * mean_c21_re;
  im_tmp = 12.0 * mean_c21_im;
  re_tmp = singal_im * mean_c21_re - im_tmp * mean_c21_im;
  im_tmp = singal_im * mean_c21_im + im_tmp * mean_c21_re;
  c63_test_tmp = b_singal_re * mean_c21_re - b_singal_im * mean_c21_im;
  c63_test->re = (((mean_c63_re - (b_re * mean_c20_re - im * mean_c20_im)) -
                   c63_test_tmp) + (c_re * mean_c21_re - singal_re_tmp *
    mean_c21_im)) + (re_tmp * mean_c21_re - im_tmp * mean_c21_im);
  b_c63_test_tmp = b_singal_re * mean_c21_im + b_singal_im * mean_c21_re;
  c63_test->im = (((mean_c63_im - (b_re * mean_c20_im + im * mean_c20_re)) -
                   b_c63_test_tmp) + (c_re * mean_c21_im + singal_re_tmp *
    mean_c21_re)) + (re_tmp * mean_c21_im + im_tmp * mean_c21_re);

  //          c84_clu = mean_c84- 16*c63_clu*mean_c21-c40_clu.*conj(c40_clu)-18*c42_clu*c42_clu-72*c42_clu*mean_c21*mean_c21-24*mean_c21*mean_c21*mean_c21*mean_c21; 
  //  mean_c21_sigma =  mean_c21- sigma2;  %c21 - sigma2
  //  mean_c21_sigma_square = mean_c21_sigma.*mean_c21_sigma;  %c21 - sigma2 整体的平方 
  //  mean_c21_sigma_3square = mean_c21_sigma.*mean_c21_sigma.*mean_c21_sigma;  %c21 - sigma2 整体的3次方 
  //  cum4= c42_clu./mean_c21_sigma_square;     %即判决式  C40/（C21 - sigma2）
  // cum6= c63_clu./mean_c21_sigma_3square;
  // ans =abs(c42_clu/(c63_clu^(2/3)));  %特征
  if (mean_c21_im == 0.0) {
    if (mean_c20_im == 0.0) {
      ans_c20->re = mean_c20_re / mean_c21_re;
      ans_c20->im = 0.0;
    } else if (mean_c20_re == 0.0) {
      ans_c20->re = 0.0;
      ans_c20->im = mean_c20_im / mean_c21_re;
    } else {
      ans_c20->re = mean_c20_re / mean_c21_re;
      ans_c20->im = mean_c20_im / mean_c21_re;
    }
  } else if (mean_c21_re == 0.0) {
    if (mean_c20_re == 0.0) {
      ans_c20->re = mean_c20_im / mean_c21_im;
      ans_c20->im = 0.0;
    } else if (mean_c20_im == 0.0) {
      ans_c20->re = 0.0;
      ans_c20->im = -(mean_c20_re / mean_c21_im);
    } else {
      ans_c20->re = mean_c20_im / mean_c21_im;
      ans_c20->im = -(mean_c20_re / mean_c21_im);
    }
  } else {
    b_singal_im = std::abs(mean_c21_re);
    singal_im = std::abs(mean_c21_im);
    if (b_singal_im > singal_im) {
      b_singal_re = mean_c21_im / mean_c21_re;
      singal_im = mean_c21_re + b_singal_re * mean_c21_im;
      ans_c20->re = (mean_c20_re + b_singal_re * mean_c20_im) / singal_im;
      ans_c20->im = (mean_c20_im - b_singal_re * mean_c20_re) / singal_im;
    } else if (singal_im == b_singal_im) {
      if (mean_c21_re > 0.0) {
        b_singal_re = 0.5;
      } else {
        b_singal_re = -0.5;
      }

      if (mean_c21_im > 0.0) {
        singal_im = 0.5;
      } else {
        singal_im = -0.5;
      }

      ans_c20->re = (mean_c20_re * b_singal_re + mean_c20_im * singal_im) /
        b_singal_im;
      ans_c20->im = (mean_c20_im * b_singal_re - mean_c20_re * singal_im) /
        b_singal_im;
    } else {
      b_singal_re = mean_c21_re / mean_c21_im;
      singal_im = mean_c21_im + b_singal_re * mean_c21_re;
      ans_c20->re = (b_singal_re * mean_c20_re + mean_c20_im) / singal_im;
      ans_c20->im = (b_singal_re * mean_c20_im - mean_c20_re) / singal_im;
    }
  }

  // 输出结果
  b_re = 3.0 * mean_c20_re;
  im = 3.0 * mean_c20_im;
  b_mean_c21_re = mean_c21_re * mean_c21_re - mean_c21_im * mean_c21_im;
  b_mean_c21_im = mean_c21_re * mean_c21_im + mean_c21_im * mean_c21_re;
  ar = mean_c40_re - (b_re * mean_c20_re - im * mean_c20_im);
  singal_re = mean_c40_im - (b_re * mean_c20_im + im * mean_c20_re);
  if (b_mean_c21_im == 0.0) {
    if (singal_re == 0.0) {
      ans_c40->re = ar / b_mean_c21_re;
      ans_c40->im = 0.0;
    } else if (ar == 0.0) {
      ans_c40->re = 0.0;
      ans_c40->im = singal_re / b_mean_c21_re;
    } else {
      ans_c40->re = ar / b_mean_c21_re;
      ans_c40->im = singal_re / b_mean_c21_re;
    }
  } else if (b_mean_c21_re == 0.0) {
    if (ar == 0.0) {
      ans_c40->re = singal_re / b_mean_c21_im;
      ans_c40->im = 0.0;
    } else if (singal_re == 0.0) {
      ans_c40->re = 0.0;
      ans_c40->im = -(ar / b_mean_c21_im);
    } else {
      ans_c40->re = singal_re / b_mean_c21_im;
      ans_c40->im = -(ar / b_mean_c21_im);
    }
  } else {
    b_singal_im = std::abs(b_mean_c21_re);
    singal_im = std::abs(b_mean_c21_im);
    if (b_singal_im > singal_im) {
      b_singal_re = b_mean_c21_im / b_mean_c21_re;
      singal_im = b_mean_c21_re + b_singal_re * b_mean_c21_im;
      ans_c40->re = (ar + b_singal_re * singal_re) / singal_im;
      ans_c40->im = (singal_re - b_singal_re * ar) / singal_im;
    } else if (singal_im == b_singal_im) {
      if (b_mean_c21_re > 0.0) {
        b_singal_re = 0.5;
      } else {
        b_singal_re = -0.5;
      }

      if (b_mean_c21_im > 0.0) {
        singal_im = 0.5;
      } else {
        singal_im = -0.5;
      }

      ans_c40->re = (ar * b_singal_re + singal_re * singal_im) / b_singal_im;
      ans_c40->im = (singal_re * b_singal_re - ar * singal_im) / b_singal_im;
    } else {
      b_singal_re = b_mean_c21_re / b_mean_c21_im;
      singal_im = b_mean_c21_im + b_singal_re * b_mean_c21_re;
      ans_c40->re = (b_singal_re * ar + singal_re) / singal_im;
      ans_c40->im = (b_singal_re * singal_re - ar) / singal_im;
    }
  }

  singal_im = mean_c21_re * mean_c21_im;
  b_mean_c21_re = mean_c21_re * mean_c21_re - mean_c21_im * mean_c21_im;
  b_mean_c21_im = mean_c21_re * mean_c21_im + mean_c21_im * mean_c21_re;
  ar = (mean_c42_re - (mean_c20_re * mean_c20_re - mean_c20_im * -mean_c20_im))
    - 2.0 * (mean_c21_re * mean_c21_re - mean_c21_im * mean_c21_im);
  singal_re = (mean_c42_im - (mean_c20_re * -mean_c20_im + mean_c20_im *
    mean_c20_re)) - 2.0 * (singal_im + singal_im);
  if (b_mean_c21_im == 0.0) {
    if (singal_re == 0.0) {
      ans_c42->re = ar / b_mean_c21_re;
      ans_c42->im = 0.0;
    } else if (ar == 0.0) {
      ans_c42->re = 0.0;
      ans_c42->im = singal_re / b_mean_c21_re;
    } else {
      ans_c42->re = ar / b_mean_c21_re;
      ans_c42->im = singal_re / b_mean_c21_re;
    }
  } else if (b_mean_c21_re == 0.0) {
    if (ar == 0.0) {
      ans_c42->re = singal_re / b_mean_c21_im;
      ans_c42->im = 0.0;
    } else if (singal_re == 0.0) {
      ans_c42->re = 0.0;
      ans_c42->im = -(ar / b_mean_c21_im);
    } else {
      ans_c42->re = singal_re / b_mean_c21_im;
      ans_c42->im = -(ar / b_mean_c21_im);
    }
  } else {
    b_singal_im = std::abs(b_mean_c21_re);
    singal_im = std::abs(b_mean_c21_im);
    if (b_singal_im > singal_im) {
      b_singal_re = b_mean_c21_im / b_mean_c21_re;
      singal_im = b_mean_c21_re + b_singal_re * b_mean_c21_im;
      ans_c42->re = (ar + b_singal_re * singal_re) / singal_im;
      ans_c42->im = (singal_re - b_singal_re * ar) / singal_im;
    } else if (singal_im == b_singal_im) {
      if (b_mean_c21_re > 0.0) {
        b_singal_re = 0.5;
      } else {
        b_singal_re = -0.5;
      }

      if (b_mean_c21_im > 0.0) {
        singal_im = 0.5;
      } else {
        singal_im = -0.5;
      }

      ans_c42->re = (ar * b_singal_re + singal_re * singal_im) / b_singal_im;
      ans_c42->im = (singal_re * b_singal_re - ar * singal_im) / b_singal_im;
    } else {
      b_singal_re = b_mean_c21_re / b_mean_c21_im;
      singal_im = b_mean_c21_im + b_singal_re * b_mean_c21_re;
      ans_c42->re = (b_singal_re * ar + singal_re) / singal_im;
      ans_c42->im = (b_singal_re * singal_re - ar) / singal_im;
    }
  }

  if (x_im == 0.0) {
    x_re /= 25000.0;
    x_im = 0.0;
  } else if (x_re == 0.0) {
    x_re = 0.0;
    x_im /= 25000.0;
  } else {
    x_re /= 25000.0;
    x_im /= 25000.0;
  }

  b_re = 3.0 * x_re;
  im = 3.0 * x_im;
  re = 3.0 * mean_c41_re;
  singal_re_tmp = 3.0 * mean_c41_im;
  c_re = 18.0 * mean_c22_re;
  b_singal_im = 18.0 * mean_c22_im;
  singal_re = c_re * mean_c20_re - b_singal_im * mean_c20_im;
  b_singal_im = c_re * mean_c20_im + b_singal_im * mean_c20_re;
  b_mean_c21_re = mean_c21_re * mean_c21_re - mean_c21_im * mean_c21_im;
  b_mean_c21_im = mean_c21_re * mean_c21_im + mean_c21_im * mean_c21_re;
  mean_c42_re = b_mean_c21_re * mean_c21_re - b_mean_c21_im * mean_c21_im;
  b_mean_c21_im = b_mean_c21_re * mean_c21_im + b_mean_c21_im * mean_c21_re;
  ar = ((((mean_c63_re - c63_test_tmp) - (b_re * mean_c20_re - im * mean_c20_im))
         - (re * mean_c22_re - singal_re_tmp * mean_c22_im)) + (singal_re *
         mean_c21_re - b_singal_im * mean_c21_im)) + (re_tmp * mean_c21_re -
    im_tmp * mean_c21_im);
  singal_re = ((((mean_c63_im - b_c63_test_tmp) - (b_re * mean_c20_im + im *
    mean_c20_re)) - (re * mean_c22_im + singal_re_tmp * mean_c22_re)) +
               (singal_re * mean_c21_im + b_singal_im * mean_c21_re)) + (re_tmp *
    mean_c21_im + im_tmp * mean_c21_re);
  if (b_mean_c21_im == 0.0) {
    if (singal_re == 0.0) {
      ans_c63->re = ar / mean_c42_re;
      ans_c63->im = 0.0;
    } else if (ar == 0.0) {
      ans_c63->re = 0.0;
      ans_c63->im = singal_re / mean_c42_re;
    } else {
      ans_c63->re = ar / mean_c42_re;
      ans_c63->im = singal_re / mean_c42_re;
    }
  } else if (mean_c42_re == 0.0) {
    if (ar == 0.0) {
      ans_c63->re = singal_re / b_mean_c21_im;
      ans_c63->im = 0.0;
    } else if (singal_re == 0.0) {
      ans_c63->re = 0.0;
      ans_c63->im = -(ar / b_mean_c21_im);
    } else {
      ans_c63->re = singal_re / b_mean_c21_im;
      ans_c63->im = -(ar / b_mean_c21_im);
    }
  } else {
    b_singal_im = std::abs(mean_c42_re);
    singal_im = std::abs(b_mean_c21_im);
    if (b_singal_im > singal_im) {
      b_singal_re = b_mean_c21_im / mean_c42_re;
      singal_im = mean_c42_re + b_singal_re * b_mean_c21_im;
      ans_c63->re = (ar + b_singal_re * singal_re) / singal_im;
      ans_c63->im = (singal_re - b_singal_re * ar) / singal_im;
    } else if (singal_im == b_singal_im) {
      if (mean_c42_re > 0.0) {
        b_singal_re = 0.5;
      } else {
        b_singal_re = -0.5;
      }

      if (b_mean_c21_im > 0.0) {
        singal_im = 0.5;
      } else {
        singal_im = -0.5;
      }

      ans_c63->re = (ar * b_singal_re + singal_re * singal_im) / b_singal_im;
      ans_c63->im = (singal_re * b_singal_re - ar * singal_im) / b_singal_im;
    } else {
      b_singal_re = mean_c42_re / b_mean_c21_im;
      singal_im = b_mean_c21_im + b_singal_re * mean_c42_re;
      ans_c63->re = (b_singal_re * ar + singal_re) / singal_im;
      ans_c63->im = (b_singal_re * singal_re - ar) / singal_im;
    }
  }

  if (c_x_im == 0.0) {
    x_re = c_x_re / 25000.0;
    x_im = 0.0;
  } else if (c_x_re == 0.0) {
    x_re = 0.0;
    x_im = c_x_im / 25000.0;
  } else {
    x_re = c_x_re / 25000.0;
    x_im = c_x_im / 25000.0;
  }

  if (b_x_im == 0.0) {
    b_x_re /= 25000.0;
    b_x_im = 0.0;
  } else if (b_x_re == 0.0) {
    b_x_re = 0.0;
    b_x_im /= 25000.0;
  } else {
    b_x_re /= 25000.0;
    b_x_im /= 25000.0;
  }

  b_re = 28.0 * mean_c20_re;
  im = 28.0 * mean_c20_im;
  re = 35.0 * mean_c40_re;
  singal_re_tmp = 35.0 * mean_c40_im;
  c_re = 420.0 * mean_c40_re;
  b_singal_im = 420.0 * mean_c40_im;
  singal_re = c_re * mean_c20_re - b_singal_im * mean_c20_im;
  b_singal_im = c_re * mean_c20_im + b_singal_im * mean_c20_re;
  c_re = 630.0 * mean_c20_re;
  b_singal_re = 630.0 * mean_c20_im;
  singal_im = c_re * mean_c20_re - b_singal_re * mean_c20_im;
  b_singal_re = c_re * mean_c20_im + b_singal_re * mean_c20_re;
  c_re = singal_im * mean_c20_re - b_singal_re * mean_c20_im;
  b_singal_re = singal_im * mean_c20_im + b_singal_re * mean_c20_re;
  b_mean_c21_re = mean_c21_re * mean_c21_re - mean_c21_im * mean_c21_im;
  b_mean_c21_im = mean_c21_re * mean_c21_im + mean_c21_im * mean_c21_re;
  mean_c42_re = b_mean_c21_re * mean_c21_re - b_mean_c21_im * mean_c21_im;
  b_mean_c21_im = b_mean_c21_re * mean_c21_im + b_mean_c21_im * mean_c21_re;
  b_mean_c21_re = mean_c42_re * mean_c21_re - b_mean_c21_im * mean_c21_im;
  mean_c21_im = mean_c42_re * mean_c21_im + b_mean_c21_im * mean_c21_re;
  ar = (((x_re - (b_re * b_x_re - im * b_x_im)) - (re * mean_c40_re -
          singal_re_tmp * mean_c40_im)) + (singal_re * mean_c20_re - b_singal_im
         * mean_c20_im)) - (c_re * mean_c20_re - b_singal_re * mean_c20_im);
  singal_re = (((x_im - (b_re * b_x_im + im * b_x_re)) - (re * mean_c40_im +
    singal_re_tmp * mean_c40_re)) + (singal_re * mean_c20_im + b_singal_im *
    mean_c20_re)) - (c_re * mean_c20_im + b_singal_re * mean_c20_re);
  if (mean_c21_im == 0.0) {
    if (singal_re == 0.0) {
      ans_c80->re = ar / b_mean_c21_re;
      ans_c80->im = 0.0;
    } else if (ar == 0.0) {
      ans_c80->re = 0.0;
      ans_c80->im = singal_re / b_mean_c21_re;
    } else {
      ans_c80->re = ar / b_mean_c21_re;
      ans_c80->im = singal_re / b_mean_c21_re;
    }
  } else if (b_mean_c21_re == 0.0) {
    if (ar == 0.0) {
      ans_c80->re = singal_re / mean_c21_im;
      ans_c80->im = 0.0;
    } else if (singal_re == 0.0) {
      ans_c80->re = 0.0;
      ans_c80->im = -(ar / mean_c21_im);
    } else {
      ans_c80->re = singal_re / mean_c21_im;
      ans_c80->im = -(ar / mean_c21_im);
    }
  } else {
    b_singal_im = std::abs(b_mean_c21_re);
    singal_im = std::abs(mean_c21_im);
    if (b_singal_im > singal_im) {
      b_singal_re = mean_c21_im / b_mean_c21_re;
      singal_im = b_mean_c21_re + b_singal_re * mean_c21_im;
      ans_c80->re = (ar + b_singal_re * singal_re) / singal_im;
      ans_c80->im = (singal_re - b_singal_re * ar) / singal_im;
    } else if (singal_im == b_singal_im) {
      if (b_mean_c21_re > 0.0) {
        b_singal_re = 0.5;
      } else {
        b_singal_re = -0.5;
      }

      if (mean_c21_im > 0.0) {
        singal_im = 0.5;
      } else {
        singal_im = -0.5;
      }

      ans_c80->re = (ar * b_singal_re + singal_re * singal_im) / b_singal_im;
      ans_c80->im = (singal_re * b_singal_re - ar * singal_im) / b_singal_im;
    } else {
      b_singal_re = b_mean_c21_re / mean_c21_im;
      singal_im = mean_c21_im + b_singal_re * b_mean_c21_re;
      ans_c80->re = (b_singal_re * ar + singal_re) / singal_im;
      ans_c80->im = (b_singal_re * singal_re - ar) / singal_im;
    }
  }

  //         ans_c84 =  c84_clu/((mean_c21-P_noise)*(mean_c21-P_noise)*(mean_c21-P_noise)*(mean_c21-P_noise)); 
}

//
// File trailer for MC_cumulants1ccode.cpp
//
// [EOF]
//
