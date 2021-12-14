//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SymbolSynchronizer.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//
#ifndef SYMBOLSYNCHRONIZER_H
#define SYMBOLSYNCHRONIZER_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder
{
  namespace comm
  {
    class SymbolSynchronizer
    {
     public:
      SymbolSynchronizer *init();
      boolean_T isLockedAndNotReleased() const;
      void set_DampingFactor();
      void set_NormalizedLoopBandwidth();
      void step(const creal_T varargin_1[50000], ::coder::array<creal_T, 1U>
                &varargout_1);
      void setupAndReset();
      void setup();
      void checkTunableProps();
      void matlabCodegenDestructor();
      void release();
      ~SymbolSynchronizer();
      SymbolSynchronizer();
      boolean_T matlabCodegenIsDeleted;
      boolean_T TunablePropsChanged;
      double DampingFactor;
      double NormalizedLoopBandwidth;
      double DetectorGain;
     private:
      int isInitialized;
      boolean_T isSetupComplete;
      double pProportionalGain;
      double pIntegratorGain;
      creal_T pInterpFilterState[3];
      double pMu;
      creal_T pTEDBuffer[2];
      boolean_T pStrobe;
      double pNumStrobe;
      boolean_T pStrobeHistory[2];
      double pNCOCounter;
      double pTimingError[50000];
      creal_T pSymbolHolder[27500];
      double pLoopFilterState;
      double pLoopPreviousInput;
    };
  }
}

#endif

//
// File trailer for SymbolSynchronizer.h
//
// [EOF]
//
