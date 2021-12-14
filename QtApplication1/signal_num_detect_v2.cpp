//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: signal_num_detect_v2.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "signal_num_detect_v2.h"
#include "detect_recognize_data.h"
#include "detect_recognize_rtwutil.h"
#include "fft.h"
#include "fftshift.h"
#include "relop.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <string.h>




#define TH4 0.05
#define TH8 0.12
#define TH10 0.25

// Function Definitions
//
// Arguments    : creal_T data[200000]
//                double *flag
//                double FX[3]
// Return Type  : void
//
void signal_num_detect_v2(creal_T data[200000], double *flag, double FX[3],double Tao[80000])
{
  static creal_T signal2[80000];
  static creal_T spectrum[80000];
  static double tao[80000];
  creal_T b_signal2[400];
  creal_T dcv[400];
  creal_T data_mean;
  double maxval[200];
  double ai;
  double ar;
  double b_p;
  double brm;
  double im;
  double re;
  int b_i;
  int i;
  int idx;
  int k;
  boolean_T p;
  data_mean = data[0];
  for (k = 0; k < 199999; k++) {
    data_mean.re += data[k + 1].re;
    data_mean.im += data[k + 1].im;
  }

  if (data_mean.im == 0.0) {
    re = data_mean.re / 200000.0;
    im = 0.0;
  } else if (data_mean.re == 0.0) {
    re = 0.0;
    im = data_mean.im / 200000.0;
  } else {
    re = data_mean.re / 200000.0;
    im = data_mean.im / 200000.0;
  }

  for (i = 0; i < 200000; i++) {
    data[i].re -= re;
    data[i].im -= im;
  }

  data_mean = data[0];
  for (k = 0; k < 199999; k++) {
    creal_T data_tmp;
    data_tmp = data[k + 1];
    p = coder::internal::relop(data_mean, data_tmp);
    if (p) {
      data_mean = data_tmp;
    }
  }

  for (i = 0; i < 200000; i++) {
    ar = data[i].re;
    ai = data[i].im;
    if (data_mean.im == 0.0) {
      if (ai == 0.0) {
        re = ar / data_mean.re;
        im = 0.0;
      } else if (ar == 0.0) {
        re = 0.0;
        im = ai / data_mean.re;
      } else {
        re = ar / data_mean.re;
        im = ai / data_mean.re;
      }
    } else if (data_mean.re == 0.0) {
      if (ar == 0.0) {
        re = ai / data_mean.im;
        im = 0.0;
      } else if (ai == 0.0) {
        re = 0.0;
        im = -(ar / data_mean.im);
      } else {
        re = ai / data_mean.im;
        im = -(ar / data_mean.im);
      }
    } else {
      brm = std::abs(data_mean.re);
      im = std::abs(data_mean.im);
      if (brm > im) {
        im = data_mean.im / data_mean.re;
        b_p = data_mean.re + im * data_mean.im;
        re = (ar + im * ai) / b_p;
        im = (ai - im * ar) / b_p;
      } else if (im == brm) {
        if (data_mean.re > 0.0) {
          im = 0.5;
        } else {
          im = -0.5;
        }

        if (data_mean.im > 0.0) {
          b_p = 0.5;
        } else {
          b_p = -0.5;
        }

        re = (ar * im + ai * b_p) / brm;
        im = (ai * im - ar * b_p) / brm;
      } else {
        im = data_mean.re / data_mean.im;
        b_p = data_mean.im + im * data_mean.re;
        re = (im * ar + ai) / b_p;
        im = (im * ai - ar) / b_p;
      }
    }

    data[i].re = re;
    data[i].im = im;
  }

  for (idx = 0; idx < 200; idx++) {
    for (b_i = 0; b_i < 400; b_i++) {
      signal2[idx + 200 * b_i] = data[400 * idx + b_i];
    }
  }

  for (b_i = 0; b_i < 200; b_i++) {
    for (i = 0; i < 400; i++) {
      b_signal2[i] = signal2[b_i + 200 * i];
    }

    coder::fft(b_signal2, dcv);
    for (i = 0; i < 400; i++) {
      spectrum[b_i + 200 * i] = dcv[i];
    }

    coder::fftshift(dcv);
    for (i = 0; i < 400; i++) {
      spectrum[b_i + 200 * i] = dcv[i];
    }
  }

  std::memset(&signal2[0], 0, 80000U * sizeof(creal_T));
  for (b_i = 0; b_i < 200; b_i++) {
    for (idx = 0; idx < 400; idx++) {
      for (k = 0; k < 200; k++) {
        int spectrum_re_tmp;
        im = (2.0 * static_cast<double>(k) + -200.0) / 2.0;
        b_p = static_cast<double>(idx) - im;
        if (b_p == 0.0) {
          brm = 0.0;
        } else {
          brm = std::fmod(b_p, 400.0);
          if (brm == 0.0) {
            brm = 0.0;
          } else {
            if (b_p < 0.0) {
              brm += 400.0;
            }
          }
        }

        b_p = static_cast<double>(idx) + im;
        if (b_p == 0.0) {
          im = 0.0;
        } else {
          im = std::fmod(b_p, 400.0);
          if (im == 0.0) {
            im = 0.0;
          } else {
            if (b_p < 0.0) {
              im += 400.0;
            }
          }
        }

        spectrum_re_tmp = b_i + 200 * (static_cast<int>(im + 1.0) - 1);
        im = spectrum[spectrum_re_tmp].re;
        b_p = -spectrum[spectrum_re_tmp].im;
        spectrum_re_tmp = b_i + 200 * (static_cast<int>(brm + 1.0) - 1);
        i = idx + 400 * k;
        signal2[i].re += spectrum[spectrum_re_tmp].re * im -
          spectrum[spectrum_re_tmp].im * b_p;
        signal2[i].im += spectrum[spectrum_re_tmp].re * b_p +
          spectrum[spectrum_re_tmp].im * im;
      }
    }
  }

  for (k = 0; k < 80000; k++) {
    ar = signal2[k].re;
    ai = signal2[k].im;
    if (ai == 0.0) {
      re = ar / 80000.0;
      im = 0.0;
    } else if (ar == 0.0) {
      re = 0.0;
      im = ai / 80000.0;
    } else {
      re = ar / 80000.0;
      im = ai / 80000.0;
    }

    signal2[k].re = re;
    signal2[k].im = im;
    tao[k] = rt_hypotd_snf(re, im);
  }

  for (idx = 0; idx < 200; idx++) {
    maxval[idx] = tao[400 * idx];
    for (b_i = 0; b_i < 399; b_i++) {
      im = tao[(b_i + 400 * idx) + 1];
      if (rtIsNaN(im)) {
        p = false;
      } else if (rtIsNaN(maxval[idx])) {
        p = true;
      } else {
        p = (maxval[idx] < im);
      }

      if (p) {
        maxval[idx] = im;
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
    while ((!exitg1) && (k <= 200)) {
      if (!rtIsNaN(maxval[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    b_p = maxval[0];
  } else {
    b_p = maxval[idx - 1];
    i = idx + 1;
    for (k = i; k < 201; k++) {
      im = maxval[k - 1];
      if (b_p < im) {
        b_p = im;
      }
    }
  }

  for (i = 0; i < 80000; i++) {
    tao[i] /= b_p;
  }

  // 4
  // 8
  // 10
  FX[0] = tao[60200];

  // 4
  FX[1] = tao[50200];

  // 8
  FX[2] = tao[48200];

  // 10
  for (i = 0; i < 80000; i++)
  {
      Tao[i] = tao[i];
  }
  if (((FX[2] >= TH10) && (FX[0] >= TH4) && (FX[1] < TH8)) ||
      ((FX[1] >= TH8) && (FX[0] >= TH4) && (FX[2] < TH10)) ||
      ((FX[2] >= TH10) && (FX[1] >= TH8) && (FX[0] < TH4))) {
      *flag = 2.0;
  }
  else if ((FX[2] >= TH10) && (FX[0] >= TH4) &&
      (FX[1] >= TH8)) {
      *flag = 3.0;
  }
  else if ((FX[2] < TH10) && (FX[0] < TH4) &&
      (FX[1] < TH8)) {
      *flag = 0.0;
  }
  else {
      *flag = 1.0;
  }
}

//
// File trailer for signal_num_detect_v2.cpp
//
// [EOF]
//
