//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sort.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "sort.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"
#include <cstring>
#include <string.h>

// Function Definitions
//
// Arguments    : int x_data[]
//                const int x_size[1]
// Return Type  : void
//
namespace coder
{
  namespace internal
  {
    void sort(int x_data[], const int x_size[1])
    {
      int b_iwork_data[200];
      int iidx_data[200];
      int iwork_data[200];
      int vwork_data[200];
      int xwork_data[200];
      int x4[4];
      int dim;
      int i1;
      int i2;
      int vlen;
      int vstride;
      int vwork_size_idx_0;
      short idx4[4];
      signed char perm[4];
      dim = 0;
      if (x_size[0] != 1) {
        dim = -1;
      }

      if (dim + 2 <= 1) {
        vwork_size_idx_0 = x_size[0];
      } else {
        vwork_size_idx_0 = 1;
      }

      vlen = vwork_size_idx_0 - 1;
      vstride = 1;
      for (i2 = 0; i2 <= dim; i2++) {
        vstride *= x_size[0];
      }

      for (int j = 0; j < vstride; j++) {
        for (i2 = 0; i2 <= vlen; i2++) {
          vwork_data[i2] = x_data[j + i2 * vstride];
        }

        dim = static_cast<unsigned char>(vwork_size_idx_0);
        if (0 <= dim - 1) {
          std::memset(&iidx_data[0], 0, dim * sizeof(int));
        }

        if (vwork_size_idx_0 != 0) {
          int i4;
          int iwork_size_idx_0;
          int nDone;
          int nQuartets;
          x4[0] = 0;
          idx4[0] = 0;
          x4[1] = 0;
          idx4[1] = 0;
          x4[2] = 0;
          idx4[2] = 0;
          x4[3] = 0;
          idx4[3] = 0;
          dim = static_cast<unsigned char>(vwork_size_idx_0);
          iwork_size_idx_0 = static_cast<unsigned char>(vwork_size_idx_0);
          if (0 <= dim - 1) {
            std::memset(&iwork_data[0], 0, dim * sizeof(int));
          }

          if (0 <= vwork_size_idx_0 - 1) {
            std::memset(&xwork_data[0], 0, vwork_size_idx_0 * sizeof(int));
          }

          nQuartets = vwork_size_idx_0 >> 2;
          for (int b_j = 0; b_j < nQuartets; b_j++) {
            int b_i;
            int i;
            i = b_j << 2;
            idx4[0] = static_cast<short>(i + 1);
            idx4[1] = static_cast<short>(i + 2);
            idx4[2] = static_cast<short>(i + 3);
            idx4[3] = static_cast<short>(i + 4);
            b_i = vwork_data[i];
            x4[0] = b_i;
            dim = vwork_data[i + 1];
            x4[1] = dim;
            i4 = vwork_data[i + 2];
            x4[2] = i4;
            nDone = vwork_data[i + 3];
            x4[3] = nDone;
            if (b_i <= dim) {
              i1 = 1;
              i2 = 2;
            } else {
              i1 = 2;
              i2 = 1;
            }

            if (i4 <= nDone) {
              dim = 3;
              i4 = 4;
            } else {
              dim = 4;
              i4 = 3;
            }

            b_i = x4[i1 - 1];
            nDone = x4[dim - 1];
            if (b_i <= nDone) {
              b_i = x4[i2 - 1];
              if (b_i <= nDone) {
                perm[0] = static_cast<signed char>(i1);
                perm[1] = static_cast<signed char>(i2);
                perm[2] = static_cast<signed char>(dim);
                perm[3] = static_cast<signed char>(i4);
              } else if (b_i <= x4[i4 - 1]) {
                perm[0] = static_cast<signed char>(i1);
                perm[1] = static_cast<signed char>(dim);
                perm[2] = static_cast<signed char>(i2);
                perm[3] = static_cast<signed char>(i4);
              } else {
                perm[0] = static_cast<signed char>(i1);
                perm[1] = static_cast<signed char>(dim);
                perm[2] = static_cast<signed char>(i4);
                perm[3] = static_cast<signed char>(i2);
              }
            } else {
              nDone = x4[i4 - 1];
              if (b_i <= nDone) {
                if (x4[i2 - 1] <= nDone) {
                  perm[0] = static_cast<signed char>(dim);
                  perm[1] = static_cast<signed char>(i1);
                  perm[2] = static_cast<signed char>(i2);
                  perm[3] = static_cast<signed char>(i4);
                } else {
                  perm[0] = static_cast<signed char>(dim);
                  perm[1] = static_cast<signed char>(i1);
                  perm[2] = static_cast<signed char>(i4);
                  perm[3] = static_cast<signed char>(i2);
                }
              } else {
                perm[0] = static_cast<signed char>(dim);
                perm[1] = static_cast<signed char>(i4);
                perm[2] = static_cast<signed char>(i1);
                perm[3] = static_cast<signed char>(i2);
              }
            }

            iidx_data[i] = idx4[perm[0] - 1];
            iidx_data[i + 1] = idx4[perm[1] - 1];
            iidx_data[i + 2] = idx4[perm[2] - 1];
            iidx_data[i + 3] = idx4[perm[3] - 1];
            vwork_data[i] = x4[perm[0] - 1];
            vwork_data[i + 1] = x4[perm[1] - 1];
            vwork_data[i + 2] = x4[perm[2] - 1];
            vwork_data[i + 3] = x4[perm[3] - 1];
          }

          nDone = nQuartets << 2;
          i1 = (vwork_size_idx_0 - nDone) - 1;
          if (i1 + 1 > 0) {
            for (i2 = 0; i2 <= i1; i2++) {
              dim = nDone + i2;
              idx4[i2] = static_cast<short>(dim + 1);
              x4[i2] = vwork_data[dim];
            }

            perm[1] = 0;
            perm[2] = 0;
            perm[3] = 0;
            if (i1 + 1 == 1) {
              perm[0] = 1;
            } else if (i1 + 1 == 2) {
              if (x4[0] <= x4[1]) {
                perm[0] = 1;
                perm[1] = 2;
              } else {
                perm[0] = 2;
                perm[1] = 1;
              }
            } else if (x4[0] <= x4[1]) {
              if (x4[1] <= x4[2]) {
                perm[0] = 1;
                perm[1] = 2;
                perm[2] = 3;
              } else if (x4[0] <= x4[2]) {
                perm[0] = 1;
                perm[1] = 3;
                perm[2] = 2;
              } else {
                perm[0] = 3;
                perm[1] = 1;
                perm[2] = 2;
              }
            } else if (x4[0] <= x4[2]) {
              perm[0] = 2;
              perm[1] = 1;
              perm[2] = 3;
            } else if (x4[1] <= x4[2]) {
              perm[0] = 2;
              perm[1] = 3;
              perm[2] = 1;
            } else {
              perm[0] = 3;
              perm[1] = 2;
              perm[2] = 1;
            }

            for (i2 = 0; i2 <= i1; i2++) {
              dim = perm[i2] - 1;
              i4 = nDone + i2;
              iidx_data[i4] = idx4[dim];
              vwork_data[i4] = x4[dim];
            }
          }

          if (vwork_size_idx_0 > 1) {
            i1 = vwork_size_idx_0 >> 2;
            nDone = 4;
            while (i1 > 1) {
              if ((i1 & 1) != 0) {
                i1--;
                dim = nDone * i1;
                i4 = vwork_size_idx_0 - dim;
                if (i4 > nDone) {
                  merge(iidx_data, vwork_data, dim, nDone, i4 - nDone,
                        iwork_data, xwork_data);
                }
              }

              dim = nDone << 1;
              i1 >>= 1;
              for (i2 = 0; i2 < i1; i2++) {
                merge(iidx_data, vwork_data, i2 * dim, nDone, nDone, iwork_data,
                      xwork_data);
              }

              nDone = dim;
            }

            if (vwork_size_idx_0 > nDone) {
              if (0 <= iwork_size_idx_0 - 1) {
                std::memcpy(&b_iwork_data[0], &iwork_data[0], iwork_size_idx_0 *
                            sizeof(int));
              }

              if (0 <= vwork_size_idx_0 - 1) {
                std::memcpy(&iwork_data[0], &xwork_data[0], vwork_size_idx_0 *
                            sizeof(int));
              }

              merge(iidx_data, vwork_data, 0, nDone, vwork_size_idx_0 - nDone,
                    b_iwork_data, iwork_data);
            }
          }
        }

        for (i2 = 0; i2 <= vlen; i2++) {
          x_data[j + i2 * vstride] = vwork_data[i2];
        }
      }
    }
  }
}

//
// File trailer for sort.cpp
//
// [EOF]
//
