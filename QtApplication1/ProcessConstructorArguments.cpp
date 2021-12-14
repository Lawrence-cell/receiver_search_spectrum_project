//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ProcessConstructorArguments.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "ProcessConstructorArguments.h"
#include "CarrierSynchronizer.h"
#include "SymbolSynchronizer.h"
#include "SystemProp.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
//
// Arguments    : comm::SymbolSynchronizer *obj
// Return Type  : void
//
namespace coder
{
  namespace matlab
  {
    namespace system
    {
      namespace coder
      {
        void ProcessConstructorArguments::b_do(comm::SymbolSynchronizer *obj)
        {
          SystemProp::matlabCodegenNotifyAnyProp((obj));
          obj->set_DampingFactor();
          SystemProp::matlabCodegenNotifyAnyProp((obj));
          obj->set_NormalizedLoopBandwidth();
        }

        //
        // Arguments    : comm::CarrierSynchronizer *obj
        // Return Type  : void
        //
        void ProcessConstructorArguments::b_do(comm::CarrierSynchronizer *obj)
        {
          SystemProp::matlabCodegenNotifyAnyProp((obj));
          obj->set_DampingFactor();
          SystemProp::matlabCodegenNotifyAnyProp((obj));
          obj->set_NormalizedLoopBandwidth();
          SystemProp::matlabCodegenNotifyAnyProp((obj));
          obj->set_SamplesPerSymbol();
          SystemProp::matlabCodegenSetAnyProp((obj));
        }
      }
    }
  }
}

//
// File trailer for ProcessConstructorArguments.cpp
//
// [EOF]
//
