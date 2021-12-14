//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SymbolSynchronizer.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "SymbolSynchronizer.h"
#include "ProcessConstructorArguments.h"
#include "detect_recognize_data.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace coder
{
  namespace comm
  {
    void SymbolSynchronizer::checkTunableProps()
    {
      if (this->TunablePropsChanged) {
        double d;
        double theta;
        double zeta;
        this->TunablePropsChanged = false;
        zeta = this->DampingFactor;
        theta = this->NormalizedLoopBandwidth / 2.0 / (zeta + 0.25 / zeta);
        d = -((2.0 * zeta * theta + 1.0) + theta * theta) * this->DetectorGain;
        this->pProportionalGain = 4.0 * zeta * theta / d;
        this->pIntegratorGain = 4.0 * theta * theta / d;
      }
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void SymbolSynchronizer::release()
    {
      if (this->isInitialized == 1) {
        this->isInitialized = 2;
      }
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void SymbolSynchronizer::setup()
    {
      double d;
      double theta;
      double zeta;
      this->isSetupComplete = false;
      this->isInitialized = 1;
      zeta = this->DampingFactor;
      theta = this->NormalizedLoopBandwidth / 2.0 / (zeta + 0.25 / zeta);
      d = -((2.0 * zeta * theta + 1.0) + theta * theta) * this->DetectorGain;
      this->pProportionalGain = 4.0 * zeta * theta / d;
      this->pIntegratorGain = 4.0 * theta * theta / d;
      this->isSetupComplete = true;
      this->TunablePropsChanged = false;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void SymbolSynchronizer::setupAndReset()
    {
      this->setup();
      this->pLoopFilterState = 0.0;
      this->pLoopPreviousInput = 0.0;
      this->pStrobe = false;
      this->pNumStrobe = 0.0;
      this->pStrobeHistory[0] = false;
      this->pStrobeHistory[1] = false;
      this->pMu = 0.0;
      this->pNCOCounter = 0.0;
      std::memset(&this->pTimingError[0], 0, 50000U * sizeof(double));
      this->pInterpFilterState[0].re = 0.0;
      this->pInterpFilterState[0].im = 0.0;
      this->pInterpFilterState[1].re = 0.0;
      this->pInterpFilterState[1].im = 0.0;
      this->pInterpFilterState[2].re = 0.0;
      this->pInterpFilterState[2].im = 0.0;
      this->pTEDBuffer[0].re = 0.0;
      this->pTEDBuffer[0].im = 0.0;
      this->pTEDBuffer[1].re = 0.0;
      this->pTEDBuffer[1].im = 0.0;
      std::memset(&this->pSymbolHolder[0], 0, 27500U * sizeof(creal_T));
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    SymbolSynchronizer::SymbolSynchronizer()
    {
      this->matlabCodegenIsDeleted = true;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    SymbolSynchronizer::~SymbolSynchronizer()
    {
      this->matlabCodegenDestructor();
    }

    //
    // Arguments    : void
    // Return Type  : SymbolSynchronizer *
    //
    SymbolSynchronizer *SymbolSynchronizer::init()
    {
      SymbolSynchronizer *obj;
      obj = this;
      obj->DetectorGain = 2.7;
      obj->isInitialized = 0;
      matlab::system::coder::ProcessConstructorArguments::b_do((obj));
      obj->matlabCodegenIsDeleted = false;
      return obj;
    }

    //
    // Arguments    : void
    // Return Type  : boolean_T
    //
    boolean_T SymbolSynchronizer::isLockedAndNotReleased() const
    {
      return this->isInitialized == 1;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void SymbolSynchronizer::matlabCodegenDestructor()
    {
      if (!this->matlabCodegenIsDeleted) {
        this->matlabCodegenIsDeleted = true;
        this->release();
      }
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void SymbolSynchronizer::set_DampingFactor()
    {
      this->DampingFactor = 0.70710678118654757;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void SymbolSynchronizer::set_NormalizedLoopBandwidth()
    {
      this->NormalizedLoopBandwidth = 0.01;
    }

    //
    // Arguments    : const creal_T varargin_1[50000]
    //                ::coder::array<creal_T, 1U> &varargout_1
    // Return Type  : void
    //
    void SymbolSynchronizer::step(const creal_T varargin_1[50000], ::coder::
      array<creal_T, 1U> &varargout_1)
    {
      static const double b_dv[12] = { 0.0, -0.5, 0.5, 0.0, 1.5, -0.5, 1.0, -0.5,
        -0.5, 0.0, -0.5, 0.5 };

      creal_T dcv[12];
      creal_T y[3];
      double d;
      int i;
      int sampleIdx;
      boolean_T exitg1;
      if (this->isInitialized != 1) {
        this->setupAndReset();
      }

      this->checkTunableProps();
      this->pNumStrobe = 0.0;
      sampleIdx = 0;
      exitg1 = false;
      while ((!exitg1) && ((sampleIdx < 50000) && ((!(this->pNumStrobe ==
                 27500.0)) || (!this->pStrobe)))) {
        creal_T xSeq_idx_0;
        creal_T xSeq_idx_1;
        creal_T xSeq_idx_2;
        creal_T xSeq_idx_3;
        double ai;
        double b_x;
        double e;
        double intOut_im;
        double intOut_re;
        double midSample_im;
        double midSample_re;
        double x;
        this->pNumStrobe += static_cast<double>(this->pStrobe);
        this->pTimingError[sampleIdx] = this->pMu;
        xSeq_idx_0 = varargin_1[sampleIdx];
        xSeq_idx_1 = this->pInterpFilterState[0];
        xSeq_idx_2 = this->pInterpFilterState[1];
        xSeq_idx_3 = this->pInterpFilterState[2];
        for (i = 0; i < 12; i++) {
          dcv[i].re = b_dv[i];
          dcv[i].im = 0.0;
        }

        for (i = 0; i < 3; i++) {
          d = dcv[i].re;
          midSample_im = dcv[i].im;
          e = dcv[i + 3].re;
          ai = dcv[i + 3].im;
          x = dcv[i + 6].re;
          midSample_re = dcv[i + 6].im;
          b_x = dcv[i + 9].re;
          intOut_im = dcv[i + 9].im;
          y[i].re = (((d * xSeq_idx_0.re - midSample_im * xSeq_idx_0.im) + (e *
            xSeq_idx_1.re - ai * xSeq_idx_1.im)) + (x * xSeq_idx_2.re -
                      midSample_re * xSeq_idx_2.im)) + (b_x * xSeq_idx_3.re -
            intOut_im * xSeq_idx_3.im);
          y[i].im = (((d * xSeq_idx_0.im + midSample_im * xSeq_idx_0.re) + (e *
            xSeq_idx_1.im + ai * xSeq_idx_1.re)) + (x * xSeq_idx_2.im +
                      midSample_re * xSeq_idx_2.re)) + (b_x * xSeq_idx_3.im +
            intOut_im * xSeq_idx_3.re);
        }

        midSample_im = this->pMu;
        d = midSample_im * midSample_im;
        intOut_re = (y[0].re + this->pMu * y[1].re) + d * y[2].re;
        intOut_im = (y[0].im + this->pMu * y[1].im) + d * y[2].im;
        this->pInterpFilterState[0] = xSeq_idx_0;
        this->pInterpFilterState[1] = xSeq_idx_1;
        this->pInterpFilterState[2] = xSeq_idx_2;
        if (this->pStrobe) {
          this->pSymbolHolder[static_cast<int>(this->pNumStrobe) - 1].re =
            intOut_re;
          this->pSymbolHolder[static_cast<int>(this->pNumStrobe) - 1].im =
            intOut_im;
        }

        if (this->pNumStrobe > 27500.0) {
          exitg1 = true;
        } else {
          if (this->pStrobe && (!this->pStrobeHistory[1])) {
            midSample_im = this->pTEDBuffer[1].re + this->pTEDBuffer[1].re;
            ai = this->pTEDBuffer[1].im + this->pTEDBuffer[1].im;
            if (ai == 0.0) {
              midSample_re = midSample_im / 2.0;
              midSample_im = 0.0;
            } else if (midSample_im == 0.0) {
              midSample_re = 0.0;
              midSample_im = ai / 2.0;
            } else {
              midSample_re = midSample_im / 2.0;
              midSample_im = ai / 2.0;
            }

            b_x = this->pTEDBuffer[0].re;
            if (b_x < 0.0) {
              b_x = -1.0;
            } else if (b_x > 0.0) {
              b_x = 1.0;
            } else {
              if (b_x == 0.0) {
                b_x = 0.0;
              }
            }

            e = intOut_re;
            if (intOut_re < 0.0) {
              e = -1.0;
            } else if (intOut_re > 0.0) {
              e = 1.0;
            } else {
              if (intOut_re == 0.0) {
                e = 0.0;
              }
            }

            ai = this->pTEDBuffer[0].im;
            if (ai < 0.0) {
              ai = -1.0;
            } else if (ai > 0.0) {
              ai = 1.0;
            } else {
              if (ai == 0.0) {
                ai = 0.0;
              }
            }

            x = intOut_im;
            if (intOut_im < 0.0) {
              x = -1.0;
            } else if (intOut_im > 0.0) {
              x = 1.0;
            } else {
              if (intOut_im == 0.0) {
                x = 0.0;
              }
            }

            e = midSample_re * (b_x - e) + midSample_im * (ai - x);
          } else {
            e = 0.0;
          }

          switch (this->pStrobeHistory[1] + this->pStrobe) {
           case 0:
            break;

           case 1:
            this->pTEDBuffer[0] = this->pTEDBuffer[1];
            this->pTEDBuffer[1].re = intOut_re;
            this->pTEDBuffer[1].im = intOut_im;
            break;

           default:
            this->pTEDBuffer[0].re = 0.0;
            this->pTEDBuffer[0].im = 0.0;
            this->pTEDBuffer[1].re = intOut_re;
            this->pTEDBuffer[1].im = intOut_im;
            break;
          }

          midSample_im = this->pLoopPreviousInput + this->pLoopFilterState;
          ai = e * this->pProportionalGain + midSample_im;
          this->pLoopFilterState = midSample_im;
          this->pLoopPreviousInput = e * this->pIntegratorGain;
          this->pStrobeHistory[0] = this->pStrobeHistory[1];
          this->pStrobeHistory[1] = this->pStrobe;
          this->pStrobe = (this->pNCOCounter < ai + 0.5);
          if (this->pStrobe) {
            this->pMu = this->pNCOCounter / (ai + 0.5);
          }

          b_x = this->pNCOCounter - (ai + 0.5);
          if (rtIsNaN(b_x) || rtIsInf(b_x)) {
            midSample_im = rtNaN;
          } else if (b_x == 0.0) {
            midSample_im = 0.0;
          } else {
            midSample_im = std::fmod(b_x, 1.0);
            if (midSample_im == 0.0) {
              midSample_im = 0.0;
            } else {
              if (b_x < 0.0) {
                midSample_im++;
              }
            }
          }

          this->pNCOCounter = midSample_im;
          sampleIdx++;
        }
      }

      d = this->pNumStrobe;
      if (1.0 > d) {
        sampleIdx = 0;
      } else {
        sampleIdx = static_cast<int>(d);
      }

      varargout_1.set_size(sampleIdx);
      for (i = 0; i < sampleIdx; i++) {
        varargout_1[i] = this->pSymbolHolder[i];
      }
    }
  }
}

//
// File trailer for SymbolSynchronizer.cpp
//
// [EOF]
//
