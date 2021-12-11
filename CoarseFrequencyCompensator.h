//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CoarseFrequencyCompensator.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//
#ifndef COARSEFREQUENCYCOMPENSATOR_H
#define COARSEFREQUENCYCOMPENSATOR_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder
{
  namespace comm
  {
    class CoarseFrequencyCompensator
    {
     public:
      CoarseFrequencyCompensator *init();
      CoarseFrequencyCompensator *b_init();
      void step(const creal_T varargin_1[25000], creal_T varargout_1[25000]);
      void setupAndReset();
      void setup();
      void step(const creal_T varargin_1[25000], creal_T varargout_1[25000],
                double *varargout_2);
      void matlabCodegenDestructor();
      void release();
      void handle_matlabCodegenDestructor();
      ~CoarseFrequencyCompensator();
      CoarseFrequencyCompensator();
     protected:
      static double FFTEstimateOffset(const creal_T x[25000]);
      static double b_FFTEstimateOffset(const creal_T x[25000]);
     private:
      void SystemCore_delete();
     public:
      boolean_T matlabCodegenIsDeleted;
     protected:
      creal_T pRaisedSignalBuffer[1024];
      double pCumFreqOffset;
     private:
      int isInitialized;
      boolean_T isSetupComplete;
    };
  }
}

#endif

//
// File trailer for CoarseFrequencyCompensator.h
//
// [EOF]
//
