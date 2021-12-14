//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: findpeaks.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "findpeaks.h"
#include "eml_setop.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "rt_nonfinite.h"
#include <cstring>
#include <string.h>

// Function Definitions
//
// Arguments    : const double Yin[100]
//                double Ypk_data[]
//                int Ypk_size[1]
//                double Xpk_data[]
//                int Xpk_size[1]
// Return Type  : void
//
namespace coder
{
  void findpeaks(const double Yin[100], double Ypk_data[], int Ypk_size[1],
                 double Xpk_data[], int Xpk_size[1])
  {
    double yk;
    double ykfirst;
    int c_data[200];
    int idx_data[200];
    int iwork_data[200];
    int sortIdx_data[200];
    int b_iFinite_data[100];
    int iInfinite_data[100];
    int iInflect_data[100];
    int iPk_data[100];
    int c_size[1];
    int iFinite_size[1];
    int iInfinite_size[1];
    int iInflect_size[1];
    int iPk_size[1];
    int idx_size[1];
    int i;
    int k;
    int kfirst;
    int n;
    int nInf;
    int nPk;
    int p;
    int qEnd;
    unsigned char b_tmp_data[200];
    signed char locs_temp_data[200];
    signed char iFinite_data[100];
    char dir;
    boolean_T idelete_data[200];
    boolean_T tmp_data[200];
    boolean_T isinfykfirst;
    nPk = -1;
    nInf = -1;
    dir = 'n';
    kfirst = -1;
    ykfirst = rtInf;
    isinfykfirst = true;
    for (k = 0; k < 100; k++) {
      boolean_T isinfyk;
      yk = Yin[k];
      if (rtIsNaN(yk)) {
        yk = rtInf;
        isinfyk = true;
      } else if (rtIsInf(yk) && (yk > 0.0)) {
        isinfyk = true;
        nInf++;
        iInfinite_data[nInf] = k + 1;
      } else {
        isinfyk = false;
      }

      if (yk != ykfirst) {
        char previousdir;
        previousdir = dir;
        if (isinfyk || isinfykfirst) {
          dir = 'n';
        } else if (yk < ykfirst) {
          dir = 'd';
          if (('d' != previousdir) && (previousdir == 'i')) {
            nPk++;
            b_iFinite_data[nPk] = kfirst + 1;
          }
        } else {
          dir = 'i';
        }

        ykfirst = yk;
        kfirst = k;
        isinfykfirst = isinfyk;
      }
    }

    if (1 > nPk + 1) {
      p = -1;
    } else {
      p = nPk;
    }

    kfirst = p + 1;
    for (i = 0; i <= p; i++) {
      iFinite_data[i] = static_cast<signed char>(b_iFinite_data[i]);
    }

    for (i = 0; i < kfirst; i++) {
      b_iFinite_data[i] = iFinite_data[i];
    }

    if (1 > nInf + 1) {
      kfirst = -1;
    } else {
      kfirst = nInf;
    }

    nPk = kfirst + 1;
    for (i = 0; i <= kfirst; i++) {
      iFinite_data[i] = static_cast<signed char>(iInfinite_data[i]);
    }

    iInfinite_size[0] = kfirst + 1;
    for (i = 0; i < nPk; i++) {
      iInfinite_data[i] = iFinite_data[i];
    }

    nPk = 0;
    n = p + 1;
    for (k = 0; k < n; k++) {
      i = b_iFinite_data[k];
      yk = Yin[i - 1];
      if (yk > 0.3) {
        ykfirst = Yin[i];
        if ((Yin[i - 2] > ykfirst) || rtIsNaN(ykfirst)) {
          ykfirst = Yin[i - 2];
        } else {
          ykfirst = Yin[i];
        }

        if (yk - ykfirst >= 0.0) {
          nPk++;
          iPk_data[nPk - 1] = i;
        }
      }
    }

    if (1 > nPk) {
      iPk_size[0] = 0;
    } else {
      iPk_size[0] = nPk;
    }

    do_vectors(iPk_data, iPk_size, iInfinite_data, iInfinite_size, c_data,
               c_size, iInflect_data, iInflect_size, b_iFinite_data,
               iFinite_size);
    if (c_size[0] == 0) {
      idx_size[0] = 0;
    } else {
      int b_i;
      int sortIdx_size_idx_0;
      n = c_size[0] + 1;
      sortIdx_size_idx_0 = static_cast<unsigned char>(c_size[0]);
      p = static_cast<unsigned char>(c_size[0]);
      if (0 <= p - 1) {
        std::memset(&sortIdx_data[0], 0, p * sizeof(int));
      }

      i = c_size[0] - 1;
      for (k = 1; k <= i; k += 2) {
        yk = Yin[c_data[k - 1] - 1];
        if ((yk >= Yin[c_data[k] - 1]) || rtIsNaN(yk)) {
          sortIdx_data[k - 1] = k;
          sortIdx_data[k] = k + 1;
        } else {
          sortIdx_data[k - 1] = k + 1;
          sortIdx_data[k] = k;
        }
      }

      if ((c_size[0] & 1) != 0) {
        sortIdx_data[c_size[0] - 1] = c_size[0];
      }

      b_i = 2;
      while (b_i < n - 1) {
        kfirst = b_i << 1;
        nPk = 1;
        for (nInf = b_i + 1; nInf < n; nInf = qEnd + b_i) {
          int kEnd;
          int q;
          p = nPk - 1;
          q = nInf;
          qEnd = nPk + kfirst;
          if (qEnd > n) {
            qEnd = n;
          }

          k = 0;
          kEnd = qEnd - nPk;
          while (k + 1 <= kEnd) {
            yk = Yin[c_data[sortIdx_data[p] - 1] - 1];
            i = sortIdx_data[q - 1];
            if ((yk >= Yin[c_data[i - 1] - 1]) || rtIsNaN(yk)) {
              iwork_data[k] = sortIdx_data[p];
              p++;
              if (p + 1 == nInf) {
                while (q < qEnd) {
                  k++;
                  iwork_data[k] = sortIdx_data[q - 1];
                  q++;
                }
              }
            } else {
              iwork_data[k] = i;
              q++;
              if (q == qEnd) {
                while (p + 1 < nInf) {
                  k++;
                  iwork_data[k] = sortIdx_data[p];
                  p++;
                }
              }
            }

            k++;
          }

          for (k = 0; k < kEnd; k++) {
            sortIdx_data[(nPk + k) - 1] = iwork_data[k];
          }

          nPk = qEnd;
        }

        b_i = kfirst;
      }

      for (i = 0; i < sortIdx_size_idx_0; i++) {
        locs_temp_data[i] = static_cast<signed char>(static_cast<signed char>
          (c_data[sortIdx_data[i] - 1] - 1) + 1);
      }

      if (0 <= sortIdx_size_idx_0 - 1) {
        std::memset(&idelete_data[0], 0, sortIdx_size_idx_0 * sizeof(boolean_T));
      }

      for (b_i = 0; b_i < sortIdx_size_idx_0; b_i++) {
        if (!idelete_data[b_i]) {
          i = sortIdx_data[b_i];
          for (kfirst = 0; kfirst < sortIdx_size_idx_0; kfirst++) {
            signed char i1;
            nPk = static_cast<signed char>(static_cast<signed char>(c_data[i - 1]
              - 1) + 1);
            i1 = locs_temp_data[kfirst];
            tmp_data[kfirst] = ((i1 >= nPk - 5) && (i1 <= nPk + 5));
          }

          for (i = 0; i < sortIdx_size_idx_0; i++) {
            idelete_data[i] = (idelete_data[i] || tmp_data[i]);
          }

          idelete_data[b_i] = false;
        }
      }

      kfirst = static_cast<unsigned char>(c_size[0]) - 1;
      nInf = 0;
      nPk = 0;
      for (b_i = 0; b_i <= kfirst; b_i++) {
        if (!idelete_data[b_i]) {
          nInf++;
          b_tmp_data[nPk] = static_cast<unsigned char>(b_i + 1);
          nPk++;
        }
      }

      idx_size[0] = nInf;
      for (i = 0; i < nInf; i++) {
        idx_data[i] = sortIdx_data[b_tmp_data[i] - 1];
      }

      internal::sort(idx_data, idx_size);
    }

    if (idx_size[0] > 100) {
      std::memcpy(&sortIdx_data[0], &idx_data[0], 100U * sizeof(int));
      idx_size[0] = 100;
      std::memcpy(&idx_data[0], &sortIdx_data[0], 100U * sizeof(int));
    }

    kfirst = idx_size[0];
    p = idx_size[0];
    for (i = 0; i < p; i++) {
      iwork_data[i] = c_data[idx_data[i] - 1];
    }

    Ypk_size[0] = idx_size[0];
    for (i = 0; i < kfirst; i++) {
      Ypk_data[i] = Yin[iwork_data[i] - 1];
    }

    Xpk_size[0] = idx_size[0];
    for (i = 0; i < kfirst; i++) {
      Xpk_data[i] = static_cast<signed char>(static_cast<signed char>
        (iwork_data[i] - 1) + 1);
    }
  }
}

//
// File trailer for findpeaks.cpp
//
// [EOF]
//
