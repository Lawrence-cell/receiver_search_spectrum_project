//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: RaisedCosineReceiveFilter.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "RaisedCosineReceiveFilter.h"
#include "FIRDecimator.h"
#include "rt_nonfinite.h"
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
    void RaisedCosineReceiveFilter::release()
    {
      if (this->isInitialized == 1) {
        this->isInitialized = 2;
        this->releaseWrapper();
      }
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void RaisedCosineReceiveFilter::releaseWrapper()
    {
      if (this->isSetupComplete) {
        this->pFilter->release();
      }
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void RaisedCosineReceiveFilter::setup()
    {
      dspcodegen::FIRDecimator *filt;
      this->isSetupComplete = false;
      this->isInitialized = 1;
      filt = this->_pobj0.init();
      this->pFilter = filt;
      this->isSetupComplete = true;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void RaisedCosineReceiveFilter::setupAndReset()
    {
      this->setup();
      this->pFilter->reset();
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    RaisedCosineReceiveFilter::RaisedCosineReceiveFilter()
    {
      this->matlabCodegenIsDeleted = true;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    RaisedCosineReceiveFilter::~RaisedCosineReceiveFilter()
    {
      this->matlabCodegenDestructor();
    }

    //
    // Arguments    : void
    // Return Type  : RaisedCosineReceiveFilter *
    //
    RaisedCosineReceiveFilter *RaisedCosineReceiveFilter::init()
    {
      RaisedCosineReceiveFilter *obj;
      obj = this;
      obj->isInitialized = 0;
      obj->matlabCodegenIsDeleted = false;
      return obj;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void RaisedCosineReceiveFilter::matlabCodegenDestructor()
    {
      if (!this->matlabCodegenIsDeleted) {
        this->matlabCodegenIsDeleted = true;
        this->release();
      }
    }

    //
    // Arguments    : const creal_T varargin_1[100000]
    //                creal_T varargout_1[50000]
    // Return Type  : void
    //
    void RaisedCosineReceiveFilter::step(const creal_T varargin_1[100000],
      creal_T varargout_1[50000])
    {
      if (this->isInitialized != 1) {
        this->setupAndReset();
      }

      this->pFilter->step(varargin_1, varargout_1);
    }
  }
}

//
// File trailer for RaisedCosineReceiveFilter.cpp
//
// [EOF]
//
