//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FIRDecimator.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "FIRDecimator.h"
#include "rt_nonfinite.h"
#include <cstring>
#include <string.h>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace coder
{
  namespace dspcodegen
  {
    void FIRDecimator::setup()
    {
      this->isSetupComplete = false;
      this->isInitialized = 1;
      this->isSetupComplete = true;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void FIRDecimator::setupAndReset()
    {
      this->setup();

      // System object Initialization function: dsp.FIRDecimator
      this->cSFunObject.W2_CoeffIdx = 21;
      this->cSFunObject.W0_PhaseIdx = 1;
      this->cSFunObject.W4_TapDelayIndex = 20;
      this->cSFunObject.W1_Sums.re = 0.0;
      this->cSFunObject.W1_Sums.im = 0.0;
      std::memset(&this->cSFunObject.W3_StatesBuff[0], 0, 40U * sizeof(creal_T));
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    FIRDecimator::FIRDecimator()
    {
      this->matlabCodegenIsDeleted = true;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    FIRDecimator::~FIRDecimator()
    {
      this->matlabCodegenDestructor();
    }

    //
    // Arguments    : void
    // Return Type  : FIRDecimator *
    //
    FIRDecimator *FIRDecimator::init()
    {
      static const double b_dv[42] = { -0.0041037526379487559,
        0.014842378087392853, -1.0721878409242424E-17, -0.029113895479116733,
        0.010632450016503588, 0.051980866747350807, -0.036045775355096926,
        -0.10001777868186816, 0.12616021374283923, 0.46782780072615732,
        0.46782780072615732, 0.12616021374283923, -0.10001777868186816,
        -0.036045775355096926, 0.051980866747350807, 0.010632450016503588,
        -0.029113895479116733, -1.0721878409242424E-17, 0.014842378087392853,
        -0.0041037526379487559, 0.0, -0.00848977273295494, 0.0061032595700433925,
        0.013681487697665758, -0.018970551677554924, -0.018868980313045666,
        0.042448863664774704, 0.023297350931244683, -0.092382991348415489,
        -0.026277767069145433, 0.3136098240355385, 0.52741770572179669,
        0.3136098240355385, -0.026277767069145433, -0.092382991348415489,
        0.023297350931244683, 0.042448863664774704, -0.018868980313045666,
        -0.018970551677554924, 0.013681487697665758, 0.0061032595700433925,
        -0.00848977273295494 };

      FIRDecimator *obj;
      obj = this;
      obj->isInitialized = 0;

      // System object Constructor function: dsp.FIRDecimator
      obj->cSFunObject.P0_IC.re = 0.0;
      obj->cSFunObject.P0_IC.im = 0.0;
      for (int i = 0; i < 42; i++) {
        obj->cSFunObject.P1_FILT[i] = b_dv[i];
      }

      obj->matlabCodegenIsDeleted = false;
      return obj;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void FIRDecimator::matlabCodegenDestructor()
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
    void FIRDecimator::release()
    {
      if (this->isInitialized == 1) {
        this->isInitialized = 2;
      }
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void FIRDecimator::reset()
    {
      if (this->isInitialized == 1) {
        // System object Initialization function: dsp.FIRDecimator
        this->cSFunObject.W2_CoeffIdx = 21;
        this->cSFunObject.W0_PhaseIdx = 1;
        this->cSFunObject.W4_TapDelayIndex = 20;
        this->cSFunObject.W1_Sums.re = 0.0;
        this->cSFunObject.W1_Sums.im = 0.0;
        std::memset(&this->cSFunObject.W3_StatesBuff[0], 0, 40U * sizeof(creal_T));
      }
    }

    //
    // Arguments    : const creal_T varargin_1[100000]
    //                creal_T varargout_1[50000]
    // Return Type  : void
    //
    void FIRDecimator::step(const creal_T varargin_1[100000], creal_T
      varargout_1[50000])
    {
      dsp_FIRDecimator_0 *obj;
      int cffIdx;
      int curTapIdx;
      int i;
      int maxWindow;
      int outBufIdx;
      int phaseIdx;
      if (this->isInitialized != 1) {
        this->setupAndReset();
      }

      obj = &this->cSFunObject;

      // System object Outputs function: dsp.FIRDecimator
      i = 0;
      curTapIdx = this->cSFunObject.W4_TapDelayIndex;
      phaseIdx = this->cSFunObject.W0_PhaseIdx;
      cffIdx = this->cSFunObject.W2_CoeffIdx;
      outBufIdx = 0;
      maxWindow = (phaseIdx + 1) * 20;
      for (int iIdx = 0; iIdx < 100000; iIdx++) {
        int jIdx;
        obj->W1_Sums.re += varargin_1[i].re * obj->P1_FILT[cffIdx];
        obj->W1_Sums.im += varargin_1[i].im * obj->P1_FILT[cffIdx];
        cffIdx++;
        for (jIdx = curTapIdx + 1; jIdx < maxWindow; jIdx++) {
          obj->W1_Sums.re += obj->W3_StatesBuff[jIdx].re * obj->P1_FILT[cffIdx];
          obj->W1_Sums.im += obj->W3_StatesBuff[jIdx].im * obj->P1_FILT[cffIdx];
          cffIdx++;
        }

        for (jIdx = maxWindow - 20; jIdx <= curTapIdx; jIdx++) {
          obj->W1_Sums.re += obj->W3_StatesBuff[jIdx].re * obj->P1_FILT[cffIdx];
          obj->W1_Sums.im += obj->W3_StatesBuff[jIdx].im * obj->P1_FILT[cffIdx];
          cffIdx++;
        }

        obj->W3_StatesBuff[curTapIdx] = varargin_1[i];
        i++;
        curTapIdx += 20;
        if (curTapIdx >= 40) {
          curTapIdx -= 40;
        }

        phaseIdx++;
        if (phaseIdx < 2) {
          maxWindow += 20;
        } else {
          obj->O0_Y0[outBufIdx] = obj->W1_Sums;
          outBufIdx++;
          obj->W1_Sums.re = 0.0;
          obj->W1_Sums.im = 0.0;
          phaseIdx = 0;
          cffIdx = 0;
          curTapIdx--;
          if (curTapIdx < 0) {
            curTapIdx += 20;
          }

          maxWindow = 20;
        }
      }

      this->cSFunObject.W4_TapDelayIndex = curTapIdx;
      this->cSFunObject.W2_CoeffIdx = cffIdx;
      this->cSFunObject.W0_PhaseIdx = phaseIdx;
      for (i = 0; i < 50000; i++) {
        varargout_1[i] = this->cSFunObject.O0_Y0[i];
      }
    }
  }
}

//
// File trailer for FIRDecimator.cpp
//
// [EOF]
//
