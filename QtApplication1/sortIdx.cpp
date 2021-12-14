//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sortIdx.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "sortIdx.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
//
// Arguments    : int idx_data[]
//                int x_data[]
//                int offset
//                int np
//                int nq
//                int iwork_data[]
//                int xwork_data[]
// Return Type  : void
//
namespace coder
{
  namespace internal
  {
    void merge(int idx_data[], int x_data[], int offset, int np, int nq, int
               iwork_data[], int xwork_data[])
    {
      if (nq != 0) {
        int iout;
        int j;
        int n_tmp;
        int p;
        int q;
        n_tmp = np + nq;
        for (j = 0; j < n_tmp; j++) {
          iout = offset + j;
          iwork_data[j] = idx_data[iout];
          xwork_data[j] = x_data[iout];
        }

        p = 0;
        q = np;
        iout = offset - 1;
        int exitg1;
        do {
          exitg1 = 0;
          iout++;
          if (xwork_data[p] <= xwork_data[q]) {
            idx_data[iout] = iwork_data[p];
            x_data[iout] = xwork_data[p];
            if (p + 1 < np) {
              p++;
            } else {
              exitg1 = 1;
            }
          } else {
            idx_data[iout] = iwork_data[q];
            x_data[iout] = xwork_data[q];
            if (q + 1 < n_tmp) {
              q++;
            } else {
              q = iout - p;
              for (j = p + 1; j <= np; j++) {
                iout = q + j;
                idx_data[iout] = iwork_data[j - 1];
                x_data[iout] = xwork_data[j - 1];
              }

              exitg1 = 1;
            }
          }
        } while (exitg1 == 0);
      }
    }
  }
}

//
// File trailer for sortIdx.cpp
//
// [EOF]
//
