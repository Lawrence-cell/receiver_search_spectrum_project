//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: relop.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "relop.h"
#include "detect_recognize_rtwutil.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>
#include <string.h>

// Function Declarations
namespace coder
{
  namespace internal
  {
    static boolean_T iseq(double x, double y);
  }
}

// Function Definitions
//
// Arguments    : double x
//                double y
// Return Type  : boolean_T
//
namespace coder
{
  namespace internal
  {
    static boolean_T iseq(double x, double y)
    {
      double absx;
      int exponent;
      boolean_T p;
      absx = std::abs(y / 2.0);
      if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
        if (absx <= 2.2250738585072014E-308) {
          absx = 4.94065645841247E-324;
        } else {
          frexp(absx, &exponent);
          absx = std::ldexp(1.0, exponent - 53);
        }
      } else {
        absx = rtNaN;
      }

      if ((std::abs(y - x) < absx) || (rtIsInf(x) && rtIsInf(y) && ((x > 0.0) ==
            (y > 0.0)))) {
        p = true;
      } else {
        p = false;
      }

      return p;
    }

    //
    // Arguments    : const creal_T a
    //                const creal_T b
    // Return Type  : boolean_T
    //
    boolean_T relop(const creal_T a, const creal_T b)
    {
      boolean_T p;
      if (rtIsNaN(b.re) || rtIsNaN(b.im)) {
        p = false;
      } else if (rtIsNaN(a.re) || rtIsNaN(a.im)) {
        p = true;
      } else {
        double absai;
        double absbi;
        double ma;
        double mb;
        boolean_T SCALEA;
        boolean_T SCALEB;
        ma = std::abs(a.re);
        if ((ma > 8.9884656743115785E+307) || (std::abs(a.im) >
             8.9884656743115785E+307)) {
          SCALEA = true;
        } else {
          SCALEA = false;
        }

        mb = std::abs(b.re);
        if ((mb > 8.9884656743115785E+307) || (std::abs(b.im) >
             8.9884656743115785E+307)) {
          SCALEB = true;
        } else {
          SCALEB = false;
        }

        if (SCALEA || SCALEB) {
          absai = rt_hypotd_snf(a.re / 2.0, a.im / 2.0);
          absbi = rt_hypotd_snf(b.re / 2.0, b.im / 2.0);
        } else {
          absai = rt_hypotd_snf(a.re, a.im);
          absbi = rt_hypotd_snf(b.re, b.im);
        }

        if (iseq(absai, absbi)) {
          double Ma;
          double Mb;
          absai = std::abs(a.im);
          absbi = std::abs(b.im);
          if (ma > absai) {
            Ma = ma;
            ma = absai;
          } else {
            Ma = absai;
          }

          if (mb > absbi) {
            Mb = mb;
            mb = absbi;
          } else {
            Mb = absbi;
          }

          if (Ma > Mb) {
            if (ma < mb) {
              absai = Ma - Mb;
              absbi = (ma / 2.0 + mb / 2.0) / (Ma / 2.0 + Mb / 2.0) * (mb - ma);
            } else {
              absai = Ma;
              absbi = Mb;
            }
          } else if (Ma < Mb) {
            if (ma > mb) {
              absbi = Mb - Ma;
              absai = (ma / 2.0 + mb / 2.0) / (Ma / 2.0 + Mb / 2.0) * (ma - mb);
            } else {
              absai = Ma;
              absbi = Mb;
            }
          } else {
            absai = ma;
            absbi = mb;
          }

          if (iseq(absai, absbi)) {
            absai = rt_atan2d_snf(a.im, a.re);
            absbi = rt_atan2d_snf(b.im, b.re);
            if (iseq(absai, absbi)) {
              if (absai > 0.78539816339744828) {
                if (absai > 2.3561944901923448) {
                  absai = -a.im;
                  absbi = -b.im;
                } else {
                  absai = -a.re;
                  absbi = -b.re;
                }
              } else if (absai > -0.78539816339744828) {
                absai = a.im;
                absbi = b.im;
              } else if (absai > -2.3561944901923448) {
                absai = a.re;
                absbi = b.re;
              } else {
                absai = -a.im;
                absbi = -b.im;
              }

              if (iseq(absai, absbi)) {
                absai = 0.0;
                absbi = 0.0;
              }
            }
          }
        }

        p = (absai < absbi);
      }

      return p;
    }
  }
}

//
// File trailer for relop.cpp
//
// [EOF]
//
