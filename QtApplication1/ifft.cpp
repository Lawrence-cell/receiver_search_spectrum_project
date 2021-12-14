//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ifft.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "ifft.h"
#include "FFTImplementationCallback.h"
#include "detect_recognize_data.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions
//
// Arguments    : const creal_T x[100000]
//                creal_T y[100000]
// Return Type  : void
//
namespace coder
{
  void ifft(const creal_T x[100000], creal_T y[100000])
  {
    static creal_T b_fv[262144];
    static creal_T fv[262144];
    static creal_T wwc[199999];
    static double costab[131073];
    static double sintab[131073];
    static double sintabinv[131073];
    double d;
    double d1;
    double im;
    double nt_im;
    double nt_re;
    int idx;
    int k;
    int rt;
    internal::FFTImplementationCallback::generate_twiddle_tables((costab),
      (sintab), (sintabinv));
    idx = 99998;
    rt = 0;
    wwc[99999].re = 1.0;
    wwc[99999].im = 0.0;
    for (k = 0; k < 99999; k++) {
      int b_y;
      b_y = ((k + 1) << 1) - 1;
      if (200000 - rt <= b_y) {
        rt = (b_y + rt) - 200000;
      } else {
        rt += b_y;
      }

      nt_im = 3.1415926535897931 * static_cast<double>(rt) / 100000.0;
      if (nt_im == 0.0) {
        nt_re = 1.0;
        nt_im = 0.0;
      } else {
        nt_re = std::cos(nt_im);
        nt_im = std::sin(nt_im);
      }

      wwc[idx].re = nt_re;
      wwc[idx].im = -nt_im;
      idx--;
    }

    idx = 0;
    for (k = 99998; k >= 0; k--) {
      wwc[k + 100000] = wwc[idx];
      idx++;
    }

    idx = 0;
    for (k = 0; k < 100000; k++) {
      nt_re = wwc[k + 99999].re;
      nt_im = wwc[k + 99999].im;
      y[k].re = nt_re * x[idx].re + nt_im * x[idx].im;
      y[k].im = nt_re * x[idx].im - nt_im * x[idx].re;
      idx++;
    }

    internal::FFTImplementationCallback::c_r2br_r2dit_trig_impl((y), (costab),
      (sintab), (fv));
    internal::FFTImplementationCallback::c_r2br_r2dit_trig((wwc), (costab),
      (sintab), (b_fv));
    for (idx = 0; idx < 262144; idx++) {
      nt_re = fv[idx].re;
      nt_im = fv[idx].im;
      d = b_fv[idx].im;
      d1 = b_fv[idx].re;
      im = nt_re * d + nt_im * d1;
      d1 = nt_re * d1 - nt_im * d;
      b_fv[idx].re = d1;
      b_fv[idx].im = im;
    }

    internal::FFTImplementationCallback::d_r2br_r2dit_trig((b_fv), (costab),
      (sintabinv), (fv));
    idx = 0;
    for (k = 0; k < 100000; k++) {
      nt_re = wwc[k + 99999].re;
      nt_im = wwc[k + 99999].im;
      d = fv[k + 99999].re;
      d1 = fv[k + 99999].im;
      y[idx].re = nt_re * d + nt_im * d1;
      y[idx].im = nt_re * d1 - nt_im * d;
      nt_re = y[idx].re;
      nt_im = y[idx].im;
      if (nt_im == 0.0) {
        nt_re /= 100000.0;
        im = 0.0;
      } else if (nt_re == 0.0) {
        nt_re = 0.0;
        im = nt_im / 100000.0;
      } else {
        nt_re /= 100000.0;
        im = nt_im / 100000.0;
      }

      y[idx].re = nt_re;
      y[idx].im = im;
      idx++;
    }
  }
}

//
// File trailer for ifft.cpp
//
// [EOF]
//
