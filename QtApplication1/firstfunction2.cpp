//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: firstfunction2.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "firstfunction2.h"
#include "CACfig_v4.h"
#include "Ymaxccode.h"
#include "detect_recognize_data.h"
#include "detect_recognize_rtwutil.h"
#include "fft.h"
#include "fftshift.h"
#include "findpeaks.h"
#include "hilbert.h"
#include "newprojectshicenew2ccode.h"
#include "relop.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
//
// Arguments    : const creal_T data[200000]
// Return Type  : double
//

double firstfunction2(const creal_T data[200000])
{
  static creal_T b_data[200000];
  static creal_T datayw[100000];
  static creal_T w[100000];
  static creal_T scf[20000];
  static creal_T signal2[10000];
  static creal_T spectrum[10000];
  static double A4_tmp[100000];
  static double Acn[100000];
  static double t[100000];
  static double b_t[20480];
  creal_T b_signal2[200];
  creal_T dcv[200];
  creal_T data_mean;
  double scf1[10000];
  double locs_data[100];
  double maxval[100];
  double unusedU0_data[100];
  double AtestYmax;
  double a42;
  double brm;
  double d;
  double kd;
  double modulation2;
  double re;
  int locs_size[1];
  int unusedU0_size[1];
  int i;
  int idx;
  int k;
  boolean_T p;

  //  目前较为稳定的版本，但是6db信噪比下fsk和数字还是会误判，考虑下一个版本更改判决策略 
  // 更新策略，ymax先判决2fsk，再判4fsk和其他，如果不行，还是plus2版本最稳定
  // 10dB，调制方式识别：具备包含BPSK、QPSK、OQPSK、8PSK、16PSK、2FSK、4FSK、8FSK、16FSK、16QAM、32QAM、16APSK等调制方式识别能力，调制方式识别准确度≥90% 
  // 采样频率
  // 载波频率
  // 符号数
  // 采样时间间隔
  t[0] = 0.0;
  t[99999] = 4.99995;
  for (k = 0; k < 49998; k++) {
    kd = (static_cast<double>(k) + 1.0) * 5.0E-5;
    t[k + 1] = kd;
    t[99998 - k] = 4.99995 - kd;
  }

  t[49999] = 2.49995;
  t[50000] = 2.5;
  data_mean = data[0];
  for (k = 0; k < 99999; k++) {
    data_mean.re += data[k + 1].re;
    data_mean.im += data[k + 1].im;
  }

  if (data_mean.im == 0.0) {
    re = data_mean.re / 100000.0;
    kd = 0.0;
  } else if (data_mean.re == 0.0) {
    re = 0.0;
    kd = data_mean.im / 100000.0;
  } else {
    re = data_mean.re / 100000.0;
    kd = data_mean.im / 100000.0;
  }

  for (i = 0; i < 100000; i++) {
    datayw[i].re = data[i].re - re;
    datayw[i].im = data[i].im - kd;
  }

  data_mean = datayw[0];
  for (k = 0; k < 99999; k++) {
    creal_T datayw_tmp;
    datayw_tmp = datayw[k + 1];
    p = coder::internal::relop(data_mean, datayw_tmp);
    if (p) {
      data_mean = datayw_tmp;
    }
  }

  //      fcc=fc_count(ys,Fs);
  // [ampt1,phi1,freq1]=Inst_parameter(y,fcc,Fs);
  // 信号数据长度
  // %%%%希尔伯特变换法%%%%%
  for (k = 0; k < 100000; k++) {
    a42 = datayw[k].re;
    AtestYmax = datayw[k].im;
    if (data_mean.im == 0.0) {
      if (AtestYmax == 0.0) {
        re = a42 / data_mean.re;
        kd = 0.0;
      } else if (a42 == 0.0) {
        re = 0.0;
        kd = AtestYmax / data_mean.re;
      } else {
        re = a42 / data_mean.re;
        kd = AtestYmax / data_mean.re;
      }
    } else if (data_mean.re == 0.0) {
      if (a42 == 0.0) {
        re = AtestYmax / data_mean.im;
        kd = 0.0;
      } else if (AtestYmax == 0.0) {
        re = 0.0;
        kd = -(a42 / data_mean.im);
      } else {
        re = AtestYmax / data_mean.im;
        kd = -(a42 / data_mean.im);
      }
    } else {
      brm = std::abs(data_mean.re);
      kd = std::abs(data_mean.im);
      if (brm > kd) {
        kd = data_mean.im / data_mean.re;
        d = data_mean.re + kd * data_mean.im;
        re = (a42 + kd * AtestYmax) / d;
        kd = (AtestYmax - kd * a42) / d;
      } else if (kd == brm) {
        if (data_mean.re > 0.0) {
          kd = 0.5;
        } else {
          kd = -0.5;
        }

        if (data_mean.im > 0.0) {
          d = 0.5;
        } else {
          d = -0.5;
        }

        re = (a42 * kd + AtestYmax * d) / brm;
        kd = (AtestYmax * kd - a42 * d) / brm;
      } else {
        kd = data_mean.re / data_mean.im;
        d = data_mean.im + kd * data_mean.re;
        re = (kd * a42 + AtestYmax) / d;
        kd = (kd * AtestYmax - a42) / d;
      }
    }

    datayw[k].re = re;
    datayw[k].im = kd;
    brm = 12566.370614359172 * t[k];
    d = brm;
    brm = std::cos(brm);
    d = std::sin(d);
    brm = re * brm - kd * d;
    t[k] = brm;
  }

  coder::hilbert(t, w);

  // .*exp(-i.*2*pi*fc*t);
  for (idx = 0; idx < 100000; idx++) {
    brm = w[idx].re;
    d = w[idx].im;
    t[idx] = std::sqrt(brm * brm + d * d);
  }

  // a42=count_a42(ampt);%瞬时幅度紧致矩
  d = t[0];
  for (k = 0; k < 99999; k++) {
    d += t[k + 1];
  }

  kd = d / 100000.0;
  for (i = 0; i < 100000; i++) {
    brm = t[i] / kd - 1.0;
    d = brm * brm;
    A4_tmp[i] = d;
    brm *= d * brm;
    Acn[i] = brm;
  }

  d = Acn[0];
  kd = A4_tmp[0];
  for (k = 0; k < 99999; k++) {
    d += Acn[k + 1];
    kd += A4_tmp[k + 1];
  }

  kd /= 100000.0;
  a42 = d / 100000.0 / (kd * kd);
  AtestYmax = Ymaxccode(t);

  //
  if (AtestYmax < 4.0) {
    // 更改a42为ymax判决
    //      modulation='2fsk';
    modulation2 = 8.0;
  } else {
    int b_i;

    // 采样频率
    // 载波频率
    //      fd=0.05*fs;    % fd,即Rs，是fsk的符号速率，fskmod部分使用，也就是freqsep，fsk峰值间隔与这个一致 
    //  fd1，循环谱认为设定的波特率，并不是符号速率，影响的是N1的分组，应用于实测的时候也可以固定,控制循环谱分辨率,影响搜索峰值间隔 
    // 每个符号的采样点数
    //      M=5120;%符号数
    // 采样时间间隔
    b_t[0] = 0.0;
    b_t[20479] = 1.02395;
    for (k = 0; k < 10238; k++) {
      kd = (static_cast<double>(k) + 1.0) * 5.0E-5;
      b_t[k + 1] = kd;
      b_t[20478 - k] = 1.02395 - kd;
    }

    b_t[10239] = 0.51195;
    b_t[10240] = 0.5119999999999999;

    //  FFT点数，决定scf精度分辨率精度，alfa轴N1/2, F轴 1/N1
    // 接收信号sample
    // 总采样点数/N1    N2 频谱平均次数
    //          y=yn.*exp(J*2*pi*fc*t);
    for (k = 0; k < 20480; k++) {
      b_t[k] = datayw[k].re * std::cos(0.0 * b_t[k]) - datayw[k].im * 0.0;
    }

    for (idx = 0; idx < 50; idx++) {
      for (b_i = 0; b_i < 200; b_i++) {
        i = idx + 50 * b_i;
        signal2[i].re = b_t[(200 * idx + b_i) + 100];
        signal2[i].im = 0.0;
      }
    }

    for (b_i = 0; b_i < 50; b_i++) {
      for (i = 0; i < 200; i++) {
        b_signal2[i] = signal2[b_i + 50 * i];
      }

      coder::b_fft(b_signal2, dcv);

      // 进行离散傅里叶变换
      for (i = 0; i < 200; i++) {
        spectrum[b_i + 50 * i] = dcv[i];
      }

      coder::b_fftshift(dcv);
      for (i = 0; i < 200; i++) {
        spectrum[b_i + 50 * i] = dcv[i];
      }

      // 将前半部分元素与后半部分元素交换
    }

    std::memset(&scf[0], 0, 20000U * sizeof(creal_T));

    // 100个点
    for (b_i = 0; b_i < 50; b_i++) {
      for (idx = 0; idx < 200; idx++) {
        //  f
        for (k = 0; k < 100; k++) {
          int spectrum_re_tmp;

          //  h 表示alfa下标
          // Circular shift
          // The index of a matrix starts at 1, but d is from 0 to N1-1, so d=d+1 
          // Circular shift
          kd = (2.0 * static_cast<double>(k) + -100.0) / 2.0;
          d = static_cast<double>(idx) - kd;
          if (d == 0.0) {
            brm = 0.0;
          } else {
            brm = std::fmod(d, 200.0);
            if (brm == 0.0) {
              brm = 0.0;
            } else {
              if (d < 0.0) {
                brm += 200.0;
              }
            }
          }

          d = static_cast<double>(idx) + kd;
          if (d == 0.0) {
            kd = 0.0;
          } else {
            kd = std::fmod(d, 200.0);
            if (kd == 0.0) {
              kd = 0.0;
            } else {
              if (d < 0.0) {
                kd += 200.0;
              }
            }
          }

          spectrum_re_tmp = b_i + 50 * (static_cast<int>(kd + 1.0) - 1);
          kd = spectrum[spectrum_re_tmp].re;
          d = -spectrum[spectrum_re_tmp].im;
          spectrum_re_tmp = b_i + 50 * (static_cast<int>(brm + 1.0) - 1);
          i = idx + 200 * k;
          scf[i].re += spectrum[spectrum_re_tmp].re * kd -
            spectrum[spectrum_re_tmp].im * d;
          scf[i].im += spectrum[spectrum_re_tmp].re * d +
            spectrum[spectrum_re_tmp].im * kd;
        }
      }
    }

    //      scf1=abs(scf);
    //      p=max(max(scf1));
    for (k = 0; k < 10000; k++) {
      data_mean = scf[(k % 100 + 200 * (k / 100)) + 100];
      scf1[k] = rt_hypotd_snf(data_mean.re, data_mean.im);
    }

    for (idx = 0; idx < 100; idx++) {
      maxval[idx] = scf1[100 * idx];
      for (b_i = 0; b_i < 99; b_i++) {
        brm = scf1[(b_i + 100 * idx) + 1];
        if (rtIsNaN(brm)) {
          p = false;
        } else if (rtIsNaN(maxval[idx])) {
          p = true;
        } else {
          p = (maxval[idx] < brm);
        }

        if (p) {
          maxval[idx] = brm;
        }
      }
    }

    if (!rtIsNaN(maxval[0])) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= 100)) {
        if (!rtIsNaN(maxval[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      kd = maxval[0];
    } else {
      kd = maxval[idx - 1];
      i = idx + 1;
      for (k = i; k < 101; k++) {
        brm = maxval[k - 1];
        if (kd < brm) {
          kd = brm;
        }
      }
    }

    for (i = 0; i < 100; i++) {
      maxval[i] = scf1[i + 5000] / kd;
    }

    coder::findpeaks(maxval, unusedU0_data, unusedU0_size, locs_data, locs_size);

    //      modulation2=0;
    //      modulation=0;
    if ((locs_size[0] == 2) && (AtestYmax < 11.0)) {
      std::memcpy(&b_data[0], &data[0], 200000U * sizeof(creal_T));
      kd = CACfig_v4(b_data);
      if (kd >= 30.0) {
        //              modulation='4fsk';
        modulation2 = 9.0;
      }
      else if (kd <= 3) {
          modulation2 = newprojectshicenew2ccode(*(creal_T(*)[100000]) & data[0]);
      }
      else {
        //              modulation='OQPSK';
        modulation2 = 5.0;
      }
    } else if ((a42 > 4.0) && (locs_size[0] == 4)) {
      //          modulation='8fsk';
      modulation2 = 10.0;
    } else if ((a42 > 4.0) && (locs_size[0] == 8)) {
      //          modulation='16fsk';
      modulation2 = 11.0;
    } else {
      std::memcpy(&b_data[0], &data[0], 200000U * sizeof(creal_T));
      kd = CACfig_v4(b_data);
      if (kd >= 80.0) {
        //              modulation='OQPSK';
        modulation2 = 5.0;
      } else {
        modulation2 = newprojectshicenew2ccode(*(creal_T (*)[100000])&data[0]);
      }
    }
  }

  return modulation2;
}

//
// File trailer for firstfunction2.cpp
//
// [EOF]
//
