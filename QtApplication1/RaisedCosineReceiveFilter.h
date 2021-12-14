//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: RaisedCosineReceiveFilter.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//
#ifndef RAISEDCOSINERECEIVEFILTER_H
#define RAISEDCOSINERECEIVEFILTER_H

// Include Files
#include "FIRDecimator.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder
{
  namespace dspcodegen
  {
    class FIRDecimator;
  }
}

// Type Definitions
namespace coder
{
  namespace comm
  {
    class RaisedCosineReceiveFilter
    {
     public:
      RaisedCosineReceiveFilter *init();
      void step(const creal_T varargin_1[100000], creal_T varargout_1[50000]);
      void setupAndReset();
      void setup();
      void matlabCodegenDestructor();
      void release();
      void releaseWrapper();
      ~RaisedCosineReceiveFilter();
      RaisedCosineReceiveFilter();
      boolean_T matlabCodegenIsDeleted;
      dspcodegen::FIRDecimator _pobj0;
     protected:
      dspcodegen::FIRDecimator *pFilter;
     private:
      int isInitialized;
      boolean_T isSetupComplete;
    };
  }
}

#endif

//
// File trailer for RaisedCosineReceiveFilter.h
//
// [EOF]
//
