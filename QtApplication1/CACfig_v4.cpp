//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CACfig_v4.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "CACfig_v4.h"
#include "detect_recognize_data.h"
#include "detect_recognize_rtwutil.h"
#include "relop.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
//
// Arguments    : creal_T data[200000]
// Return Type  : double
//
double CACfig_v4(creal_T data[200000])
{
  static creal_T J[200000];
  static creal_T tao[12000];
  creal_T data1;
  double b_tao[12000];
  double brm;
  double flag;
  double im;
  double re;
  double sgnbi;
  int idx;
  int k;
  flag = 0.0;
  data1 = data[0];
  for (k = 0; k < 199999; k++) {
    data1.re += data[k + 1].re;
    data1.im += data[k + 1].im;
  }

  if (data1.im == 0.0) {
    re = data1.re / 200000.0;
    im = 0.0;
  } else if (data1.re == 0.0) {
    re = 0.0;
    im = data1.im / 200000.0;
  } else {
    re = data1.re / 200000.0;
    im = data1.im / 200000.0;
  }

  for (idx = 0; idx < 200000; idx++) {
    data[idx].re -= re;
    data[idx].im -= im;
  }

  data1 = data[0];
  for (k = 0; k < 199999; k++) {
    creal_T data_tmp;
    boolean_T p;
    data_tmp = data[k + 1];
    p = coder::internal::relop(data1, data_tmp);
    if (p) {
      data1 = data_tmp;
    }
  }

  for (idx = 0; idx < 200000; idx++) {
    double ai;
    double ar;
    ar = data[idx].re;
    ai = data[idx].im;
    if (data1.im == 0.0) {
      if (ai == 0.0) {
        re = ar / data1.re;
        im = 0.0;
      } else if (ar == 0.0) {
        re = 0.0;
        im = ai / data1.re;
      } else {
        re = ar / data1.re;
        im = ai / data1.re;
      }
    } else if (data1.re == 0.0) {
      if (ar == 0.0) {
        re = ai / data1.im;
        im = 0.0;
      } else if (ai == 0.0) {
        re = 0.0;
        im = -(ar / data1.im);
      } else {
        re = ai / data1.im;
        im = -(ar / data1.im);
      }
    } else {
      brm = std::abs(data1.re);
      im = std::abs(data1.im);
      if (brm > im) {
        im = data1.im / data1.re;
        brm = data1.re + im * data1.im;
        re = (ar + im * ai) / brm;
        im = (ai - im * ar) / brm;
      } else if (im == brm) {
        if (data1.re > 0.0) {
          im = 0.5;
        } else {
          im = -0.5;
        }

        if (data1.im > 0.0) {
          sgnbi = 0.5;
        } else {
          sgnbi = -0.5;
        }

        re = (ar * im + ai * sgnbi) / brm;
        im = (ai * im - ar * sgnbi) / brm;
      } else {
        im = data1.re / data1.im;
        brm = data1.im + im * data1.re;
        re = (im * ar + ai) / brm;
        im = (im * ai - ar) / brm;
      }
    }

    data[idx].re = re;
    data[idx].im = im;
    J[idx].re = re * re - im * -im;
    J[idx].im = re * -im + im * re;
  }

  data1.re = 0.0;
  data1.im = 0.0;
  std::memset(&tao[0], 0, 12000U * sizeof(creal_T));
  for (idx = 0; idx < 600; idx++) {
    for (k = 0; k < 200000; k++) {
      im = 0.0016666666666666668 * (static_cast<double>(k) * ((static_cast<
        double>(idx) + -299.0) * -6.2831853071795862));
      if (im == 0.0) {
        brm = 1.0;
        im = 0.0;
      } else {
        brm = std::cos(im);
        im = std::sin(im);
      }

      re = J[k].re;
      sgnbi = J[k].im;
      data1.re += re * brm - sgnbi * im;
      data1.im += re * im + sgnbi * brm;
    }

    if (data1.im == 0.0) {
      tao[20 * idx].re = data1.re / 200000.0;
      tao[20 * idx].im = 0.0;
    } else if (data1.re == 0.0) {
      tao[20 * idx].re = 0.0;
      tao[20 * idx].im = data1.im / 200000.0;
    } else {
      tao[20 * idx].re = data1.re / 200000.0;
      tao[20 * idx].im = data1.im / 200000.0;
    }

    data1.re = 0.0;
    data1.im = 0.0;
  }

  for (k = 0; k < 12000; k++) {
    b_tao[k] = rt_hypotd_snf(tao[k].re, tao[k].im);
  }

  std::memset(&b_tao[5980], 0, 20U * sizeof(double));
  if (!rtIsNaN(b_tao[0])) {
    idx = 1;
  } else {
    boolean_T exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k <= 600)) {
      if (!rtIsNaN(b_tao[20 * (k - 1)])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    im = b_tao[0];
  } else {
    im = b_tao[20 * (idx - 1)];
    idx++;
    for (k = idx; k < 601; k++) {
      re = b_tao[20 * (k - 1)];
      if (im < re) {
        im = re;
      }
    }
  }

  for (idx = 0; idx < 12000; idx++) {
    b_tao[idx] /= im;
  }

  for (k = 0; k < 300; k++) {
    if (b_tao[20 * (k + 300)] > 0.17) {
      flag++;
    }
  }

  return flag;
}

//
// File trailer for CACfig_v4.cpp
//
// [EOF]
//
