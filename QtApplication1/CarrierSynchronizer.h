//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CarrierSynchronizer.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//
#ifndef CARRIERSYNCHRONIZER_H
#define CARRIERSYNCHRONIZER_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct cell_wrap_18
{
  unsigned int f1[8];
};

namespace coder
{
  namespace comm
  {
    class CarrierSynchronizer
    {
     public:
      CarrierSynchronizer *init();
      void step(const creal_T varargin_1[25000], creal_T varargout_1[25000]);
      void setupAndReset();
      void setup();
      void checkTunableProps();
      void SystemCore_step(const creal_T varargin_1[25000], creal_T varargout_1
                           [25000]);
      void SystemCore_setupAndReset();
      void SystemCore_setup();
      void SystemCore_checkTunableProps();
      void set_DampingFactor();
      void set_NormalizedLoopBandwidth();
      void set_SamplesPerSymbol();
      boolean_T isLockedAndNotReleased() const;
      boolean_T TunablePropsChanged;
      char ModulationPhaseOffset[4];
      double CustomPhaseOffset;
      double SamplesPerSymbol;
      double DampingFactor;
      double NormalizedLoopBandwidth;
     private:
      int isInitialized;
      cell_wrap_18 inputVarSize[1];
      double pProportionalGain;
      double pIntegratorGain;
      double pDigitalSynthesizerGain;
      double pPhase;
      creal_T pPreviousSample;
      double pActualPhaseOffset;
      double pLoopFilterState;
      double pIntegFilterState;
      double pDDSPreviousInput;
    };
  }
}

#endif

//
// File trailer for CarrierSynchronizer.h
//
// [EOF]
//
