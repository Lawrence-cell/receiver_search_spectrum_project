//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: hilbert.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "hilbert.h"
#include "FFTImplementationCallback.h"
#include "ifft.h"
#include "rt_nonfinite.h"
#include <cstring>
#include <string.h>

// Function Definitions
//
// Arguments    : const double xr[100000]
//                creal_T x[100000]
// Return Type  : void
//
namespace coder
{
  void hilbert(const double xr[100000], creal_T x[100000])
  {
    static creal_T dcv[100000];
    static double costab[131073];
    static double sintab[131073];
    static double sintabinv[131073];
    internal::FFTImplementationCallback::generate_twiddle_tables((costab),
      (sintab), (sintabinv));
    internal::FFTImplementationCallback::dobluesteinfft((xr), (costab), (sintab),
      (sintabinv), (dcv));
    std::memcpy(&x[0], &dcv[0], 100000U * sizeof(creal_T));
    for (int i = 0; i < 49999; i++) {
      x[i + 1].re *= 2.0;
      x[i + 1].im *= 2.0;
      x[i + 50001].re = 0.0;
      x[i + 50001].im = 0.0;
    }

    ifft(x, dcv);
    std::memcpy(&x[0], &dcv[0], 100000U * sizeof(creal_T));
  }
}

//
// File trailer for hilbert.cpp
//
// [EOF]
//
