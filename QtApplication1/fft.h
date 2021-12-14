//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fft.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//
#ifndef FFT_H
#define FFT_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder
{
  void b_fft(const creal_T x[200], creal_T y[200]);
  void fft(const creal_T x[400], creal_T y[400]);
}

#endif

//
// File trailer for fft.h
//
// [EOF]
//
