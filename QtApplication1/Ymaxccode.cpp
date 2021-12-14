//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Ymaxccode.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "Ymaxccode.h"
#include "FFTImplementationCallback.h"
#include "detect_recognize_rtwutil.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const double ampt[100000]
// Return Type  : double
//
double Ymaxccode(const double ampt[100000])
{
  static creal_T dcv[100000];
  static double costab[131073];
  static double sintab[131073];
  static double sintabinv[131073];
  static double b_ampt[100000];
  coder::array<double, 2U> x;
  double Ymax;
  double ampt_mean;
  int idx;
  int k;
  ampt_mean = ampt[0];
  for (k = 0; k < 99999; k++) {
    ampt_mean += ampt[k + 1];
  }

  ampt_mean /= 100000.0;
  coder::internal::FFTImplementationCallback::generate_twiddle_tables((costab),
    (sintab), (sintabinv));
  for (idx = 0; idx < 100000; idx++) {
    b_ampt[idx] = ampt[idx] / ampt_mean - 1.0;
  }

  coder::internal::FFTImplementationCallback::dobluesteinfft((b_ampt), (costab),
    (sintab), (sintabinv), (dcv));
  x.set_size(1, 100000);
  for (k = 0; k < 100000; k++) {
    ampt_mean = rt_hypotd_snf(dcv[k].re, dcv[k].im);
    ampt_mean = ampt_mean * ampt_mean / 100000.0;
    b_ampt[k] = ampt_mean;
    x[k] = ampt_mean;
  }

  if (!rtIsNaN(x[0])) {
    idx = 1;
  } else {
    boolean_T exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k <= 100000)) {
      if (!rtIsNaN(x[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    Ymax = b_ampt[0];
  } else {
    Ymax = b_ampt[idx - 1];
    idx++;
    for (k = idx; k < 100001; k++) {
      ampt_mean = b_ampt[k - 1];
      if (Ymax < ampt_mean) {
        Ymax = ampt_mean;
      }
    }
  }

  return Ymax;
}

//
// File trailer for Ymaxccode.cpp
//
// [EOF]
//
