//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SystemProp.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "SystemProp.h"
#include "CarrierSynchronizer.h"
#include "SymbolSynchronizer.h"
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
        void SystemProp::matlabCodegenNotifyAnyProp(comm::SymbolSynchronizer
          *obj)
        {
          if (obj->isLockedAndNotReleased()) {
            obj->TunablePropsChanged = true;
          }
        }

        //
        // Arguments    : comm::CarrierSynchronizer *obj
        // Return Type  : void
        //
        void SystemProp::matlabCodegenNotifyAnyProp(comm::CarrierSynchronizer
          *obj)
        {
          if (obj->isLockedAndNotReleased()) {
            obj->TunablePropsChanged = true;
          }
        }

        //
        // Arguments    : comm::CarrierSynchronizer *obj
        // Return Type  : void
        //
        void SystemProp::matlabCodegenSetAnyProp(comm::CarrierSynchronizer *obj)
        {
          SystemProp::matlabCodegenNotifyAnyProp((obj));
          obj->ModulationPhaseOffset[0] = 'A';
          obj->ModulationPhaseOffset[1] = 'u';
          obj->ModulationPhaseOffset[2] = 't';
          obj->ModulationPhaseOffset[3] = 'o';
        }
      }
    }
  }
}

//
// File trailer for SystemProp.cpp
//
// [EOF]
//
