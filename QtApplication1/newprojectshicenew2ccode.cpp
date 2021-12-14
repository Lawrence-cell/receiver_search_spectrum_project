//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: newprojectshicenew2ccode.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "newprojectshicenew2ccode.h"
#include "CarrierSynchronizer.h"
#include "CoarseFrequencyCompensator.h"
#include "FIRDecimator.h"
#include "MC_cumulants1ccode.h"
#include "RaisedCosineReceiveFilter.h"
#include "SymbolSynchronizer.h"
#include "detect_recognize_data.h"
#include "detect_recognize_rtwutil.h"
#include "relop.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
//
// Arguments    : const creal_T data[100000]
// Return Type  : double
//
double newprojectshicenew2ccode(const creal_T data[100000])
{
  static coder::comm::RaisedCosineReceiveFilter rcrFilt;
  static coder::comm::SymbolSynchronizer symsync;
  static creal_T data11[100000];
  static creal_T data1[50000];
  static creal_T compensatedData[25000];
  static creal_T data10[25000];
  static creal_T varargin_1[25000];
  coder::comm::CarrierSynchronizer csync;
  coder::comm::CarrierSynchronizer csync2;
  coder::comm::CoarseFrequencyCompensator freqComp;
  coder::comm::CoarseFrequencyCompensator freqComp2;
  coder::array<creal_T, 1U> b_data1;
  creal_T c42_ams;
  creal_T c63_ams;
  creal_T data11_tmp;
  creal_T data_mean;
  creal_T unusedU2;
  creal_T unusedU3;
  double F1;
  double F2;
  double ai;
  double bim;
  double brm;
  double modulation;
  double r;
  double re;
  int i;
  rcrFilt._pobj0.matlabCodegenIsDeleted = true;
  rcrFilt.matlabCodegenIsDeleted = true;
  symsync.matlabCodegenIsDeleted = true;
  freqComp.matlabCodegenIsDeleted = true;
  freqComp2.matlabCodegenIsDeleted = true;

  // 增加16psk版本
  rcrFilt.init();
  symsync.init();
  data_mean = data[0];
  for (i = 0; i < 99999; i++) {
    data_mean.re += data[i + 1].re;
    data_mean.im += data[i + 1].im;
  }

  if (data_mean.im == 0.0) {
    re = data_mean.re / 100000.0;
    F2 = 0.0;
  } else if (data_mean.re == 0.0) {
    re = 0.0;
    F2 = data_mean.im / 100000.0;
  } else {
    re = data_mean.re / 100000.0;
    F2 = data_mean.im / 100000.0;
  }

  for (i = 0; i < 100000; i++) {
    data11[i].re = data[i].re - re;
    data11[i].im = data[i].im - F2;
  }

  data_mean = data11[0];
  for (i = 0; i < 99999; i++) {
    boolean_T p;
    data11_tmp = data11[i + 1];
    p = coder::internal::relop(data_mean, data11_tmp);
    if (p) {
      data_mean = data11_tmp;
    }
  }

  for (i = 0; i < 100000; i++) {
    r = data11[i].re;
    ai = data11[i].im;
    if (data_mean.im == 0.0) {
      if (ai == 0.0) {
        re = r / data_mean.re;
        F2 = 0.0;
      } else if (r == 0.0) {
        re = 0.0;
        F2 = ai / data_mean.re;
      } else {
        re = r / data_mean.re;
        F2 = ai / data_mean.re;
      }
    } else if (data_mean.re == 0.0) {
      if (r == 0.0) {
        re = ai / data_mean.im;
        F2 = 0.0;
      } else if (ai == 0.0) {
        re = 0.0;
        F2 = -(r / data_mean.im);
      } else {
        re = ai / data_mean.im;
        F2 = -(r / data_mean.im);
      }
    } else {
      brm = std::abs(data_mean.re);
      bim = std::abs(data_mean.im);
      if (brm > bim) {
        bim = data_mean.im / data_mean.re;
        F2 = data_mean.re + bim * data_mean.im;
        re = (r + bim * ai) / F2;
        F2 = (ai - bim * r) / F2;
      } else if (bim == brm) {
        if (data_mean.re > 0.0) {
          bim = 0.5;
        } else {
          bim = -0.5;
        }

        if (data_mean.im > 0.0) {
          F2 = 0.5;
        } else {
          F2 = -0.5;
        }

        re = (r * bim + ai * F2) / brm;
        F2 = (ai * bim - r * F2) / brm;
      } else {
        bim = data_mean.re / data_mean.im;
        F2 = data_mean.im + bim * data_mean.re;
        re = (bim * r + ai) / F2;
        F2 = (bim * ai - r) / F2;
      }
    }

    data11[i].re = re;
    data11[i].im = F2;
  }

  rcrFilt.step(data11, data1);
  symsync.step(data1, b_data1);
  std::memset(&data10[0], 0, 25000U * sizeof(creal_T));
  if (b_data1.size(0) < 25000) {
    int loop_ub;
    if (1 > b_data1.size(0)) {
      loop_ub = 0;
    } else {
      loop_ub = b_data1.size(0);
    }

    for (i = 0; i < loop_ub; i++) {
      data10[i] = b_data1[i];
    }

    loop_ub = 25000 - b_data1.size(0);
    for (i = 0; i < loop_ub; i++) {
      data10[b_data1.size(0) + i].re = 0.0;
      data10[b_data1.size(0) + i].im = 0.0;
    }
  } else {
    for (i = 0; i < 25000; i++) {
      data10[i] = b_data1[i];
    }
  }

  freqComp.init();
  freqComp2.b_init();
  freqComp.step(data10, varargin_1);
  csync.init();
  csync2.init();
  csync.step(varargin_1, compensatedData);

  // [c20_ams, c40_ams, c42_ams, c63_ams,c63_test,c80_ams]
  MC_cumulants1ccode(compensatedData, &data11_tmp, &data_mean, &c42_ams,
                     &c63_ams, &unusedU2, &unusedU3);
  F1 = rt_hypotd_snf(data_mean.re, data_mean.im) / rt_hypotd_snf(c42_ams.re,
    c42_ams.im);
  if ((c42_ams.im == 0.0) && (c42_ams.re >= 0.0)) {
    data_mean.re = rt_powd_snf(c42_ams.re, 3.0);
    data_mean.im = 0.0;
  } else if (c42_ams.re == 0.0) {
    data_mean.re = 0.0;
    data_mean.im = -rt_powd_snf(c42_ams.im, 3.0);
  } else {
    if (c42_ams.im == 0.0) {
      if (c42_ams.re < 0.0) {
        c42_ams.re = std::log(std::abs(c42_ams.re));
        c42_ams.im = 3.1415926535897931;
      } else {
        c42_ams.re = std::log(c42_ams.re);
        c42_ams.im = 0.0;
      }
    } else if ((std::abs(c42_ams.re) > 8.9884656743115785E+307) || (std::abs
                (c42_ams.im) > 8.9884656743115785E+307)) {
      F2 = c42_ams.re;
      c42_ams.re = std::log(rt_hypotd_snf(c42_ams.re / 2.0, c42_ams.im / 2.0)) +
        0.69314718055994529;
      c42_ams.im = rt_atan2d_snf(c42_ams.im, F2);
    } else {
      F2 = c42_ams.re;
      c42_ams.re = std::log(rt_hypotd_snf(c42_ams.re, c42_ams.im));
      c42_ams.im = rt_atan2d_snf(c42_ams.im, F2);
    }

    data_mean.re = 3.0 * c42_ams.re;
    data_mean.im = 3.0 * c42_ams.im;
    if (data_mean.im == 0.0) {
      F2 = data_mean.re;
      data_mean.re = std::exp(F2);
      data_mean.im = 0.0;
    } else if (rtIsInf(data_mean.im) && rtIsInf(data_mean.re) && (data_mean.re <
                0.0)) {
      data_mean.re = 0.0;
      data_mean.im = 0.0;
    } else {
      r = std::exp(data_mean.re / 2.0);
      F2 = data_mean.im;
      ai = data_mean.im;
      data_mean.re = r * (r * std::cos(F2));
      data_mean.im = r * (r * std::sin(ai));
    }
  }

  ai = c63_ams.re * c63_ams.re - c63_ams.im * c63_ams.im;
  F2 = c63_ams.re * c63_ams.im;
  r = F2 + F2;
  if (data_mean.im == 0.0) {
    if (r == 0.0) {
      re = ai / data_mean.re;
      F2 = 0.0;
    } else if (ai == 0.0) {
      re = 0.0;
      F2 = r / data_mean.re;
    } else {
      re = ai / data_mean.re;
      F2 = r / data_mean.re;
    }
  } else if (data_mean.re == 0.0) {
    if (ai == 0.0) {
      re = r / data_mean.im;
      F2 = 0.0;
    } else if (r == 0.0) {
      re = 0.0;
      F2 = -(ai / data_mean.im);
    } else {
      re = r / data_mean.im;
      F2 = -(ai / data_mean.im);
    }
  } else {
    brm = std::abs(data_mean.re);
    bim = std::abs(data_mean.im);
    if (brm > bim) {
      bim = data_mean.im / data_mean.re;
      F2 = data_mean.re + bim * data_mean.im;
      re = (ai + bim * r) / F2;
      F2 = (r - bim * ai) / F2;
    } else if (bim == brm) {
      if (data_mean.re > 0.0) {
        bim = 0.5;
      } else {
        bim = -0.5;
      }

      if (data_mean.im > 0.0) {
        F2 = 0.5;
      } else {
        F2 = -0.5;
      }

      re = (ai * bim + r * F2) / brm;
      F2 = (r * bim - ai * F2) / brm;
    } else {
      bim = data_mean.re / data_mean.im;
      F2 = data_mean.im + bim * data_mean.re;
      re = (bim * ai + r) / F2;
      F2 = (bim * r - ai) / F2;
    }
  }

  F2 = rt_hypotd_snf(re, F2);

  //           F3=abs((c80_ams)/(c42_ams^2));
  if ((0.1 < rt_hypotd_snf(data11_tmp.re, data11_tmp.im)) || (F2 > 26.0)) {
    //              modulation = 'BPSK';
    modulation = 1.0;
  } else if (F2 < 14.5) {
    // 容易造成误判，QPSK可能会被判到QAM类里，但是如果降低门限，将16APSK划入PSK类里，利用F1可以将16APSK和8PSK划为一类 
    //          modulation2='QAM类(包括16APSK）';
    if (F1 < 0.04) {
      // 0.15改为0.03
      //          modulation='16APSK';
      modulation = 4.0;
    } else if (F1 < 0.3) {
      // 0.5改为0.05
      //              modulation='32QAM';
      modulation = 7.0;
    } else {
      //              modulation='16QAM';
      modulation = 6.0;
    }
  } else {
    //          modulation2='PSK类（包括OQPSK）';
    if ((F1 < 0.05) && (F2 > 15.0)) {
      // F1 0.5改为0.05
      freqComp2.step(data10, varargin_1, (&F2));
      csync2.SystemCore_step(varargin_1, compensatedData);
      MC_cumulants1ccode(compensatedData, &data_mean, &unusedU2, &c42_ams,
                         &unusedU3, &c63_ams, &data11_tmp);

      //          c20QPSK = c20QPSK+c40_QPSK;
      //          F11=abs(c40_ams)/abs(c42_ams);
      //          F22=abs((c63_ams^2)/(c42_ams^3));
      r = c42_ams.re * c42_ams.re - c42_ams.im * c42_ams.im;
      F2 = c42_ams.re * c42_ams.im;
      F2 += F2;
      if (F2 == 0.0) {
        if (data11_tmp.im == 0.0) {
          data_mean.re = data11_tmp.re / r;
          data_mean.im = 0.0;
        } else if (data11_tmp.re == 0.0) {
          data_mean.re = 0.0;
          data_mean.im = data11_tmp.im / r;
        } else {
          data_mean.re = data11_tmp.re / r;
          data_mean.im = data11_tmp.im / r;
        }
      } else if (r == 0.0) {
        if (data11_tmp.re == 0.0) {
          data_mean.re = data11_tmp.im / F2;
          data_mean.im = 0.0;
        } else if (data11_tmp.im == 0.0) {
          data_mean.re = 0.0;
          data_mean.im = -(data11_tmp.re / F2);
        } else {
          data_mean.re = data11_tmp.im / F2;
          data_mean.im = -(data11_tmp.re / F2);
        }
      } else {
        brm = std::abs(r);
        bim = std::abs(F2);
        if (brm > bim) {
          bim = F2 / r;
          F2 = r + bim * F2;
          data_mean.re = (data11_tmp.re + bim * data11_tmp.im) / F2;
          data_mean.im = (data11_tmp.im - bim * data11_tmp.re) / F2;
        } else if (bim == brm) {
          if (r > 0.0) {
            bim = 0.5;
          } else {
            bim = -0.5;
          }

          if (F2 > 0.0) {
            F2 = 0.5;
          } else {
            F2 = -0.5;
          }

          data_mean.re = (data11_tmp.re * bim + data11_tmp.im * F2) / brm;
          data_mean.im = (data11_tmp.im * bim - data11_tmp.re * F2) / brm;
        } else {
          bim = r / F2;
          F2 += bim * r;
          data_mean.re = (bim * data11_tmp.re + data11_tmp.im) / F2;
          data_mean.im = (bim * data11_tmp.im - data11_tmp.re) / F2;
        }
      }

      if (rt_hypotd_snf(data_mean.re, data_mean.im) > 0.2) {
        //      modulation='8PSK';
        modulation = 3.0;
      } else {
        //          modulation='16PSK';
        modulation = 12.0;
      }
    } else if ((F1 < 0.05) && (F2 < 15.0)) {
      // 增加16APSK准确性
      //      modulation='16APSK';
      modulation = 4.0;
    } else {
      //  modulation='QPSK';
      modulation = 2.0;
    }
  }

  freqComp2.matlabCodegenDestructor();
  freqComp.matlabCodegenDestructor();
  symsync.matlabCodegenDestructor();
  rcrFilt.matlabCodegenDestructor();
  rcrFilt._pobj0.matlabCodegenDestructor();
  return modulation;
}

//
// File trailer for newprojectshicenew2ccode.cpp
//
// [EOF]
//
