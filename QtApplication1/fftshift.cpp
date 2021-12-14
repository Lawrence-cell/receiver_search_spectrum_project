//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fftshift.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "fftshift.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
//
// Arguments    : creal_T x[200]
// Return Type  : void
//
namespace coder
{
  void b_fftshift(creal_T x[200])
  {
    int i2;
    i2 = 0;
    for (int i = 0; i < 1; i++) {
      int i1;
      i1 = i2;
      i2 += 199;
      for (int j = 0; j < 1; j++) {
        int ia;
        int ib;
        i1++;
        i2++;
        ia = i1 - 1;
        ib = i1 + 99;
        for (int k = 0; k < 100; k++) {
          double xtmp_im;
          double xtmp_re;
          xtmp_re = x[ia].re;
          xtmp_im = x[ia].im;
          x[ia] = x[ib];
          x[ib].re = xtmp_re;
          x[ib].im = xtmp_im;
          ia++;
          ib++;
        }
      }
    }
  }

  //
  // Arguments    : creal_T x[1024]
  // Return Type  : void
  //
  void c_fftshift(creal_T x[1024])
  {
    int i2;
    i2 = 0;
    for (int i = 0; i < 1; i++) {
      int i1;
      i1 = i2;
      i2 += 1023;
      for (int j = 0; j < 1; j++) {
        int ia;
        int ib;
        i1++;
        i2++;
        ia = i1 - 1;
        ib = i1 + 511;
        for (int k = 0; k < 512; k++) {
          double xtmp_im;
          double xtmp_re;
          xtmp_re = x[ia].re;
          xtmp_im = x[ia].im;
          x[ia] = x[ib];
          x[ib].re = xtmp_re;
          x[ib].im = xtmp_im;
          ia++;
          ib++;
        }
      }
    }
  }

  //
  // Arguments    : creal_T x[400]
  // Return Type  : void
  //
  void fftshift(creal_T x[400])
  {
    int i2;
    i2 = 0;
    for (int i = 0; i < 1; i++) {
      int i1;
      i1 = i2;
      i2 += 399;
      for (int j = 0; j < 1; j++) {
        int ia;
        int ib;
        i1++;
        i2++;
        ia = i1 - 1;
        ib = i1 + 199;
        for (int k = 0; k < 200; k++) {
          double xtmp_im;
          double xtmp_re;
          xtmp_re = x[ia].re;
          xtmp_im = x[ia].im;
          x[ia] = x[ib];
          x[ib].re = xtmp_re;
          x[ib].im = xtmp_im;
          ia++;
          ib++;
        }
      }
    }
  }
}

//
// File trailer for fftshift.cpp
//
// [EOF]
//
