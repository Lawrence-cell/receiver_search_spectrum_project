//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SystemProp.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//
#ifndef SYSTEMPROP_H
#define SYSTEMPROP_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder
{
  namespace comm
  {
    class SymbolSynchronizer;
    class CarrierSynchronizer;
  }
}

// Type Definitions
namespace coder
{
  namespace matlab
  {
    namespace system
    {
      namespace coder
      {
        class SystemProp
        {
         public:
          static void matlabCodegenNotifyAnyProp(comm::SymbolSynchronizer *obj);
          static void matlabCodegenSetAnyProp(comm::CarrierSynchronizer *obj);
          static void matlabCodegenNotifyAnyProp(comm::CarrierSynchronizer *obj);
        };
      }
    }
  }
}

#endif

//
// File trailer for SystemProp.h
//
// [EOF]
//
