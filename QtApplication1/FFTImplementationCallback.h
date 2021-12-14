//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FFTImplementationCallback.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//
#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder
{
  namespace internal
  {
    class FFTImplementationCallback
    {
     public:
      static void r2br_r2dit_trig_impl(const creal_T x[1024], const double
        costab[513], const double sintab[513], creal_T y[1024]);
      static void generate_twiddle_tables(double costab[131073], double sintab
        [131073], double sintabinv[131073]);
      static void dobluesteinfft(const double x[100000], const double costab
        [131073], const double sintab[131073], const double sintabinv[131073],
        creal_T y[100000]);
      static void c_r2br_r2dit_trig_impl(const creal_T x[100000], const double
        costab[131073], const double sintab[131073], creal_T y[262144]);
      static void c_r2br_r2dit_trig(const creal_T x[199999], const double
        costab[131073], const double sintab[131073], creal_T y[262144]);
      static void d_r2br_r2dit_trig(const creal_T x[262144], const double
        costab[131073], const double sintab[131073], creal_T y[262144]);
     protected:
      static void b_generate_twiddle_tables(double costab[100001], double
        sintab[100001], double sintabinv[100001]);
      static void b_r2br_r2dit_trig_impl(const creal_T x[50000], const double
        costab[65536], const double sintab[65536], creal_T y[131072]);
      static void r2br_r2dit_trig(const creal_T x[99999], const double costab
        [65536], const double sintab[65536], creal_T y[131072]);
      static void b_r2br_r2dit_trig(const creal_T x[131072], const double
        costab[65536], const double sintab[65536], creal_T y[131072]);
      static void doHalfLengthBluestein(const double x[100000], creal_T y[100000],
        const creal_T wwc[99999], const double costab[131073], const double
        sintab[131073], const double costabinv[131073], const double sintabinv
        [131073]);
    };
  }
}

#endif

//
// File trailer for FFTImplementationCallback.h
//
// [EOF]
//
