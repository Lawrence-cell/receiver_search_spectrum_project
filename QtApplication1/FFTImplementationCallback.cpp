//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FFTImplementationCallback.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
//
// Arguments    : double costab[100001]
//                double sintab[100001]
//                double sintabinv[100001]
// Return Type  : void
//
namespace coder
{
  namespace internal
  {
    void FFTImplementationCallback::b_generate_twiddle_tables(double costab
      [100001], double sintab[100001], double sintabinv[100001])
    {
      static double costab1q[50001];
      int k;
      costab1q[0] = 1.0;
      for (k = 0; k < 25000; k++) {
        costab1q[k + 1] = std::cos(3.1415926535897928E-5 * (static_cast<double>
          (k) + 1.0));
      }

      for (k = 0; k < 24999; k++) {
        costab1q[k + 25001] = std::sin(3.1415926535897928E-5 * (50000.0 - (
          static_cast<double>(k) + 25001.0)));
      }

      costab1q[50000] = 0.0;
      costab[0] = 1.0;
      sintab[0] = 0.0;
      for (k = 0; k < 50000; k++) {
        double b_sintabinv_tmp;
        double sintabinv_tmp;
        sintabinv_tmp = costab1q[49999 - k];
        sintabinv[k + 1] = sintabinv_tmp;
        b_sintabinv_tmp = costab1q[k + 1];
        sintabinv[k + 50001] = b_sintabinv_tmp;
        costab[k + 1] = b_sintabinv_tmp;
        sintab[k + 1] = -sintabinv_tmp;
        costab[k + 50001] = -sintabinv_tmp;
        sintab[k + 50001] = -b_sintabinv_tmp;
      }
    }

    //
    // Arguments    : const creal_T x[131072]
    //                const double costab[65536]
    //                const double sintab[65536]
    //                creal_T y[131072]
    // Return Type  : void
    //
    void FFTImplementationCallback::b_r2br_r2dit_trig(const creal_T x[131072],
      const double costab[65536], const double sintab[65536], creal_T y[131072])
    {
      double temp_im;
      double temp_re;
      double twid_im;
      double twid_re;
      int i;
      int iheight;
      int ix;
      int iy;
      int j;
      int ju;
      ix = 0;
      iy = 0;
      ju = 0;
      for (i = 0; i < 131071; i++) {
        boolean_T tst;
        y[iy] = x[ix];
        iy = 131072;
        tst = true;
        while (tst) {
          iy >>= 1;
          ju ^= iy;
          tst = ((ju & iy) == 0);
        }

        iy = ju;
        ix++;
      }

      y[iy] = x[ix];
      for (i = 0; i <= 131070; i += 2) {
        double im;
        double re;
        twid_re = y[i + 1].re;
        temp_re = twid_re;
        twid_im = y[i + 1].im;
        temp_im = twid_im;
        re = y[i].re;
        im = y[i].im;
        twid_re = re - twid_re;
        y[i + 1].re = twid_re;
        twid_im = im - twid_im;
        y[i + 1].im = twid_im;
        y[i].re = re + temp_re;
        y[i].im = im + temp_im;
      }

      iy = 2;
      ix = 4;
      ju = 32768;
      iheight = 131069;
      while (ju > 0) {
        int istart;
        int temp_re_tmp;
        for (i = 0; i < iheight; i += ix) {
          temp_re_tmp = i + iy;
          temp_re = y[temp_re_tmp].re;
          temp_im = y[temp_re_tmp].im;
          y[temp_re_tmp].re = y[i].re - temp_re;
          y[temp_re_tmp].im = y[i].im - temp_im;
          y[i].re += temp_re;
          y[i].im += temp_im;
        }

        istart = 1;
        for (j = ju; j < 65536; j += ju) {
          int ihi;
          twid_re = costab[j];
          twid_im = sintab[j];
          i = istart;
          ihi = istart + iheight;
          while (i < ihi) {
            temp_re_tmp = i + iy;
            temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
            temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
            y[temp_re_tmp].re = y[i].re - temp_re;
            y[temp_re_tmp].im = y[i].im - temp_im;
            y[i].re += temp_re;
            y[i].im += temp_im;
            i += ix;
          }

          istart++;
        }

        ju /= 2;
        iy = ix;
        ix += ix;
        iheight -= iy;
      }

      for (iy = 0; iy < 131072; iy++) {
        y[iy].re *= 7.62939453125E-6;
        y[iy].im *= 7.62939453125E-6;
      }
    }

    //
    // Arguments    : const creal_T x[50000]
    //                const double costab[65536]
    //                const double sintab[65536]
    //                creal_T y[131072]
    // Return Type  : void
    //
    void FFTImplementationCallback::b_r2br_r2dit_trig_impl(const creal_T x[50000],
      const double costab[65536], const double sintab[65536], creal_T y[131072])
    {
      double temp_im;
      double temp_re;
      double twid_im;
      double twid_re;
      int i;
      int iheight;
      int ix;
      int iy;
      int j;
      int ju;
      std::memset(&y[0], 0, 131072U * sizeof(creal_T));
      ix = 0;
      iy = 0;
      ju = 0;
      for (i = 0; i < 49999; i++) {
        boolean_T tst;
        y[iy] = x[ix];
        iy = 131072;
        tst = true;
        while (tst) {
          iy >>= 1;
          ju ^= iy;
          tst = ((ju & iy) == 0);
        }

        iy = ju;
        ix++;
      }

      y[iy] = x[ix];
      for (i = 0; i <= 131070; i += 2) {
        double im;
        double re;
        twid_re = y[i + 1].re;
        temp_re = twid_re;
        twid_im = y[i + 1].im;
        temp_im = twid_im;
        re = y[i].re;
        im = y[i].im;
        twid_re = re - twid_re;
        y[i + 1].re = twid_re;
        twid_im = im - twid_im;
        y[i + 1].im = twid_im;
        y[i].re = re + temp_re;
        y[i].im = im + temp_im;
      }

      iy = 2;
      ix = 4;
      ju = 32768;
      iheight = 131069;
      while (ju > 0) {
        int istart;
        int temp_re_tmp;
        for (i = 0; i < iheight; i += ix) {
          temp_re_tmp = i + iy;
          temp_re = y[temp_re_tmp].re;
          temp_im = y[temp_re_tmp].im;
          y[temp_re_tmp].re = y[i].re - temp_re;
          y[temp_re_tmp].im = y[i].im - temp_im;
          y[i].re += temp_re;
          y[i].im += temp_im;
        }

        istart = 1;
        for (j = ju; j < 65536; j += ju) {
          int ihi;
          twid_re = costab[j];
          twid_im = sintab[j];
          i = istart;
          ihi = istart + iheight;
          while (i < ihi) {
            temp_re_tmp = i + iy;
            temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
            temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
            y[temp_re_tmp].re = y[i].re - temp_re;
            y[temp_re_tmp].im = y[i].im - temp_im;
            y[i].re += temp_re;
            y[i].im += temp_im;
            i += ix;
          }

          istart++;
        }

        ju /= 2;
        iy = ix;
        ix += ix;
        iheight -= iy;
      }
    }

    //
    // Arguments    : const double x[100000]
    //                creal_T y[100000]
    //                const creal_T wwc[99999]
    //                const double costab[131073]
    //                const double sintab[131073]
    //                const double costabinv[131073]
    //                const double sintabinv[131073]
    // Return Type  : void
    //
    void FFTImplementationCallback::doHalfLengthBluestein(const double x[100000],
      creal_T y[100000], const creal_T wwc[99999], const double costab[131073],
      const double sintab[131073], const double costabinv[131073], const double
      sintabinv[131073])
    {
      static creal_T b_fv[131072];
      static creal_T fv[131072];
      static creal_T reconVar1[50000];
      static creal_T reconVar2[50000];
      static creal_T ytmp[50000];
      static double costable[100001];
      static double sintable[100001];
      static double unusedU0[100001];
      static double hcostab[65536];
      static double hcostabinv[65536];
      static double hsintab[65536];
      static double hsintabinv[65536];
      static int wrapIndex[50000];
      double b_im;
      double b_re;
      double d;
      double d1;
      double d2;
      double d3;
      int i;
      int idx;
      int xidx;
      FFTImplementationCallback::b_generate_twiddle_tables((costable), (sintable),
        (unusedU0));
      for (i = 0; i < 65536; i++) {
        xidx = ((i + 1) << 1) - 2;
        hcostab[i] = costab[xidx];
        hsintab[i] = sintab[xidx];
        hcostabinv[i] = costabinv[xidx];
        hsintabinv[i] = sintabinv[xidx];
      }

      idx = 0;
      xidx = 1;
      for (i = 0; i < 50000; i++) {
        reconVar1[i].re = sintable[idx] + 1.0;
        reconVar1[i].im = -costable[idx];
        reconVar2[i].re = 1.0 - sintable[idx];
        reconVar2[i].im = costable[idx];
        idx += 2;
        if (i + 1 != 1) {
          wrapIndex[i] = 50001 - i;
        } else {
          wrapIndex[0] = 1;
        }

        b_re = x[xidx - 1];
        b_im = x[xidx];
        d = wwc[i + 49999].re;
        d1 = wwc[i + 49999].im;
        ytmp[i].re = d * b_re + d1 * b_im;
        ytmp[i].im = d * b_im - d1 * b_re;
        xidx += 2;
      }

      FFTImplementationCallback::b_r2br_r2dit_trig_impl((ytmp), (hcostab),
        (hsintab), (fv));
      FFTImplementationCallback::r2br_r2dit_trig((wwc), (hcostab), (hsintab),
        (b_fv));
      for (xidx = 0; xidx < 131072; xidx++) {
        d = fv[xidx].re;
        d1 = fv[xidx].im;
        d2 = b_fv[xidx].im;
        d3 = b_fv[xidx].re;
        b_re = d * d2 + d1 * d3;
        d3 = d * d3 - d1 * d2;
        b_fv[xidx].re = d3;
        b_fv[xidx].im = b_re;
      }

      FFTImplementationCallback::b_r2br_r2dit_trig((b_fv), (hcostabinv),
        (hsintabinv), (fv));
      idx = 0;
      for (xidx = 0; xidx < 50000; xidx++) {
        d = wwc[xidx + 49999].re;
        d1 = wwc[xidx + 49999].im;
        d2 = fv[xidx + 49999].re;
        d3 = fv[xidx + 49999].im;
        ytmp[idx].re = d * d2 + d1 * d3;
        ytmp[idx].im = d * d3 - d1 * d2;
        idx++;
      }

      for (i = 0; i < 50000; i++) {
        xidx = wrapIndex[i];
        b_re = ytmp[xidx - 1].re;
        b_im = -ytmp[xidx - 1].im;
        d = reconVar1[i].re;
        d1 = reconVar1[i].im;
        d2 = reconVar2[i].re;
        d3 = reconVar2[i].im;
        y[i].re = 0.5 * ((ytmp[i].re * d - ytmp[i].im * d1) + (b_re * d2 - b_im *
          d3));
        y[i].im = 0.5 * ((ytmp[i].re * d1 + ytmp[i].im * d) + (b_re * d3 + b_im *
          d2));
        y[i + 50000].re = 0.5 * ((ytmp[i].re * d2 - ytmp[i].im * d3) + (b_re * d
          - b_im * d1));
        y[i + 50000].im = 0.5 * ((ytmp[i].re * d3 + ytmp[i].im * d2) + (b_re *
          d1 + b_im * d));
      }
    }

    //
    // Arguments    : const creal_T x[99999]
    //                const double costab[65536]
    //                const double sintab[65536]
    //                creal_T y[131072]
    // Return Type  : void
    //
    void FFTImplementationCallback::r2br_r2dit_trig(const creal_T x[99999],
      const double costab[65536], const double sintab[65536], creal_T y[131072])
    {
      double temp_im;
      double temp_re;
      double twid_im;
      double twid_re;
      int i;
      int iheight;
      int ix;
      int iy;
      int j;
      int ju;
      std::memset(&y[0], 0, 131072U * sizeof(creal_T));
      ix = 0;
      iy = 0;
      ju = 0;
      for (i = 0; i < 99998; i++) {
        boolean_T tst;
        y[iy] = x[ix];
        iy = 131072;
        tst = true;
        while (tst) {
          iy >>= 1;
          ju ^= iy;
          tst = ((ju & iy) == 0);
        }

        iy = ju;
        ix++;
      }

      y[iy] = x[ix];
      for (i = 0; i <= 131070; i += 2) {
        double im;
        double re;
        twid_re = y[i + 1].re;
        temp_re = twid_re;
        twid_im = y[i + 1].im;
        temp_im = twid_im;
        re = y[i].re;
        im = y[i].im;
        twid_re = re - twid_re;
        y[i + 1].re = twid_re;
        twid_im = im - twid_im;
        y[i + 1].im = twid_im;
        y[i].re = re + temp_re;
        y[i].im = im + temp_im;
      }

      iy = 2;
      ix = 4;
      ju = 32768;
      iheight = 131069;
      while (ju > 0) {
        int istart;
        int temp_re_tmp;
        for (i = 0; i < iheight; i += ix) {
          temp_re_tmp = i + iy;
          temp_re = y[temp_re_tmp].re;
          temp_im = y[temp_re_tmp].im;
          y[temp_re_tmp].re = y[i].re - temp_re;
          y[temp_re_tmp].im = y[i].im - temp_im;
          y[i].re += temp_re;
          y[i].im += temp_im;
        }

        istart = 1;
        for (j = ju; j < 65536; j += ju) {
          int ihi;
          twid_re = costab[j];
          twid_im = sintab[j];
          i = istart;
          ihi = istart + iheight;
          while (i < ihi) {
            temp_re_tmp = i + iy;
            temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
            temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
            y[temp_re_tmp].re = y[i].re - temp_re;
            y[temp_re_tmp].im = y[i].im - temp_im;
            y[i].re += temp_re;
            y[i].im += temp_im;
            i += ix;
          }

          istart++;
        }

        ju /= 2;
        iy = ix;
        ix += ix;
        iheight -= iy;
      }
    }

    //
    // Arguments    : const creal_T x[199999]
    //                const double costab[131073]
    //                const double sintab[131073]
    //                creal_T y[262144]
    // Return Type  : void
    //
    void FFTImplementationCallback::c_r2br_r2dit_trig(const creal_T x[199999],
      const double costab[131073], const double sintab[131073], creal_T y[262144])
    {
      double temp_im;
      double temp_re;
      double twid_im;
      double twid_re;
      int i;
      int iheight;
      int ix;
      int iy;
      int j;
      int ju;
      std::memset(&y[0], 0, 262144U * sizeof(creal_T));
      ix = 0;
      iy = 0;
      ju = 0;
      for (i = 0; i < 199998; i++) {
        boolean_T tst;
        y[iy] = x[ix];
        iy = 262144;
        tst = true;
        while (tst) {
          iy >>= 1;
          ju ^= iy;
          tst = ((ju & iy) == 0);
        }

        iy = ju;
        ix++;
      }

      y[iy] = x[ix];
      for (i = 0; i <= 262142; i += 2) {
        double im;
        double re;
        twid_re = y[i + 1].re;
        temp_re = twid_re;
        twid_im = y[i + 1].im;
        temp_im = twid_im;
        re = y[i].re;
        im = y[i].im;
        twid_re = re - twid_re;
        y[i + 1].re = twid_re;
        twid_im = im - twid_im;
        y[i + 1].im = twid_im;
        y[i].re = re + temp_re;
        y[i].im = im + temp_im;
      }

      iy = 2;
      ix = 4;
      ju = 65536;
      iheight = 262141;
      while (ju > 0) {
        int istart;
        int temp_re_tmp;
        for (i = 0; i < iheight; i += ix) {
          temp_re_tmp = i + iy;
          temp_re = y[temp_re_tmp].re;
          temp_im = y[temp_re_tmp].im;
          y[temp_re_tmp].re = y[i].re - temp_re;
          y[temp_re_tmp].im = y[i].im - temp_im;
          y[i].re += temp_re;
          y[i].im += temp_im;
        }

        istart = 1;
        for (j = ju; j < 131072; j += ju) {
          int ihi;
          twid_re = costab[j];
          twid_im = sintab[j];
          i = istart;
          ihi = istart + iheight;
          while (i < ihi) {
            temp_re_tmp = i + iy;
            temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
            temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
            y[temp_re_tmp].re = y[i].re - temp_re;
            y[temp_re_tmp].im = y[i].im - temp_im;
            y[i].re += temp_re;
            y[i].im += temp_im;
            i += ix;
          }

          istart++;
        }

        ju /= 2;
        iy = ix;
        ix += ix;
        iheight -= iy;
      }
    }

    //
    // Arguments    : const creal_T x[100000]
    //                const double costab[131073]
    //                const double sintab[131073]
    //                creal_T y[262144]
    // Return Type  : void
    //
    void FFTImplementationCallback::c_r2br_r2dit_trig_impl(const creal_T x
      [100000], const double costab[131073], const double sintab[131073],
      creal_T y[262144])
    {
      double temp_im;
      double temp_re;
      double twid_im;
      double twid_re;
      int i;
      int iheight;
      int ix;
      int iy;
      int j;
      int ju;
      std::memset(&y[0], 0, 262144U * sizeof(creal_T));
      ix = 0;
      iy = 0;
      ju = 0;
      for (i = 0; i < 99999; i++) {
        boolean_T tst;
        y[iy] = x[ix];
        iy = 262144;
        tst = true;
        while (tst) {
          iy >>= 1;
          ju ^= iy;
          tst = ((ju & iy) == 0);
        }

        iy = ju;
        ix++;
      }

      y[iy] = x[ix];
      for (i = 0; i <= 262142; i += 2) {
        double im;
        double re;
        twid_re = y[i + 1].re;
        temp_re = twid_re;
        twid_im = y[i + 1].im;
        temp_im = twid_im;
        re = y[i].re;
        im = y[i].im;
        twid_re = re - twid_re;
        y[i + 1].re = twid_re;
        twid_im = im - twid_im;
        y[i + 1].im = twid_im;
        y[i].re = re + temp_re;
        y[i].im = im + temp_im;
      }

      iy = 2;
      ix = 4;
      ju = 65536;
      iheight = 262141;
      while (ju > 0) {
        int istart;
        int temp_re_tmp;
        for (i = 0; i < iheight; i += ix) {
          temp_re_tmp = i + iy;
          temp_re = y[temp_re_tmp].re;
          temp_im = y[temp_re_tmp].im;
          y[temp_re_tmp].re = y[i].re - temp_re;
          y[temp_re_tmp].im = y[i].im - temp_im;
          y[i].re += temp_re;
          y[i].im += temp_im;
        }

        istart = 1;
        for (j = ju; j < 131072; j += ju) {
          int ihi;
          twid_re = costab[j];
          twid_im = sintab[j];
          i = istart;
          ihi = istart + iheight;
          while (i < ihi) {
            temp_re_tmp = i + iy;
            temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
            temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
            y[temp_re_tmp].re = y[i].re - temp_re;
            y[temp_re_tmp].im = y[i].im - temp_im;
            y[i].re += temp_re;
            y[i].im += temp_im;
            i += ix;
          }

          istart++;
        }

        ju /= 2;
        iy = ix;
        ix += ix;
        iheight -= iy;
      }
    }

    //
    // Arguments    : const creal_T x[262144]
    //                const double costab[131073]
    //                const double sintab[131073]
    //                creal_T y[262144]
    // Return Type  : void
    //
    void FFTImplementationCallback::d_r2br_r2dit_trig(const creal_T x[262144],
      const double costab[131073], const double sintab[131073], creal_T y[262144])
    {
      double temp_im;
      double temp_re;
      double twid_im;
      double twid_re;
      int i;
      int iheight;
      int ix;
      int iy;
      int j;
      int ju;
      ix = 0;
      iy = 0;
      ju = 0;
      for (i = 0; i < 262143; i++) {
        boolean_T tst;
        y[iy] = x[ix];
        iy = 262144;
        tst = true;
        while (tst) {
          iy >>= 1;
          ju ^= iy;
          tst = ((ju & iy) == 0);
        }

        iy = ju;
        ix++;
      }

      y[iy] = x[ix];
      for (i = 0; i <= 262142; i += 2) {
        double im;
        double re;
        twid_re = y[i + 1].re;
        temp_re = twid_re;
        twid_im = y[i + 1].im;
        temp_im = twid_im;
        re = y[i].re;
        im = y[i].im;
        twid_re = re - twid_re;
        y[i + 1].re = twid_re;
        twid_im = im - twid_im;
        y[i + 1].im = twid_im;
        y[i].re = re + temp_re;
        y[i].im = im + temp_im;
      }

      iy = 2;
      ix = 4;
      ju = 65536;
      iheight = 262141;
      while (ju > 0) {
        int istart;
        int temp_re_tmp;
        for (i = 0; i < iheight; i += ix) {
          temp_re_tmp = i + iy;
          temp_re = y[temp_re_tmp].re;
          temp_im = y[temp_re_tmp].im;
          y[temp_re_tmp].re = y[i].re - temp_re;
          y[temp_re_tmp].im = y[i].im - temp_im;
          y[i].re += temp_re;
          y[i].im += temp_im;
        }

        istart = 1;
        for (j = ju; j < 131072; j += ju) {
          int ihi;
          twid_re = costab[j];
          twid_im = sintab[j];
          i = istart;
          ihi = istart + iheight;
          while (i < ihi) {
            temp_re_tmp = i + iy;
            temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
            temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
            y[temp_re_tmp].re = y[i].re - temp_re;
            y[temp_re_tmp].im = y[i].im - temp_im;
            y[i].re += temp_re;
            y[i].im += temp_im;
            i += ix;
          }

          istart++;
        }

        ju /= 2;
        iy = ix;
        ix += ix;
        iheight -= iy;
      }

      for (iy = 0; iy < 262144; iy++) {
        y[iy].re *= 3.814697265625E-6;
        y[iy].im *= 3.814697265625E-6;
      }
    }

    //
    // Arguments    : const double x[100000]
    //                const double costab[131073]
    //                const double sintab[131073]
    //                const double sintabinv[131073]
    //                creal_T y[100000]
    // Return Type  : void
    //
    void FFTImplementationCallback::dobluesteinfft(const double x[100000], const
      double costab[131073], const double sintab[131073], const double
      sintabinv[131073], creal_T y[100000])
    {
      static creal_T wwc[99999];
      int idx;
      int k;
      int rt;
      idx = 49998;
      rt = 0;
      wwc[49999].re = 1.0;
      wwc[49999].im = 0.0;
      for (k = 0; k < 49999; k++) {
        double nt_im;
        double nt_re;
        int b_y;
        b_y = ((k + 1) << 1) - 1;
        if (100000 - rt <= b_y) {
          rt = (b_y + rt) - 100000;
        } else {
          rt += b_y;
        }

        nt_im = -3.1415926535897931 * static_cast<double>(rt) / 50000.0;
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
      for (k = 49998; k >= 0; k--) {
        wwc[k + 50000] = wwc[idx];
        idx++;
      }

      FFTImplementationCallback::doHalfLengthBluestein((x), (y), (wwc), (costab),
        (sintab), (costab), (sintabinv));
    }

    //
    // Arguments    : double costab[131073]
    //                double sintab[131073]
    //                double sintabinv[131073]
    // Return Type  : void
    //
    void FFTImplementationCallback::generate_twiddle_tables(double costab[131073],
      double sintab[131073], double sintabinv[131073])
    {
      static double costab1q[65537];
      int k;
      costab1q[0] = 1.0;
      for (k = 0; k < 32768; k++) {
        costab1q[k + 1] = std::cos(2.3968449810713143E-5 * (static_cast<double>
          (k) + 1.0));
      }

      for (k = 0; k < 32767; k++) {
        costab1q[k + 32769] = std::sin(2.3968449810713143E-5 * (65536.0 - (
          static_cast<double>(k) + 32769.0)));
      }

      costab1q[65536] = 0.0;
      costab[0] = 1.0;
      sintab[0] = 0.0;
      for (k = 0; k < 65536; k++) {
        double b_sintabinv_tmp;
        double sintabinv_tmp;
        sintabinv_tmp = costab1q[65535 - k];
        sintabinv[k + 1] = sintabinv_tmp;
        b_sintabinv_tmp = costab1q[k + 1];
        sintabinv[k + 65537] = b_sintabinv_tmp;
        costab[k + 1] = b_sintabinv_tmp;
        sintab[k + 1] = -sintabinv_tmp;
        costab[k + 65537] = -sintabinv_tmp;
        sintab[k + 65537] = -b_sintabinv_tmp;
      }
    }

    //
    // Arguments    : const creal_T x[1024]
    //                const double costab[513]
    //                const double sintab[513]
    //                creal_T y[1024]
    // Return Type  : void
    //
    void FFTImplementationCallback::r2br_r2dit_trig_impl(const creal_T x[1024],
      const double costab[513], const double sintab[513], creal_T y[1024])
    {
      double temp_im;
      double temp_re;
      double twid_im;
      double twid_re;
      int i;
      int iheight;
      int ix;
      int iy;
      int j;
      int ju;
      ix = 0;
      iy = 0;
      ju = 0;
      for (i = 0; i < 1023; i++) {
        boolean_T tst;
        y[iy] = x[ix];
        iy = 1024;
        tst = true;
        while (tst) {
          iy >>= 1;
          ju ^= iy;
          tst = ((ju & iy) == 0);
        }

        iy = ju;
        ix++;
      }

      y[iy] = x[ix];
      for (i = 0; i <= 1022; i += 2) {
        double im;
        double re;
        twid_re = y[i + 1].re;
        temp_re = twid_re;
        twid_im = y[i + 1].im;
        temp_im = twid_im;
        re = y[i].re;
        im = y[i].im;
        twid_re = re - twid_re;
        y[i + 1].re = twid_re;
        twid_im = im - twid_im;
        y[i + 1].im = twid_im;
        y[i].re = re + temp_re;
        y[i].im = im + temp_im;
      }

      iy = 2;
      ix = 4;
      ju = 256;
      iheight = 1021;
      while (ju > 0) {
        int istart;
        int temp_re_tmp;
        for (i = 0; i < iheight; i += ix) {
          temp_re_tmp = i + iy;
          temp_re = y[temp_re_tmp].re;
          temp_im = y[temp_re_tmp].im;
          y[temp_re_tmp].re = y[i].re - temp_re;
          y[temp_re_tmp].im = y[i].im - temp_im;
          y[i].re += temp_re;
          y[i].im += temp_im;
        }

        istart = 1;
        for (j = ju; j < 512; j += ju) {
          int ihi;
          twid_re = costab[j];
          twid_im = sintab[j];
          i = istart;
          ihi = istart + iheight;
          while (i < ihi) {
            temp_re_tmp = i + iy;
            temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
            temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
            y[temp_re_tmp].re = y[i].re - temp_re;
            y[temp_re_tmp].im = y[i].im - temp_im;
            y[i].re += temp_re;
            y[i].im += temp_im;
            i += ix;
          }

          istart++;
        }

        ju /= 2;
        iy = ix;
        ix += ix;
        iheight -= iy;
      }
    }
  }
}

//
// File trailer for FFTImplementationCallback.cpp
//
// [EOF]
//
