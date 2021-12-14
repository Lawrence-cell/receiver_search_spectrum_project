//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FIRDecimator.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//
#ifndef FIRDECIMATOR_H
#define FIRDECIMATOR_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct dsp_FIRDecimator_0
{
  int S0_isInitialized;
  int W0_PhaseIdx;
  creal_T W1_Sums;
  int W2_CoeffIdx;
  creal_T W3_StatesBuff[40];
  int W4_TapDelayIndex;
  int W5_PrevNumChan;
  creal_T P0_IC;
  double P1_FILT[42];
  creal_T O0_Y0[50000];
};

namespace coder
{
  namespace dspcodegen
  {
    class FIRDecimator
    {
     public:
      FIRDecimator *init();
      void reset();
      void step(const creal_T varargin_1[100000], creal_T varargout_1[50000]);
      void setupAndReset();
      void setup();
      void matlabCodegenDestructor();
      void release();
      ~FIRDecimator();
      FIRDecimator();
      boolean_T matlabCodegenIsDeleted;
     private:
      int isInitialized;
      boolean_T isSetupComplete;
      dsp_FIRDecimator_0 cSFunObject;
    };
  }
}

#endif

//
// File trailer for FIRDecimator.h
//
// [EOF]
//
