//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CarrierSynchronizer.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "CarrierSynchronizer.h"
#include "ProcessConstructorArguments.h"
#include "rt_nonfinite.h"
#include <cmath>
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
    void CarrierSynchronizer::SystemCore_checkTunableProps()
    {
      static const char b[4] = { 'A', 'u', 't', 'o' };

      if (this->TunablePropsChanged) {
        double PhaseRecoveryGain;
        double d;
        double theta;
        int ret;
        this->TunablePropsChanged = false;
        PhaseRecoveryGain = this->SamplesPerSymbol;
        theta = this->NormalizedLoopBandwidth * this->SamplesPerSymbol /
          ((this->DampingFactor + 0.25 / this->DampingFactor) *
           this->SamplesPerSymbol);
        d = (2.0 * this->DampingFactor * theta + 1.0) + theta * theta;
        this->pProportionalGain = 4.0 * this->DampingFactor * theta / d /
          PhaseRecoveryGain;
        this->pIntegratorGain = 4.0 * theta * theta / d / PhaseRecoveryGain;
        ret = memcmp(&this->ModulationPhaseOffset[0], &b[0], 4);
        if (ret == 0) {
          this->pActualPhaseOffset = 0.0;
        } else {
          this->pActualPhaseOffset = this->CustomPhaseOffset -
            0.39269908169872414;
        }
      }
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void CarrierSynchronizer::SystemCore_setup()
    {
      static const char b[4] = { 'A', 'u', 't', 'o' };

      double PhaseRecoveryGain;
      double d;
      double theta;
      int ret;
      this->isInitialized = 1;
      this->pPhase = 0.0;
      this->pPreviousSample.re = 0.0;
      this->pPreviousSample.im = 0.0;
      PhaseRecoveryGain = this->SamplesPerSymbol;
      theta = this->NormalizedLoopBandwidth * this->SamplesPerSymbol /
        ((this->DampingFactor + 0.25 / this->DampingFactor) *
         this->SamplesPerSymbol);
      d = (2.0 * this->DampingFactor * theta + 1.0) + theta * theta;
      this->pProportionalGain = 4.0 * this->DampingFactor * theta / d /
        PhaseRecoveryGain;
      this->pIntegratorGain = 4.0 * theta * theta / d / PhaseRecoveryGain;
      ret = memcmp(&this->ModulationPhaseOffset[0], &b[0], 4);
      if (ret == 0) {
        this->pActualPhaseOffset = 0.0;
      } else {
        this->pActualPhaseOffset = this->CustomPhaseOffset - 0.39269908169872414;
      }

      this->pDigitalSynthesizerGain = -1.0;
      this->TunablePropsChanged = false;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void CarrierSynchronizer::SystemCore_setupAndReset()
    {
      this->SystemCore_setup();
      this->pLoopFilterState = 0.0;
      this->pIntegFilterState = 0.0;
      this->pDDSPreviousInput = 0.0;
      this->pPhase = 0.0;
      this->pPreviousSample.re = 0.0;
      this->pPreviousSample.im = 0.0;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void CarrierSynchronizer::checkTunableProps()
    {
      static const char b[4] = { 'A', 'u', 't', 'o' };

      if (this->TunablePropsChanged) {
        double PhaseRecoveryGain;
        double d;
        double theta;
        int ret;
        this->TunablePropsChanged = false;
        PhaseRecoveryGain = this->SamplesPerSymbol;
        theta = this->NormalizedLoopBandwidth * this->SamplesPerSymbol /
          ((this->DampingFactor + 0.25 / this->DampingFactor) *
           this->SamplesPerSymbol);
        d = (2.0 * this->DampingFactor * theta + 1.0) + theta * theta;
        this->pProportionalGain = 4.0 * this->DampingFactor * theta / d / (2.0 *
          PhaseRecoveryGain);
        this->pIntegratorGain = 4.0 * theta * theta / d / (2.0 *
          PhaseRecoveryGain);
        ret = memcmp(&this->ModulationPhaseOffset[0], &b[0], 4);
        if (ret == 0) {
          this->pActualPhaseOffset = 0.0;
        } else {
          this->pActualPhaseOffset = this->CustomPhaseOffset -
            0.78539816339744828;
        }
      }
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void CarrierSynchronizer::setup()
    {
      static const char b[4] = { 'A', 'u', 't', 'o' };

      double PhaseRecoveryGain;
      double d;
      double theta;
      int ret;
      this->isInitialized = 1;
      this->pPhase = 0.0;
      this->pPreviousSample.re = 0.0;
      this->pPreviousSample.im = 0.0;
      PhaseRecoveryGain = this->SamplesPerSymbol;
      theta = this->NormalizedLoopBandwidth * this->SamplesPerSymbol /
        ((this->DampingFactor + 0.25 / this->DampingFactor) *
         this->SamplesPerSymbol);
      d = (2.0 * this->DampingFactor * theta + 1.0) + theta * theta;
      this->pProportionalGain = 4.0 * this->DampingFactor * theta / d / (2.0 *
        PhaseRecoveryGain);
      this->pIntegratorGain = 4.0 * theta * theta / d / (2.0 * PhaseRecoveryGain);
      ret = memcmp(&this->ModulationPhaseOffset[0], &b[0], 4);
      if (ret == 0) {
        this->pActualPhaseOffset = 0.0;
      } else {
        this->pActualPhaseOffset = this->CustomPhaseOffset - 0.78539816339744828;
      }

      this->pDigitalSynthesizerGain = -1.0;
      this->TunablePropsChanged = false;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void CarrierSynchronizer::setupAndReset()
    {
      this->setup();
      this->pLoopFilterState = 0.0;
      this->pIntegFilterState = 0.0;
      this->pDDSPreviousInput = 0.0;
      this->pPhase = 0.0;
      this->pPreviousSample.re = 0.0;
      this->pPreviousSample.im = 0.0;
    }

    //
    // Arguments    : const creal_T varargin_1[25000]
    //                creal_T varargout_1[25000]
    // Return Type  : void
    //
    void CarrierSynchronizer::SystemCore_step(const creal_T varargin_1[25000],
      creal_T varargout_1[25000])
    {
      double DDSOut;
      double DDSPreviousInp;
      double d;
      double loopFiltOut;
      double phErr;
      double previousSample_im;
      double previousSample_re;
      double r;
      double y_im;
      double y_re;
      int k;
      if (this->isInitialized != 1) {
        this->SystemCore_setupAndReset();
      }

      this->SystemCore_checkTunableProps();
      loopFiltOut = this->pLoopFilterState;
      DDSOut = this->pIntegFilterState;
      DDSPreviousInp = this->pDDSPreviousInput;
      previousSample_re = this->pPreviousSample.re;
      previousSample_im = this->pPreviousSample.im;
      for (k = 0; k < 25000; k++) {
        if (std::abs(previousSample_re) >= std::abs(previousSample_im)) {
          r = previousSample_re;
          if (previousSample_re < 0.0) {
            r = -1.0;
          } else if (previousSample_re > 0.0) {
            r = 1.0;
          } else {
            if (previousSample_re == 0.0) {
              r = 0.0;
            }
          }

          phErr = previousSample_im;
          if (previousSample_im < 0.0) {
            phErr = -1.0;
          } else if (previousSample_im > 0.0) {
            phErr = 1.0;
          } else {
            if (previousSample_im == 0.0) {
              phErr = 0.0;
            }
          }

          phErr = r * previousSample_im - phErr * previousSample_re *
            0.41421356237309515;
        } else {
          r = previousSample_re;
          if (previousSample_re < 0.0) {
            r = -1.0;
          } else if (previousSample_re > 0.0) {
            r = 1.0;
          } else {
            if (previousSample_re == 0.0) {
              r = 0.0;
            }
          }

          phErr = previousSample_im;
          if (previousSample_im < 0.0) {
            phErr = -1.0;
          } else if (previousSample_im > 0.0) {
            phErr = 1.0;
          } else {
            if (previousSample_im == 0.0) {
              phErr = 0.0;
            }
          }

          phErr = r * previousSample_im * 0.41421356237309515 - phErr *
            previousSample_re;
        }

        y_re = this->pPhase * 0.0;
        y_im = this->pPhase;
        if (y_im == 0.0) {
          y_re = std::exp(y_re);
          y_im = 0.0;
        } else {
          r = std::exp(y_re / 2.0);
          y_re = r * (r * std::cos(y_im));
          y_im = r * (r * std::sin(y_im));
        }

        r = varargin_1[k].re;
        d = varargin_1[k].im;
        previousSample_re = r * y_re - d * y_im;
        previousSample_im = r * y_im + d * y_re;
        varargout_1[k].re = previousSample_re;
        varargout_1[k].im = previousSample_im;
        loopFiltOut += phErr * this->pIntegratorGain;
        DDSOut += DDSPreviousInp;
        DDSPreviousInp = phErr * this->pProportionalGain + loopFiltOut;
        this->pPhase = this->pDigitalSynthesizerGain * DDSOut;
      }

      y_re = this->pActualPhaseOffset * 0.0;
      y_im = this->pActualPhaseOffset;
      if (y_im == 0.0) {
        y_re = std::exp(y_re);
        y_im = 0.0;
      } else {
        r = std::exp(y_re / 2.0);
        y_re = r * (r * std::cos(y_im));
        y_im = r * (r * std::sin(y_im));
      }

      for (k = 0; k < 25000; k++) {
        r = varargout_1[k].re;
        d = varargout_1[k].im;
        phErr = r * y_im + d * y_re;
        r = r * y_re - d * y_im;
        varargout_1[k].re = r;
        varargout_1[k].im = phErr;
      }

      this->pLoopFilterState = loopFiltOut;
      this->pIntegFilterState = DDSOut;
      this->pPreviousSample.re = previousSample_re;
      this->pPreviousSample.im = previousSample_im;
      this->pDDSPreviousInput = DDSPreviousInp;
    }

    //
    // Arguments    : void
    // Return Type  : CarrierSynchronizer *
    //
    CarrierSynchronizer *CarrierSynchronizer::init()
    {
      CarrierSynchronizer *obj;
      obj = this;
      obj->CustomPhaseOffset = 0.0;
      obj->isInitialized = 0;
      matlab::system::coder::ProcessConstructorArguments::b_do((obj));
      return obj;
    }

    //
    // Arguments    : void
    // Return Type  : boolean_T
    //
    boolean_T CarrierSynchronizer::isLockedAndNotReleased() const
    {
      return this->isInitialized == 1;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void CarrierSynchronizer::set_DampingFactor()
    {
      this->DampingFactor = 0.707;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void CarrierSynchronizer::set_NormalizedLoopBandwidth()
    {
      this->NormalizedLoopBandwidth = 0.01;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void CarrierSynchronizer::set_SamplesPerSymbol()
    {
      this->SamplesPerSymbol = 1.0;
    }

    //
    // Arguments    : const creal_T varargin_1[25000]
    //                creal_T varargout_1[25000]
    // Return Type  : void
    //
    void CarrierSynchronizer::step(const creal_T varargin_1[25000], creal_T
      varargout_1[25000])
    {
      double DDSOut;
      double DDSPreviousInp;
      double d;
      double loopFiltOut;
      double phErr;
      double previousSample_im;
      double previousSample_re;
      double r;
      double y_im;
      double y_re;
      int k;
      if (this->isInitialized != 1) {
        this->setupAndReset();
      }

      this->checkTunableProps();
      loopFiltOut = this->pLoopFilterState;
      DDSOut = this->pIntegFilterState;
      DDSPreviousInp = this->pDDSPreviousInput;
      previousSample_re = this->pPreviousSample.re;
      previousSample_im = this->pPreviousSample.im;
      for (k = 0; k < 25000; k++) {
        r = previousSample_re;
        if (previousSample_re < 0.0) {
          r = -1.0;
        } else if (previousSample_re > 0.0) {
          r = 1.0;
        } else {
          if (previousSample_re == 0.0) {
            r = 0.0;
          }
        }

        phErr = previousSample_im;
        if (previousSample_im < 0.0) {
          phErr = -1.0;
        } else if (previousSample_im > 0.0) {
          phErr = 1.0;
        } else {
          if (previousSample_im == 0.0) {
            phErr = 0.0;
          }
        }

        phErr = r * previousSample_im - phErr * previousSample_re;
        y_re = this->pPhase * 0.0;
        y_im = this->pPhase;
        if (y_im == 0.0) {
          y_re = std::exp(y_re);
          y_im = 0.0;
        } else {
          r = std::exp(y_re / 2.0);
          y_re = r * (r * std::cos(y_im));
          y_im = r * (r * std::sin(y_im));
        }

        r = varargin_1[k].re;
        d = varargin_1[k].im;
        previousSample_re = r * y_re - d * y_im;
        previousSample_im = r * y_im + d * y_re;
        varargout_1[k].re = previousSample_re;
        varargout_1[k].im = previousSample_im;
        loopFiltOut += phErr * this->pIntegratorGain;
        DDSOut += DDSPreviousInp;
        DDSPreviousInp = phErr * this->pProportionalGain + loopFiltOut;
        this->pPhase = this->pDigitalSynthesizerGain * DDSOut;
      }

      y_re = this->pActualPhaseOffset * 0.0;
      y_im = this->pActualPhaseOffset;
      if (y_im == 0.0) {
        y_re = std::exp(y_re);
        y_im = 0.0;
      } else {
        r = std::exp(y_re / 2.0);
        y_re = r * (r * std::cos(y_im));
        y_im = r * (r * std::sin(y_im));
      }

      for (k = 0; k < 25000; k++) {
        r = varargout_1[k].re;
        d = varargout_1[k].im;
        phErr = r * y_im + d * y_re;
        r = r * y_re - d * y_im;
        varargout_1[k].re = r;
        varargout_1[k].im = phErr;
      }

      this->pLoopFilterState = loopFiltOut;
      this->pIntegFilterState = DDSOut;
      this->pPreviousSample.re = previousSample_re;
      this->pPreviousSample.im = previousSample_im;
      this->pDDSPreviousInput = DDSPreviousInp;
    }
  }
}

//
// File trailer for CarrierSynchronizer.cpp
//
// [EOF]
//
