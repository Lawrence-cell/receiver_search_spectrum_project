//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ProcessConstructorArguments.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//
#ifndef PROCESSCONSTRUCTORARGUMENTS_H
#define PROCESSCONSTRUCTORARGUMENTS_H

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
        class ProcessConstructorArguments
        {
         public:
          static void b_do(comm::SymbolSynchronizer *obj);
          static void b_do(comm::CarrierSynchronizer *obj);
        };
      }
    }
  }
}

#endif

//
// File trailer for ProcessConstructorArguments.h
//
// [EOF]
//
