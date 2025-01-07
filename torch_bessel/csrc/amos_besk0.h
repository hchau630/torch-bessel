/*
 *
 * This file is a C++ translation of the Fortran code written by
 * D.E. Amos with the following original description:
 *
 *
 * A Portable Package for Bessel Functions of a Complex Argument
 * and Nonnegative Order
 *
 * This algorithm is a package of subroutines for computing Bessel
 * functions and Airy functions.  The routines are updated
 * versions of those routines found in TOMS algorithm 644.
 *
 * Disclaimer:
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                 ISSUED BY SANDIA LABORATORIES,
 *                   A PRIME CONTRACTOR TO THE
 *               UNITED STATES DEPARTMENT OF ENERGY
 * * * * * * * * * * * * * *  NOTICE   * * * * * * * * * * * * * * *
 * THIS REPORT WAS PREPARED AS AN ACCOUNT OF WORK SPONSORED BY THE
 * UNITED STATES GOVERNMENT.  NEITHER THE UNITED STATES NOR THE
 * UNITED STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR
 * EMPLOYEES, NOR ANY OF THEIR CONTRACTORS, SUBCONTRACTORS, OR THEIR
 * EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY
 * LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS
 * OR USEFULNESS OF ANY INFORMATION, APPARATUS, PRODUCT OR PROCESS
 * DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE
 * PRIVATELY OWNED RIGHTS.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * THIS CODE HAS BEEN APPROVED FOR UNLIMITED RELEASE.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *
 *
 * The original Fortran code can be found at https://www.netlib.org/amos/
 *
 * References:
 *
 * [1]: Abramowitz, M. and Stegun, I. A., Handbook of Mathematical
 *      Functions, NBS Applied Math Series 55, U.S. Dept. of Commerce,
 *      Washington, D.C., 1955
 *
 * [2]: Amos, D. E., Algorithm 644, A Portable Package For Bessel
 *      Functions of a Complex Argument and Nonnegative Order, ACM
 *      Transactions on Mathematical Software, Vol. 12, No. 3,
 *      September 1986, Pages 265-273, DOI:10.1145/7921.214331
 *
 * [3]: Amos, D. E., Remark on Algorithm 644, ACM Transactions on
 *      Mathematical Software, Vol. 16, No. 4, December 1990, Page
 *      404, DOI:10.1145/98267.98299
 *
 * [4]: Amos, D. E., A remark on Algorithm 644: "A portable package
 *      for Bessel functions of a complex argument and nonnegative order",
 *      ACM Transactions on Mathematical Software, Vol. 21, No. 4,
 *      December 1995, Pages 388-393, DOI:10.1145/212066.212078
 *
 * [5]: Cody, W. J., Algorithm 665, MACHAR: A Subroutine to
 *      Dynamically Determine Machine Parameters, ACM Transactions on
 *      Mathematical Software, Vol. 14, No. 4, December 1988, Pages
 *      303-311, DOI:10.1145/50063.51907
 *
 */

/*
 * Copyright (C) 2024 SciPy developers
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * a. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * b. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * c. Names of the SciPy Developers may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once

#include <stdlib.h>

#include <math.h>
#include <c10/util/complex.h>
#include <c10/macros/Macros.h>

namespace amos_besk0 {

C10_HOST_DEVICE int besk0(c10::complex<double>, int, c10::complex<double> *, int *);
C10_HOST_DEVICE int bknu0(c10::complex<double>, int, c10::complex<double> *, double, double, double);
C10_HOST_DEVICE int kscl0(c10::complex<double>, int, c10::complex<double> *, c10::complex<double>, double *, double, double);
C10_HOST_DEVICE int uchk(c10::complex<double>, double, double);


C10_HOST_DEVICE constexpr double d1mach[5] = {
    2.2250738585072014e-308,  /* np.finfo(np.float64).tiny      */
    1.7976931348623157e+308,  /* np.finfo(np.float64).max       */
    1.1102230246251565e-16,   /* 0.5 * np.finfo(np.float64).eps */
    2.220446049250313e-16,    /* np.finfo(np.float64).eps       */
    0.3010299956639812        /* np.log10(2)                    */
};

C10_HOST_DEVICE constexpr double i1mach[16] = {
    5,           /* standard input         */
    6,           /* standard output        */
    7,           /* standard punch         */
    0,           /* standard error         */
    32,          /* bits per integer       */
    4,           /* sizeof(int);           */
    2,           /* base for integers      */
    31,          /* digits of integer base */
    2147483647,  /* LONG MAX 2**31 - 1     */
    2,           /* FLT_RADIX;             */
    24,          /* FLT_MANT_DIG;          */
    -126,        /* FLT_MIN_EXP;           */
    128,         /* FLT_MAX_EXP;           */
    53,          /* DBL_MANT_DIG;          */
    -1021,       /* DBL_MIN_EXP;           */
    1024         /* DBL_MAX_EXP;           */
};

inline C10_HOST_DEVICE int besk0(
    c10::complex<double> z,
    int n,
    c10::complex<double> *cy,
    int *ierr
) {

    //***BEGIN PROLOGUE  ZBESK
    //***DATE WRITTEN   830501   (YYMMDD)
    //***REVISION DATE  890801   (YYMMDD)
    //***CATEGORY NO.  B5K
    //***KEYWORDS  K-BESSEL FUNCTION,COMPLEX BESSEL FUNCTION,
    //             MODIFIED BESSEL FUNCTION OF THE SECOND KIND,
    //             BESSEL FUNCTION OF THE THIRD KIND
    //***AUTHOR  AMOS, DONALD E., SANDIA NATIONAL LABORATORIES
    //***PURPOSE  TO COMPUTE K-BESSEL FUNCTIONS OF COMPLEX ARGUMENT
    //***DESCRIPTION
    //
    //                      ***A DOUBLE PRECISION ROUTINE***
    //
    //         ON KODE=1, CBESK COMPUTES AN N MEMBER SEQUENCE OF COMPLEX
    //         BESSEL FUNCTIONS CY(J)=K(FNU+J-1,Z) FOR REAL, NONNEGATIVE
    //         ORDERS FNU+J-1, J=1,...,N AND COMPLEX Z.NE.c10::complex<double>(0.0,0.0)
    //         IN THE CUT PLANE -PI.LT.ARG(Z).LE.PI. ON KODE=2, CBESK
    //         RETURNS THE SCALED K FUNCTIONS,
    //
    //         CY(J)=EXP(Z)*K(FNU+J-1,Z) , J=1,...,N,
    //
    //         WHICH REMOVE THE EXPONENTIAL BEHAVIOR IN BOTH THE LEFT AND
    //         RIGHT HALF PLANES FOR Z TO INFINITY. DEFINITIONS AND
    //         NOTATION ARE FOUND IN THE NBS HANDBOOK OF MATHEMATICAL
    //         FUNCTIONS (REF. 1).
    //
    //         INPUT      ZR,ZI,FNU ARE DOUBLE PRECISION
    //           ZR,ZI  - Z=c10::complex<double>(ZR,ZI), Z.NE.c10::complex<double>(0.0D0,0.0D0),
    //                    -PI.LT.ARG(Z).LE.PI
    //           FNU    - ORDER OF INITIAL K FUNCTION, FNU.GE.0.0D0
    //           N      - NUMBER OF MEMBERS OF THE SEQUENCE, N.GE.1
    //           KODE   - A PARAMETER TO INDICATE THE SCALING OPTION
    //                    KODE= 1  RETURNS
    //                             CY(I)=K(FNU+I-1,Z), I=1,...,N
    //                        = 2  RETURNS
    //                             CY(I)=K(FNU+I-1,Z)*EXP(Z), I=1,...,N
    //
    //         OUTPUT     CYR,CYI ARE DOUBLE PRECISION
    //           CYR,CYI- DOUBLE PRECISION VECTORS WHOSE FIRST N COMPONENTS
    //                    CONTAIN REAL AND IMAGINARY PARTS FOR THE SEQUENCE
    //                    CY(I)=K(FNU+I-1,Z), I=1,...,N OR
    //                    CY(I)=K(FNU+I-1,Z)*EXP(Z), I=1,...,N
    //                    DEPENDING ON KODE
    //           NZ     - NUMBER OF COMPONENTS SET TO ZERO DUE TO UNDERFLOW.
    //                    NZ= 0   , NORMAL RETURN
    //                    NZ.GT.0 , FIRST NZ COMPONENTS OF CY SET TO ZERO DUE
    //                              TO UNDERFLOW, CY(I)=c10::complex<double>(0.0D0,0.0D0),
    //                              I=1,...,N WHEN X.GE.0.0. WHEN X.LT.0.0
    //                              NZ STATES ONLY THE NUMBER OF UNDERFLOWS
    //                              IN THE SEQUENCE.
    //
    //           IERR   - ERROR FLAG
    //                    IERR=0, NORMAL RETURN - COMPUTATION COMPLETED
    //                    IERR=1, INPUT ERROR   - NO COMPUTATION
    //                    IERR=2, OVERFLOW      - NO COMPUTATION, FNU IS
    //                            TOO LARGE OR CABS(Z) IS TOO SMALL OR BOTH
    //                    IERR=3, CABS(Z) OR FNU+N-1 LARGE - COMPUTATION DONE
    //                            BUT LOSSES OF SIGNIFCANCE BY ARGUMENT
    //                            REDUCTION PRODUCE LESS THAN HALF OF MACHINE
    //                            ACCURACY
    //                    IERR=4, CABS(Z) OR FNU+N-1 TOO LARGE - NO COMPUTA-
    //                            TION BECAUSE OF COMPLETE LOSSES OF SIGNIFI-
    //                            CANCE BY ARGUMENT REDUCTION
    //                    IERR=5, ERROR              - NO COMPUTATION,
    //                            ALGORITHM TERMINATION CONDITION NOT MET
    //
    //***LONG DESCRIPTION
    //
    //         EQUATIONS OF THE REFERENCE ARE IMPLEMENTED FOR SMALL ORDERS
    //         DNU AND DNU+1.0 IN THE RIGHT HALF PLANE X.GE.0.0. FORWARD
    //         RECURRENCE GENERATES HIGHER ORDERS. K IS CONTINUED TO THE LEFT
    //         HALF PLANE BY THE RELATION
    //
    //         K(FNU,Z*EXP(MP)) = EXP(-MP*FNU)*K(FNU,Z)-MP*I(FNU,Z)
    //         MP=MR*PI*I, MR=+1 OR -1, RE(Z).GT.0, I**2=-1
    //
    //         WHERE I(FNU,Z) IS THE I BESSEL FUNCTION.
    //
    //         FOR LARGE ORDERS, FNU.GT.FNUL, THE K FUNCTION IS COMPUTED
    //         BY MEANS OF ITS UNIFORM ASYMPTOTIC EXPANSIONS.
    //
    //         FOR NEGATIVE ORDERS, THE FORMULA
    //
    //                       K(-FNU,Z) = K(FNU,Z)
    //
    //         CAN BE USED.
    //
    //         CBESK ASSUMES THAT A SIGNIFICANT DIGIT SINH(X) FUNCTION IS
    //         AVAILABLE.
    //
    //         IN MOST COMPLEX VARIABLE COMPUTATION, ONE MUST EVALUATE ELE-
    //         MENTARY FUNCTIONS. WHEN THE MAGNITUDE OF Z OR FNU+N-1 IS
    //         LARGE, LOSSES OF SIGNIFICANCE BY ARGUMENT REDUCTION OCCUR.
    //         CONSEQUENTLY, IF EITHER ONE EXCEEDS U1=SQRT(0.5/UR), THEN
    //         LOSSES EXCEEDING HALF PRECISION ARE LIKELY AND AN ERROR FLAG
    //         IERR=3 IS TRIGGERED WHERE UR=DMAX1(D1MACH(4),1.0D-18) IS
    //         DOUBLE PRECISION UNIT ROUNDOFF LIMITED TO 18 DIGITS PRECISION.
    //         IF EITHER IS LARGER THAN U2=0.5/UR, THEN ALL SIGNIFICANCE IS
    //         LOST AND IERR=4. IN ORDER TO USE THE INT FUNCTION, ARGUMENTS
    //         MUST BE FURTHER RESTRICTED NOT TO EXCEED THE LARGEST MACHINE
    //         INTEGER, U3=I1MACH(9). THUS, THE MAGNITUDE OF Z AND FNU+N-1 IS
    //         RESTRICTED BY MIN(U2,U3). ON 32 BIT MACHINES, U1,U2, AND U3
    //         ARE APPROXIMATELY 2.0E+3, 4.2E+6, 2.1E+9 IN SINGLE PRECISION
    //         ARITHMETIC AND 1.3E+8, 1.8E+16, 2.1E+9 IN DOUBLE PRECISION
    //         ARITHMETIC RESPECTIVELY. THIS MAKES U2 AND U3 LIMITING IN
    //         THEIR RESPECTIVE ARITHMETICS. THIS MEANS THAT ONE CAN EXPECT
    //         TO RETAIN, IN THE WORST CASES ON 32 BIT MACHINES, NO DIGITS
    //         IN SINGLE AND ONLY 7 DIGITS IN DOUBLE PRECISION ARITHMETIC.
    //         SIMILAR CONSIDERATIONS HOLD FOR OTHER MACHINES.
    //
    //         THE APPROXIMATE RELATIVE ERROR IN THE MAGNITUDE OF A COMPLEX
    //         BESSEL FUNCTION CAN BE EXPRESSED BY P*10**S WHERE P=MAX(UNIT
    //         ROUNDOFF,1.0E-18) IS THE NOMINAL PRECISION AND 10**S REPRE-
    //         SENTS THE INCREASE IN ERROR DUE TO ARGUMENT REDUCTION IN THE
    //         ELEMENTARY FUNCTIONS. HERE, S=MAX(1,ABS(LOG10(CABS(Z))),
    //         ABS(LOG10(FNU))) APPROXIMATELY (I.E. S=MAX(1,ABS(EXPONENT OF
    //         CABS(Z),ABS(EXPONENT OF FNU)) ). HOWEVER, THE PHASE ANGLE MAY
    //         HAVE ONLY ABSOLUTE ACCURACY. THIS IS MOST LIKELY TO OCCUR WHEN
    //         ONE COMPONENT (IN ABSOLUTE VALUE) IS LARGER THAN THE OTHER BY
    //         SEVERAL ORDERS OF MAGNITUDE. IF ONE COMPONENT IS 10**K LARGER
    //         THAN THE OTHER, THEN ONE CAN EXPECT ONLY MAX(ABS(LOG10(P))-K,
    //         0) SIGNIFICANT DIGITS; OR, STATED ANOTHER WAY, WHEN K EXCEEDS
    //         THE EXPONENT OF P, NO SIGNIFICANT DIGITS REMAIN IN THE SMALLER
    //         COMPONENT. HOWEVER, THE PHASE ANGLE RETAINS ABSOLUTE ACCURACY
    //         BECAUSE, IN COMPLEX ARITHMETIC WITH PRECISION P, THE SMALLER
    //         COMPONENT WILL NOT (AS A RULE) DECREASE BELOW P TIMES THE
    //         MAGNITUDE OF THE LARGER COMPONENT. IN THESE EXTREME CASES,
    //         THE PRINCIPAL PHASE ANGLE IS ON THE ORDER OF +P, -P, PI/2-P,
    //         OR -PI/2+P.
    //
    //***REFERENCES  HANDBOOK OF MATHEMATICAL FUNCTIONS BY M. ABRAMOWITZ
    //                 AND I. A. STEGUN, NBS AMS SERIES 55, U.S. DEPT. OF
    //                 COMMERCE, 1955.
    //
    //               COMPUTATION OF BESSEL FUNCTIONS OF COMPLEX ARGUMENT
    //                 BY D. E. AMOS, SAND83-0083, MAY, 1983.
    //
    //               COMPUTATION OF BESSEL FUNCTIONS OF COMPLEX ARGUMENT
    //                 AND LARGE ORDER BY D. E. AMOS, SAND83-0643, MAY, 1983.
    //
    //               A SUBROUTINE PACKAGE FOR BESSEL FUNCTIONS OF A COMPLEX
    //                 ARGUMENT AND NONNEGATIVE ORDER BY D. E. AMOS, SAND85-
    //                 1018, MAY, 1985
    //
    //               A PORTABLE PACKAGE FOR BESSEL FUNCTIONS OF A COMPLEX
    //                 ARGUMENT AND NONNEGATIVE ORDER BY D. E. AMOS, TRANS.
    //                 MATH. SOFTWARE, 1986
    //
    //***ROUTINES CALLED  ZACON,ZBKNU,ZBUNK,ZUOIK,AZABS,I1MACH,D1MACH
    //***END PROLOGUE  ZBESK

    double xx = std::real(z);
    double yy = std::imag(z);
    double az;
    int nw;

    *ierr = 0;

    if ((yy == 0.0) && (xx <= 0.0)) { *ierr = 1; }
    if ((n < 1) || (n > 2)) { *ierr = 1; }
    if (*ierr != 0) { return 0; }

    //
    // TEST FOR PROPER RANGE
    //
    az = std::abs(z);
    if (az > 1073741823.5) {
        *ierr = 4;
        return 0;
    }
    if (az > 32767.999992370605) { *ierr = 3; }
    //
    // OVERFLOW TEST ON THE LAST MEMBER OF THE SEQUENCE
    //
    if (az < 2.2250738585072014e-305) {
        *ierr = 2;
        return 0;
    }

    /* 60 */
    //
    // RIGHT HALF PLANE COMPUTATION, REAL(Z) >= 0.
    //
    nw = bknu0(z, n, cy, 2.220446049250313e-16, 700.9217936944459, 664.8716455337102);
    if (nw < 0) {
        if (nw == -1) {
            *ierr = 2;
        } else {
            *ierr = 5;
        }
        return 0;
    }
    return nw;
}


inline C10_HOST_DEVICE int bknu0(
    c10::complex<double> z,
    int n,
    c10::complex<double> *y,
    double tol,
    double elim,
    double alim
) {

    //***BEGIN PROLOGUE  ZBKNU
    //***REFER TO  ZBESI,ZBESK,ZAIRY,ZBESH
    //
    //     ZBKNU COMPUTES THE K BESSEL FUNCTION IN THE RIGHT HALF Z PLANE.
    //
    //***ROUTINES CALLED  DGAMLN,I1MACH,D1MACH,ZKSCL,ZSHCH,ZUCHK,AZABS,ZDIV,
    //                    AZEXP,AZLOG,ZMLT,AZSQRT
    //***END PROLOGUE  ZBKNU

    c10::complex<double> ck, coef, cs, cz,\
                         f, p, pt, p1, p2, q, rz, smu, st, s1, s2;
    double ak, ascle, a1, a2, bk, caz, etest, fhs,\
           fk, fks, rk, tm, t1, t2, xx, yy;
    int iflag, k, kflag, kk, i = 1;
    c10::complex<double> cy[2];

    int kmax = 30;
    double pi = 3.14159265358979324;
    double rthpi = 1.25331413731550025;
    double spi = 1.90985931710274403;
    double hpi = 1.57079632679489662;
    double fpi = 1.89769999331517738;
    xx = std::real(z);
    yy = std::imag(z);
    caz = std::abs(z);
    c10::complex<double> css[3] = {4503599627370496.0, 1.0, 2.220446049250313e-16};
    c10::complex<double> csr[3] = {2.220446049250313e-16, 1.0, 4503599627370496.0};
    double bry[3] = {1.0020841800044864e-289, 9.9792015476736e+288, 1.7976931348623157e+308};
    int nz = 0;
    iflag = 0;
    rz = 2. / z;
    // Definitions for silencing initialization warnings.
    s1 = 0.0;
    s2 = 0.0;
    ck = 0.0;
    if (caz <= 2.) {
        //
        // SERIES FOR ABS(Z) <= R1
        //
        smu = std::log(rz);

        //
        // SERIES FOR F0 TO RESOLVE INDETERMINACY FOR SMALL ABS(DNU)
        //
        f = smu - 5.77215664901532861e-01;  // smu - cc[0]
        p = 0.5;
        q = 0.5;
        s1 = f;
        s2 = p;
        ak = 1.0;
        a1 = 1.0;
        ck = 1.0;
        bk = 1.0;
        if (n <= 1) {
            //
            // GENERATE K(FNU,Z), 0.0D0  <=  FNU  <  0.5D0 AND N=1
            //
            if (caz >= tol) {
                cz = z * z * 0.25;
                t1 = 0.25 * caz * caz;
                do {
                    f = (f*ak + p + q) / bk;
                    p = p / ak;
                    q = q / ak;
                    rk = 1.0 / ak;
                    ck *= cz * rk;
                    s1 += ck * f;
                    a1 *= t1 * rk;
                    bk += ak + ak + 1.0;
                    ak += 1.0;
                } while (a1 > tol);
            }
            y[0] = s1;
            return nz;
        }
        //
        // GENERATE K(DNU,Z) AND K(DNU+1,Z) FOR FORWARD RECURRENCE
        //
        if (caz >= tol) {
            cz = z * z * 0.25;
            t1 = 0.25 * caz * caz;
            do {
                f = (f*ak + p + q) / bk;
                p *= 1.0 / ak;
                q *= 1.0 / ak;
                rk = 1. / ak;
                ck *= cz * rk;
                s1 += ck * f;
                s2 += ck * (p - f*ak);
                a1 *= t1 * rk;
                bk += ak + ak + 1.0;
                ak += 1.0;
            } while (a1 > tol);
        }
        kflag = 2;
        bk = std::real(smu);
        a1 = 1.;
        ak = a1 * fabs(bk);
        if (ak > alim) { kflag = 3; }
        p2 = s2 * css[kflag-1];
        s2 = p2 * rz;
        s1 *= css[kflag-1];
    } else {
        //
        // IFLAG=0 MEANS NO UNDERFLOW OCCURRED
        // IFLAG=1 MEANS AN UNDERFLOW OCCURRED- COMPUTATION PROCEEDS WITH
        // KODED=2 AND A TEST FOR ON SCALE VALUES IS MADE DURING FORWARD
        // RECURSION
        //
        coef = rthpi / std::sqrt(z);
        kflag = 2;
        if (xx > alim) {
            iflag = 1;
            kflag = 2;
        } else {
            a1 = exp(-xx)*std::real(css[kflag-1]);
            pt = a1*c10::complex<double>(cos(yy), -sin(yy));
            coef *= pt;
        }

        // MILLER ALGORITHM FOR ABS(Z) > R1
    
        ak = 1.0;
        fhs = 0.25;
        //
        // COMPUTE R2=F(E). IF ABS(Z) >= R2, USE FORWARD RECURRENCE TO
        // DETERMINE THE BACKWARD INDEX K. R2=F(E) IS A STRAIGHT LINE ON
        // 12 <= E <= 60. E IS COMPUTED FROM 2**(-E)=B**(1-DIGITS(0.0_dp))=
        // TOL WHERE B IS THE BASE OF THE ARITHMETIC.
        //
        t1 = (xx == 0.) ? hpi : fabs(atan(yy/xx));
        t2 = 28.666666666666664;
        if (t2 <= caz) {
            //
            // FORWARD RECURRENCE LOOP WHEN ABS(Z) >= R2
            //
            etest = ak / (pi*caz*tol);
            fk = 1.0;
            if (etest >= 1.0) {
                fks = 2.0;
                rk = caz + caz + 2.0;
                a1 = 0.0;
                a2 = 1.0;
                for (i = 1; i < (kmax+1); i++)
                {
                    ak = fhs / fks;
                    bk = rk / (fk + 1.0);
                    tm = a2;
                    a2 = bk * a2 - ak * a1;
                    a1 = tm;
                    rk += 2.;
                    fks += fk + fk + 2.0;
                    fhs += fk + fk;
                    fk += 1.0;
                    tm = fabs(a2)*fk;
                    if (etest < tm) {
                        /* goto 160 */
                        break;
                    }
                    if (i == kmax) {
                        /* Didn't break so goes to 310 */
                        return -2;
                    }
                }

                /* 160 */
                fk += spi * t1 * sqrt(t2/caz);
                fhs = 0.25;
            }
        } else {
            //
            // COMPUTE BACKWARD INDEX K FOR ABS(Z) < R2
            //
            a2 = sqrt(caz);
            ak *= fpi / (tol*sqrt(a2));
            ak = (log(ak) + caz*cos(3.0 * t1 / (1.0 + caz))/(1.0  + 0.008*caz)) / cos(14.7 * t1 / (28.0 + caz));
            fk = 0.12125 * ak * ak / caz + 1.5;
        }
        //
        // BACKWARD RECURRENCE LOOP FOR MILLER ALGORITHM
        //
        k = (int)fk;
        fk = (double)k;
        fks = fk * fk;
        p1 = 0.0;
        p2 = tol;
        cs = p2;
        for (i=1; i < (k+1); i++)
        {
            a1 = fks - fk;
            a2 = (fks+fk) / (a1+fhs);
            rk = 2.0 / (fk + 1.);
            t1 = (fk + xx) * rk;
            t2 = yy * rk;
            pt = p2;
            p2 = (p2 * c10::complex<double>(t1, t2) - p1) * a2;
            p1 = pt;
            cs += p2;
            fks = a1 - fk + 1.0;
            fk -= 1.0;
        }

        //
        // COMPUTE (P2/CS)=(P2/ABS(CS))*(CONJG(CS)/ABS(CS)) FOR BETTER SCALING
        //
        tm = std::abs(cs);
        pt = 1.0 / tm;
        s1 = pt * p2;
        cs = std::conj(cs) * pt;
        s1 *= coef * cs;
        if (n > 1) {
            //
            // COMPUTE P1/P2=(P1/ABS(P2)*CONJG(P2)/ABS(P2) FOR SCALING
            //
            tm = std::abs(p2);
            pt = 1.0 / tm;
            p1 = pt * p1;
            p2 = std::conj(p2) * pt;
            pt = p1 * p2;
            s2 = s1 * (1. + (0.5 - pt)/z);
        }
    }
    //
    // FORWARD RECURSION ON THE THREE TERM RECURSION RELATION WITH
    // SCALING NEAR EXPONENT EXTREMES ON KFLAG=1 OR KFLAG=3
    //
    if (iflag != 1) {
        y[0] = s1 * csr[kflag-1];
        if (n == 1) { return nz; }
        y[1] = s2 * csr[kflag-1];
        return nz;
    }
    y[0] = s1;
    if (n != 1) { y[1] = s2; }
    ascle = bry[0];
    nz = kscl0(z, n, &y[0], rz, &ascle, tol, elim);
    if (nz >= n) { return nz; }
    kk = nz + 1;
    s1 = y[kk-1];
    y[kk-1] = s1 * csr[0];
    if (nz == n - 1) { return nz; }
    kk = nz + 2;
    s2 = y[kk-1];
    y[kk-1] = s2 * csr[0];
    if (nz == n - 2) { return nz; }
    t2 = kk-1;
    ck = t2 * rz;
    kflag = 1;

    // L140
    kk += 1;
    if (kk > n) { return nz; }
    p1 = csr[kflag-1];
    ascle = bry[kflag-1];
    for (i = kk; i < (n+1); i++)
    {
        p2 = s2;
        s2 = ck*s2 + s1;
        s1 = p2;
        ck += rz;
        p2 = s2*p1;
        y[i-1] = p2;
        if (kflag < 3) {
            if (fmax(fabs(std::real(p2)), fabs(std::imag(p2))) > ascle) {
                kflag += 1;
                ascle = bry[kflag-1];
                s1 *= p1;
                s2 = p2;
                s1 *= css[kflag-1];
                s2 *= css[kflag-1];
                p1 = csr[kflag-1];
            }
        }
    }
    return nz;
}


inline C10_HOST_DEVICE int kscl0(
    c10::complex<double> zr,
    int n,
    c10::complex<double> *y,
    c10::complex<double> rz,
    double *ascle,
    double tol,
    double elim
) {

    //***BEGIN PROLOGUE  ZKSCL
    //***REFER TO  ZBESK
    //
    //     SET K FUNCTIONS TO ZERO ON UNDERFLOW, CONTINUE RECURRENCE
    //     ON SCALED FUNCTIONS UNTIL TWO MEMBERS COME ON SCALE, THEN
    //     RETURN WITH MIN(NZ+2,N) VALUES SCALED BY 1/TOL.
    //
    //***ROUTINES CALLED  ZUCHK,AZABS,AZLOG
    //***END PROLOGUE  ZKSCL

    c10::complex<double> cy[2] = { 0. };
    double as, acs, alas, zri, xx;
    c10::complex<double> s1, s2, cs, ck, zd;
    int nz = 0;
    int ic = 0;
    int kk = 0;
    int i;
    double elm = exp(-elim);
    xx = std::real(zr);

    for (i = 1; i < (n + 1); i++)
    {
        s1 = y[i-1];
        cy[i-1] = s1;
        as = std::abs(s1);
        acs = -std::real(zr) + log(as);
        nz += 1;
        y[i-1] = 0.;
        if (acs < -elim) {
            continue;
        }
        cs = -zr + std::log(s1);
        cs = (exp(std::real(cs))/tol)*(cos(std::imag(cs)) + sin(std::imag(cs)*c10::complex<double>(0, 1)));
        if (!uchk(cs, *ascle, tol)) {
            y[i-1] = cs;
            nz -= 1;
            ic = i;
        }
    }
    if (n == 1) {
        return nz;
    }
    if (ic <= 1) {
        y[0] = 0.;
        nz = 2;
    }
    if (n == 2) {
        return nz;
    }
    if (nz == 0) {
        return nz;
    }

    ck = rz;
    s1 = cy[0];
    s2 = cy[1];
    zri = std::imag(zr);
    zd = zr;
    for (i = 3; i < (n+1); i++)
    {
        kk = i;
        cs = s2;
        s2 *= ck;
        s2 += s1;
        s1 = cs;
        ck += rz;
        as = std::abs(s2);
        alas = log(as);
        acs = alas - xx;
        nz += 1;
        y[i-1] = 0.;
        if (acs >= -elim) {
            cs = std::log(s2);
            cs -= zd;
            cs = (exp(std::real(cs))/tol)*c10::complex<double>(cos(std::imag(cs)), sin(std::imag(cs)));
            if (!uchk(cs, *ascle, tol)) {
                y[i-1] = cs;
                nz -= 1;
                if (ic == kk-1) {
                    nz = kk - 2;
                    for (int i = 0; i < nz; i++) { y[i] = 0.; }
                    return nz;
                }
                ic = kk;
                continue;
            }
        }
        if (alas >= 0.5*elim){
            xx -= elim;
            zd = c10::complex<double>(xx, zri);
            s1 *= elm;
            s2 *= elm;
        }
    }
    nz = n;
    if (ic == n) {
        nz = n-1;
    }

    for (int i = 0; i < nz; i++) { y[i] = 0.; }
    return nz;
}

inline C10_HOST_DEVICE int uchk(
    c10::complex<double> y,
    double ascle,
    double tol
) {

    //***BEGIN PROLOGUE  ZUCHK
    //***REFER TO ZSERI,ZUOIK,ZUNK1,ZUNK2,ZUNI1,ZUNI2,ZKSCL
    //
    //      Y ENTERS AS A SCALED QUANTITY WHOSE MAGNITUDE IS GREATER THAN
    //      EXP(-ALIM)=ASCLE=1.0E+3*D1MACH(1)/TOL. THE TEST IS MADE TO SEE
    //      IF THE MAGNITUDE OF THE REAL OR IMAGINARY PART WOULD UNDERFLOW
    //      WHEN Y IS SCALED (BY TOL) TO ITS PROPER VALUE. Y IS ACCEPTED
    //      IF THE UNDERFLOW IS AT LEAST ONE PRECISION BELOW THE MAGNITUDE
    //      OF THE LARGEST COMPONENT; OTHERWISE THE PHASE ANGLE DOES NOT HAVE
    //      ABSOLUTE ACCURACY AND AN UNDERFLOW IS ASSUMED.
    //
    //***ROUTINES CALLED  (NONE)
    //***END PROLOGUE  ZUCHK

    double yr = fabs(std::real(y));
    double yi = fabs(std::imag(y));
    double ss = fmax(yr, yi);
    double st = fmin(yr, yi);
    if (st > ascle) {
        return 0;
    } else {
        st /= tol;
        if (ss < st) {
            return 1;
        } else {
            return 0;
        }
    }
}
}
