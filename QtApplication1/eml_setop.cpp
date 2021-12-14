//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: eml_setop.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 28-Aug-2021 13:33:07
//

// Include Files
#include "eml_setop.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const int a_data[]
//                const int a_size[1]
//                const int b_data[]
//                const int b_size[1]
//                int c_data[]
//                int c_size[1]
//                int ia_data[]
//                int ia_size[1]
//                int ib_data[]
//                int ib_size[1]
// Return Type  : void
//
namespace coder
{
  void do_vectors(const int a_data[], const int a_size[1], const int b_data[],
                  const int b_size[1], int c_data[], int c_size[1], int ia_data[],
                  int ia_size[1], int ib_data[], int ib_size[1])
  {
    int b_ialast;
    int b_iblast;
    int iafirst;
    int ialast;
    int ibfirst;
    int iblast;
    int na;
    int nb;
    int nc;
    int ncmax;
    int nia;
    int nib;

    //@>1196d9
    na                                 //@>1196d8
      = a_size                         //@>38ba10
      [                                //@>2b50da
      0];

    //@>1196df
    nb                                 //@>1196de
      = b_size                         //@>38ba13
      [                                //@>2b510b
      0];

    //@>25c60f
    ncmax                              //@>25c60e
      = a_size                         //@>38ba16
      [                                //@>2b513c
      0]                               //@>25c614
      + b_size                         //@>38ba19
      [                                //@>2b516c
      0];
    c_size                             //@>2b51ae
      [                                //@>2b51b4
      0]                               //@>2b51b6
      =                                //@>2b51a3
      ncmax;
    ia_size                            //@>2b5229
      [                                //@>2b522f
      0]                               //@>2b5231
      = a_size                         //@>38ba1c
      [                                //@>2b521e
      0];
    ib_size                            //@>2b52a4
      [                                //@>2b52aa
      0]                               //@>2b52ac
      = b_size                         //@>38ba1f
      [                                //@>2b5299
      0];

    //@>119848
    nc                                 //@>119847
      =                                //@>3989c8
      -1;

    //@>11984c
    nia                                //@>11984b
      =                                //@>3989cb
      -1;

    //@>119850
    nib                                //@>11984f
      =                                //@>3989ce
      0;

    //@>119854
    iafirst                            //@>119853
      =                                //@>3989d1
      1;

    //@>119858
    ialast                             //@>119857
      =                                //@>3989d4
      0;

    //@>11985c
    ibfirst                            //@>11985b
      =                                //@>3989d7
      0;

    //@>119860
    iblast                             //@>11985f
      =                                //@>3989da
      0;
    while                              //@<119c94
      ((                               //@>119863
        ialast                         //@>2916fe
        +                              //@>2916fd
        1                              //@>1264e7
        <=                             //@>119865
        na)                            //@>385c5b
       && (                            //@>119867
           iblast                      //@>291715
           +                           //@>291714
           1                           //@>1264ef
           <=                          //@>119869
           nb)) {
      int ak;
      int bk;

      //@>271c36
      b_ialast                         //@>263a8f
        =                              //@>119882
        ialast                         //@>2916f2
        +                              //@>2916f1
        1;

      //@>263ab5
      ak                               //@>263ab4
        =                              //@>3297d0
        a_data                         //@>38ba22
        [                              //@>2b52e2
        ialast];
      while                            //@<263ae1
        ((                             //@>263aba
          b_ialast                     //@>263ad8
          < a_size                     //@>38ba25
          [                            //@>2b5315
          0])                          //@>385c5d
         && (                          //@>3297f9
             a_data                    //@>38ba28
             [                         //@>2b53a2
             b_ialast]                 //@>27780e
             ==                        //@>277812
             ak)) {
        //@>263b0c
        b_ialast                       //@>3989f3
          ++;
      }

      //@>11987f
      ialast                           //@>119ccf
        =                              //@>119ccd
        b_ialast                       //@>2916f5
        -                              //@>2916f4
        1;

      //@>271c41
      b_iblast                         //@>263bbd
        =                              //@>119889
        iblast                         //@>291709
        +                              //@>291708
        1;

      //@>263be3
      bk                               //@>263be2
        =                              //@>32987c
        b_data                         //@>38ba43
        [                              //@>2b552a
        iblast];
      while                            //@<263c0f
        ((                             //@>263be8
          b_iblast                     //@>263c06
          < b_size                     //@>38ba49
          [                            //@>2b55f5
          0])                          //@>385c5f
         && (                          //@>3298d5
             b_data                    //@>38ba4c
             [                         //@>2b56b4
             b_iblast]                 //@>277839
             ==                        //@>27783d
             bk)) {
        //@>263c3a
        b_iblast                       //@>3989fa
          ++;
      }

      //@>119886
      iblast                           //@>119ce3
        =                              //@>119ce1
        b_iblast                       //@>29170c
        -                              //@>29170b
        1;

      //@>119651
      if (                             //@>277844
          ak                           //@>277842
          ==                           //@>277846
          bk) {
        //@>25c720
        nc                             //@>3989fb
          ++;

        //@>37cdc5
        c_data                         //@>12b1c4
          [                            //@>119911
          nc]                          //@>11990e
          =                            //@>237cb7
          ak;

        //@>25c846
        nia                            //@>398a00
          ++;

        //@>37cdc8
        ia_data                        //@>12af92
          [                            //@>11991e
          nia]                         //@>11991b
          =                            //@>119920
          iafirst;

        //@>25c89a
        ialast                         //@>25c899
          =                            //@>2776d5
          b_ialast;

        //@>119929
        iafirst                        //@>119928
          =                            //@>27786c
          b_ialast                     //@>2baf05
          +                            //@>2baf04
          1;

        //@>25c918
        iblast                         //@>25c917
          =                            //@>2776d7
          b_iblast;

        //@>119933
        ibfirst                        //@>119932
          =                            //@>277874
          b_iblast;
      } else                           //@>119652
    if (                               //@>27784d
        ak                             //@>27784b
        <                              //@>27784f
        bk) {
        //@>25c79e
        nc                             //@>3989fd
          ++;

        //@>25c81c
        nia                            //@>3989ff
          ++;

        //@>37cdbf
        c_data                         //@>12b1df
          [                            //@>11996f
          nc]                          //@>11996c
          =                            //@>237cb3
          ak;

        //@>37cdc2
        ia_data                        //@>12afad
          [                            //@>119976
          nia]                         //@>119973
          =                            //@>119978
          iafirst;

        //@>25c8ee
        ialast                         //@>25c8ed
          =                            //@>2776cf
          b_ialast;

        //@>119981
        iafirst                        //@>119980
          =                            //@>277862
          b_ialast                     //@>2baf08
          +                            //@>2baf07
          1;
      } else {
        //@>25c774
        nc                             //@>3989fc
          ++;

        //@>25c7f2
        nib                            //@>3989fe
          ++;

        //@>37cdb9
        c_data                         //@>12b1fa
          [                            //@>1199eb
          nc]                          //@>1199e8
          =                            //@>237caf
          bk;

        //@>37cdbc
        ib_data                        //@>12b0c8
          [                            //@>1199f2
          nib                          //@>2baefe
          -                            //@>2baefd
          1]                           //@>1199ef
          =                            //@>1199f4
          ibfirst                      //@>291702
          +                            //@>291701
          1;

        //@>25c8c4
        iblast                         //@>25c8c3
          =                            //@>2776c9
          b_iblast;

        //@>1199fd
        ibfirst                        //@>1199fc
          =                            //@>277858
          b_iblast;
      }
    }

    while                              //@<119cb8
      (                                //@>119a09
       ialast                          //@>2916fb
       +                               //@>2916fa
       1                               //@>12aeef
       <=                              //@>119a0b
       na) {
      //@>271c37
      b_ialast                         //@>263b26
        =                              //@>119a1b
        ialast                         //@>2916f8
        +                              //@>2916f7
        1;
      while                            //@<263b78
        ((                             //@>263b51
          b_ialast                     //@>263b6f
          < a_size                     //@>38ba2e
          [                            //@>2b5378
          0])                          //@>385c5c
         && (                          //@>329820
             a_data                    //@>38ba31
             [                         //@>2b53cd
             b_ialast]                 //@>2777ce
             ==                        //@>329826
             a_data                    //@>38ba34
             [                         //@>2b53f6
             ialast])) {
        //@>263ba3
        b_ialast                       //@>3989f5
          ++;
      }

      //@>25c63b
      nc                               //@>3989f4
        ++;

      //@>25c665
      nia                              //@>3989f6
        ++;

      //@>37cdad
      c_data                           //@>2b55bb
        [                              //@>2b55c1
        nc]                            //@>119a47
        =                              //@>32988e
        a_data                         //@>38ba46
        [                              //@>2b55a5
        ialast];

      //@>37cdb0
      ia_data                          //@>12afc8
        [                              //@>119a51
        nia]                           //@>119a4e
        =                              //@>119a53
        iafirst;

      //@>25c7c8
      ialast                           //@>25c7c7
        =                              //@>2776ad
        b_ialast;

      //@>119a5c
      iafirst                          //@>119a5b
        =                              //@>2777e6
        b_ialast                       //@>2baf0b
        +                              //@>2baf0a
        1;
    }

    while                              //@<119cb4
      (                                //@>119a65
       iblast                          //@>291712
       +                               //@>291711
       1                               //@>12af2f
       <=                              //@>119a67
       nb) {
      //@>271c38
      b_iblast                         //@>263c54
        =                              //@>119a77
        iblast                         //@>29170f
        +                              //@>29170e
        1;
      while                            //@<263ca6
        ((                             //@>263c7f
          b_iblast                     //@>263c9d
          < b_size                     //@>38ba3a
          [                            //@>2b54a8
          0])                          //@>385c5e
         && (                          //@>32986c
             b_data                    //@>38ba3d
             [                         //@>2b54d6
             b_iblast]                 //@>27778e
             ==                        //@>329872
             b_data                    //@>38ba40
             [                         //@>2b54ff
             iblast])) {
        //@>263cd1
        b_iblast                       //@>3989f8
          ++;
      }

      //@>25c6c2
      nc                               //@>3989f7
        ++;

      //@>25c74a
      nib                              //@>3989f9
        ++;

      //@>37cda4
      c_data                           //@>2b5683
        [                              //@>2b5689
        nc]                            //@>119aa3
        =                              //@>3298cb
        b_data                         //@>38ba4f
        [                              //@>2b566d
        iblast];

      //@>37cda7
      ib_data                          //@>12b0e3
        [                              //@>119aad
        nib                            //@>2baf01
        -                              //@>2baf00
        1]                             //@>119aaa
        =                              //@>119aaf
        ibfirst                        //@>291705
        +                              //@>291704
        1;

      //@>25c870
      iblast                           //@>25c86f
        =                              //@>27769f
        b_iblast;

      //@>119ab8
      ibfirst                          //@>119ab7
        =                              //@>2777a6
        b_iblast;
    }

    //@>119602
    if (a_size                         //@>38ba2b
        [                              //@>2b5346
        0]                             //@>12af62
        >                              //@>1f085d
        0) {
      //@>370a55
      if (                             //@>277749
          1                            //@>277748
          >                            //@>27774b
          nia                          //@>2916dd
          +                            //@>2916dc
          1) {
        //@>37cd8f
        ia_size                        //@>370a59
          [                            //@>370a5b
          0]                           //@>370a58
          =                            //@>3989dd
          0;
      } else {
        //@>37cd8c
        ia_size                        //@>36e012
          [                            //@>36e014
          0]                           //@>36e011
          =                            //@>119ae3
          nia                          //@>2916da
          +                            //@>2916d9
          1;
      }
    }

    //@>11961d
    if (b_size                         //@>38ba37
        [                              //@>2b5429
        0]                             //@>12b098
        >                              //@>1f085f
        0) {
      //@>370a5c
      if (                             //@>27775a
          1                            //@>277759
          >                            //@>27775c
          nib) {
        //@>37cd98
        ib_size                        //@>370a60
          [                            //@>370a62
          0]                           //@>370a5f
          =                            //@>3989e0
          0;
      } else {
        //@>37cd95
        ib_size                        //@>36e019
          [                            //@>36e01b
          0]                           //@>36e018
          =                            //@>119b0c
          nib;
      }
    }

    //@>119608
    if (                               //@>119b56
        ncmax                          //@>12b194
        >                              //@>1f0861
        0) {
      //@>370a63
      if (                             //@>277765
          1                            //@>277764
          >                            //@>277767
          nc                           //@>2916d6
          +                            //@>2916d5
          1) {
        //@>37cd9e
        c_size                         //@>370a67
          [                            //@>370a69
          0]                           //@>370a66
          =                            //@>3989e3
          0;
      } else {
        //@>37cd9b
        c_size                         //@>36e020
          [                            //@>36e022
          0]                           //@>36e01f
          =                            //@>119b73
          nc                           //@>2916d3
          +                            //@>2916d2
          1;
      }
    }
  }
}

//
// File trailer for eml_setop.cpp
//
// [EOF]
//
