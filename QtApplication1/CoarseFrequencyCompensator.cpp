//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CoarseFrequencyCompensator.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "CoarseFrequencyCompensator.h"
#include "FFTImplementationCallback.h"
#include "detect_recognize_data.h"
#include "detect_recognize_rtwutil.h"
#include "fftshift.h"
#include "relop.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
//
// Arguments    : const creal_T x[25000]
// Return Type  : double
//
namespace coder
{
  namespace comm
  {
    double CoarseFrequencyCompensator::FFTEstimateOffset(const creal_T x[25000])
    {
      static creal_T raisedSignal[25000];
      creal_T absFFTSig[1024];
      creal_T y[1024];
      creal_T b_y;
      int idxFFTs;
      int k;
      for (k = 0; k < 25000; k++) {
        double d;
        double r;
        r = x[k].re;
        d = x[k].im;
        if ((d == 0.0) && (r >= 0.0)) {
          raisedSignal[k].re = rt_powd_snf(r, 4.0);
          raisedSignal[k].im = 0.0;
        } else if (r == 0.0) {
          raisedSignal[k].re = rt_powd_snf(d, 4.0);
          raisedSignal[k].im = 0.0;
        } else {
          if (d == 0.0) {
            if (r < 0.0) {
              b_y.re = std::log(std::abs(r));
              b_y.im = 3.1415926535897931;
            } else {
              b_y.re = std::log(r);
              b_y.im = 0.0;
            }
          } else if ((std::abs(r) > 8.9884656743115785E+307) || (std::abs(d) >
                      8.9884656743115785E+307)) {
            b_y.re = std::log(rt_hypotd_snf(r / 2.0, d / 2.0)) +
              0.69314718055994529;
            b_y.im = rt_atan2d_snf(d, r);
          } else {
            b_y.re = std::log(rt_hypotd_snf(r, d));
            b_y.im = rt_atan2d_snf(d, r);
          }

          b_y.re *= 4.0;
          b_y.im *= 4.0;
          if (b_y.im == 0.0) {
            raisedSignal[k].re = std::exp(b_y.re);
            raisedSignal[k].im = 0.0;
          } else if (rtIsInf(b_y.im) && rtIsInf(b_y.re) && (b_y.re < 0.0)) {
            raisedSignal[k].re = 0.0;
            raisedSignal[k].im = 0.0;
          } else {
            r = std::exp(b_y.re / 2.0);
            raisedSignal[k].re = r * (r * std::cos(b_y.im));
            raisedSignal[k].im = r * (r * std::sin(b_y.im));
          }
        }
      }

      std::memset(&absFFTSig[0], 0, 1024U * sizeof(creal_T));
      for (idxFFTs = 0; idxFFTs < 24; idxFFTs++) {
        internal::FFTImplementationCallback::r2br_r2dit_trig_impl((*(creal_T (*)
          [1024])&raisedSignal[idxFFTs << 10]), (dv), (dv1), (y));
        for (k = 0; k < 1024; k++) {
          absFFTSig[k].re += rt_hypotd_snf(y[k].re, y[k].im);
        }
      }

      internal::FFTImplementationCallback::r2br_r2dit_trig_impl((*(creal_T (*)
        [1024])&raisedSignal[23976]), (dv), (dv1), (y));
      for (k = 0; k < 1024; k++) {
        absFFTSig[k].re += rt_hypotd_snf(y[k].re, y[k].im);
      }

      c_fftshift(absFFTSig);
      idxFFTs = -1;
      b_y = absFFTSig[0];
      for (k = 0; k < 1023; k++) {
        creal_T absFFTSig_tmp;
        boolean_T p;
        absFFTSig_tmp = absFFTSig[k + 1];
        p = internal::relop(b_y, absFFTSig_tmp);
        if (p) {
          b_y = absFFTSig_tmp;
          idxFFTs = k;
        }
      }

      return 0.0009765625 * (((static_cast<double>(idxFFTs) + 2.0) - 512.0) -
        1.0) / 4.0;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void CoarseFrequencyCompensator::SystemCore_delete()
    {
      this->release();
    }

    //
    // Arguments    : const creal_T x[25000]
    // Return Type  : double
    //
    double CoarseFrequencyCompensator::b_FFTEstimateOffset(const creal_T x[25000])
    {
      static creal_T raisedSignal[25000];
      creal_T absFFTSig[1024];
      creal_T y[1024];
      creal_T b_y;
      int idxFFTs;
      int k;
      for (k = 0; k < 25000; k++) {
        double d;
        double r;
        r = x[k].re;
        d = x[k].im;
        if ((d == 0.0) && (r >= 0.0)) {
          raisedSignal[k].re = rt_powd_snf(r, 8.0);
          raisedSignal[k].im = 0.0;
        } else if (r == 0.0) {
          raisedSignal[k].re = rt_powd_snf(d, 8.0);
          raisedSignal[k].im = 0.0;
        } else {
          if (d == 0.0) {
            if (r < 0.0) {
              b_y.re = std::log(std::abs(r));
              b_y.im = 3.1415926535897931;
            } else {
              b_y.re = std::log(r);
              b_y.im = 0.0;
            }
          } else if ((std::abs(r) > 8.9884656743115785E+307) || (std::abs(d) >
                      8.9884656743115785E+307)) {
            b_y.re = std::log(rt_hypotd_snf(r / 2.0, d / 2.0)) +
              0.69314718055994529;
            b_y.im = rt_atan2d_snf(d, r);
          } else {
            b_y.re = std::log(rt_hypotd_snf(r, d));
            b_y.im = rt_atan2d_snf(d, r);
          }

          b_y.re *= 8.0;
          b_y.im *= 8.0;
          if (b_y.im == 0.0) {
            raisedSignal[k].re = std::exp(b_y.re);
            raisedSignal[k].im = 0.0;
          } else if (rtIsInf(b_y.im) && rtIsInf(b_y.re) && (b_y.re < 0.0)) {
            raisedSignal[k].re = 0.0;
            raisedSignal[k].im = 0.0;
          } else {
            r = std::exp(b_y.re / 2.0);
            raisedSignal[k].re = r * (r * std::cos(b_y.im));
            raisedSignal[k].im = r * (r * std::sin(b_y.im));
          }
        }
      }

      std::memset(&absFFTSig[0], 0, 1024U * sizeof(creal_T));
      for (idxFFTs = 0; idxFFTs < 24; idxFFTs++) {
        internal::FFTImplementationCallback::r2br_r2dit_trig_impl((*(creal_T (*)
          [1024])&raisedSignal[idxFFTs << 10]), (dv), (dv1), (y));
        for (k = 0; k < 1024; k++) {
          absFFTSig[k].re += rt_hypotd_snf(y[k].re, y[k].im);
        }
      }

      internal::FFTImplementationCallback::r2br_r2dit_trig_impl((*(creal_T (*)
        [1024])&raisedSignal[23976]), (dv), (dv1), (y));
      for (k = 0; k < 1024; k++) {
        absFFTSig[k].re += rt_hypotd_snf(y[k].re, y[k].im);
      }

      c_fftshift(absFFTSig);
      idxFFTs = -1;
      b_y = absFFTSig[0];
      for (k = 0; k < 1023; k++) {
        creal_T absFFTSig_tmp;
        boolean_T p;
        absFFTSig_tmp = absFFTSig[k + 1];
        p = internal::relop(b_y, absFFTSig_tmp);
        if (p) {
          b_y = absFFTSig_tmp;
          idxFFTs = k;
        }
      }

      return 0.0009765625 * (((static_cast<double>(idxFFTs) + 2.0) - 512.0) -
        1.0) / 8.0;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void CoarseFrequencyCompensator::release()
    {
      if (this->isInitialized == 1) {
        this->isInitialized = 2;
      }
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void CoarseFrequencyCompensator::setup()
    {
      this->isSetupComplete = false;
      this->isInitialized = 1;
      this->isSetupComplete = true;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void CoarseFrequencyCompensator::setupAndReset()
    {
      this->setup();
      std::memset(&this->pRaisedSignalBuffer[0], 0, 1024U * sizeof(creal_T));
      this->pCumFreqOffset = 0.0;
    }

    //
    // Arguments    : void
    // Return Type  : CoarseFrequencyCompensator *
    //
    CoarseFrequencyCompensator *CoarseFrequencyCompensator::b_init()
    {
      CoarseFrequencyCompensator *obj;
      obj = this;
      obj->isInitialized = 0;
      obj->matlabCodegenIsDeleted = false;
      return obj;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    CoarseFrequencyCompensator::CoarseFrequencyCompensator()
    {
      this->matlabCodegenIsDeleted = true;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    CoarseFrequencyCompensator::~CoarseFrequencyCompensator()
    {
      this->matlabCodegenDestructor();
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void CoarseFrequencyCompensator::handle_matlabCodegenDestructor()
    {
      if (!this->matlabCodegenIsDeleted) {
        this->matlabCodegenIsDeleted = true;
        this->SystemCore_delete();
      }
    }

    //
    // Arguments    : void
    // Return Type  : CoarseFrequencyCompensator *
    //
    CoarseFrequencyCompensator *CoarseFrequencyCompensator::init()
    {
      CoarseFrequencyCompensator *obj;
      obj = this;
      obj->isInitialized = 0;
      obj->matlabCodegenIsDeleted = false;
      this->setupAndReset();
      return obj;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void CoarseFrequencyCompensator::matlabCodegenDestructor()
    {
      if (!this->matlabCodegenIsDeleted) {
        this->matlabCodegenIsDeleted = true;
        this->release();
      }
    }

    //
    // Arguments    : const creal_T varargin_1[25000]
    //                creal_T varargout_1[25000]
    // Return Type  : void
    //
    void CoarseFrequencyCompensator::step(const creal_T varargin_1[25000],
      creal_T varargout_1[25000])
    {
      static double freqVec[25001];
      double cumFreqOffset;
      double r;
      int k;
      cumFreqOffset = this->pCumFreqOffset;
      r = CoarseFrequencyCompensator::FFTEstimateOffset((varargin_1));
      for (k = 0; k < 25001; k++) {
        freqVec[k] = r * static_cast<double>(k);
      }

      for (k = 0; k < 25000; k++) {
        double d;
        double d1;
        double im;
        double re;
        r = cumFreqOffset - freqVec[k];
        re = r * 0.0;
        im = r * 6.2831853071795862;
        if (im == 0.0) {
          re = std::exp(re);
          im = 0.0;
        } else {
          r = std::exp(re / 2.0);
          re = r * (r * std::cos(im));
          im = r * (r * std::sin(im));
        }

        d = varargin_1[k].re;
        d1 = varargin_1[k].im;
        r = d * re - d1 * im;
        im = d * im + d1 * re;
        varargout_1[k].re = r;
        varargout_1[k].im = im;
      }

      this->pCumFreqOffset = cumFreqOffset - freqVec[25000];
    }

    //
    // Arguments    : const creal_T varargin_1[25000]
    //                creal_T varargout_1[25000]
    //                double *varargout_2
    // Return Type  : void
    //
    void CoarseFrequencyCompensator::step(const creal_T varargin_1[25000],
      creal_T varargout_1[25000], double *varargout_2)
    {
      static double freqVec[25001];
      double cumFreqOffset;
      int k;
      if (this->isInitialized != 1) {
        this->setupAndReset();
      }

      cumFreqOffset = this->pCumFreqOffset;
      *varargout_2 = CoarseFrequencyCompensator::b_FFTEstimateOffset((varargin_1));
      for (k = 0; k < 25001; k++) {
        freqVec[k] = *varargout_2 * static_cast<double>(k);
      }

      for (k = 0; k < 25000; k++) {
        double d;
        double d1;
        double im;
        double r;
        double re;
        r = cumFreqOffset - freqVec[k];
        re = r * 0.0;
        im = r * 6.2831853071795862;
        if (im == 0.0) {
          re = std::exp(re);
          im = 0.0;
        } else {
          r = std::exp(re / 2.0);
          re = r * (r * std::cos(im));
          im = r * (r * std::sin(im));
        }

        d = varargin_1[k].re;
        d1 = varargin_1[k].im;
        r = d * re - d1 * im;
        im = d * im + d1 * re;
        varargout_1[k].re = r;
        varargout_1[k].im = im;
      }

      this->pCumFreqOffset = cumFreqOffset - freqVec[25000];
    }
  }
}

//
// File trailer for CoarseFrequencyCompensator.cpp
//
// [EOF]
//
