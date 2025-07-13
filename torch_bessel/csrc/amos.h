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

namespace amos {

template <typename T>
inline C10_HOST_DEVICE int _besk0(
    c10::complex<T> z, int n, c10::complex<T> *cy, int *ierr, T rmax, T rmin, T ascle, T tol, T elim, T alim, T t2
);
template <typename T>
C10_HOST_DEVICE int bknu0(c10::complex<T> z, int n, c10::complex<T> *y, T ascle, T tol, T elim, T alim, T t2);
template <typename T>
C10_HOST_DEVICE int kscl0(c10::complex<T> zr, int n, c10::complex<T> *y, c10::complex<T> rz, T ascle, T tol, T elim);
template <typename T>
C10_HOST_DEVICE int uchk(c10::complex<T> y, T ascle, T tol);

inline C10_HOST_DEVICE int besk0(c10::complex<double> z, int n, c10::complex<double> *cy, int *ierr) {
    return _besk0(
        z,
        n,
        cy,
        ierr,
        1073741823.5,  // aa
        2.2250738585072014e-305,  // ufl
        1.0020841800044864e-289,  // ascle (bry[0])
        2.220446049250313e-16,  // tol
        700.9217936944459,  // elim
        664.8716455337102,  // alim
        28.666666666666664  // t2
    );
}


inline C10_HOST_DEVICE int besk0(c10::complex<float> z, int n, c10::complex<float> *cy, int *ierr) {
    return _besk0(
        z,
        n,
        cy,
        ierr,
        4194303.98419452f,  // aa
        1.1754944e-35f,  // ufl
        9.860761690636695e-29f,  // ascle (bry[0])
        1.1920929e-07f,  // tol
        80.44328208178274f,  // elim
        64.49802424145732f,  // alim
        9.333333333333336f  // t2
    );
}


template <typename T>
inline C10_HOST_DEVICE int _besk0(
    c10::complex<T> z,
    int n,
    c10::complex<T> *cy,
    int *ierr,
    T rmax,
    T rmin,
    T ascle,
    T tol,
    T elim,
    T alim,
    T t2
) {
    T xx = std::real(z);
    T yy = std::imag(z);
    T az;
    int nw;

    *ierr = 0;

    if ((yy == 0.) && (xx <= 0.)) { *ierr = 1; }
    if ((n < 1) || (n > 2)) { *ierr = 1; }
    if (*ierr != 0) { return 0; }

    // TEST FOR PROPER RANGE
    az = std::abs(z);
    if (az > rmax) {
        *ierr = 4;
        return 0;
    }
    if (az > sqrt(rmax)) { *ierr = 3; }

    // OVERFLOW TEST ON THE LAST MEMBER OF THE SEQUENCE
    if (az < rmin) {
        *ierr = 2;
        return 0;
    }

    // RIGHT HALF PLANE COMPUTATION, REAL(Z) >= 0.
    nw = bknu0(z, n, cy, ascle, tol, elim, alim, t2);
    if (nw < 0) {
        *ierr = (nw == -1) ? 2 : 5;
        return 0;
    }
    return nw;
}


template <typename T>
inline C10_HOST_DEVICE int bknu0(
    c10::complex<T> z,
    int n,
    c10::complex<T> *y,
    T ascle,
    T tol,
    T elim,
    T alim,
    T t2
) {
    c10::complex<T> ck, coef, cs, cz,\
                    f, p, pt, p1, p2, q, rz, smu, s1, s2;
    T ak, a1, a2, bk, caz, etest, fhs,\
      fk, fks, rk, tm, t1, xx, yy;
    int iflag, k, kflag, kk, i = 1;

    int kmax = 30;
    T pi = 3.14159265358979324;
    T rthpi = 1.25331413731550025;
    T spi = 1.90985931710274403;
    T hpi = 1.57079632679489662;
    T fpi = 1.89769999331517738;
    xx = std::real(z);
    yy = std::imag(z);
    caz = std::abs(z);
    c10::complex<T> css[3] = {T(1.) / tol, 1., tol};
    c10::complex<T> csr[3] = {tol, 1., T(1.) / tol};
    int nz = 0;
    iflag = 0;
    rz = T(2.) / z;
    // Definitions for silencing initialization warnings.
    s1 = 0.;
    s2 = 0.;
    ck = 0.;
    if (caz <= 2.) {
        //
        // SERIES FOR ABS(Z) <= R1
        //
        smu = std::log(rz);

        //
        // SERIES FOR F0 TO RESOLVE INDETERMINACY FOR SMALL ABS(DNU)
        //
        f = smu - T(5.77215664901532861e-01);  // smu - cc[0]
        p = 0.5;
        q = 0.5;
        s1 = f;
        s2 = p;
        ak = 1.;
        a1 = 1.;
        ck = 1.;
        bk = 1.;
        if (n <= 1) {
            //
            // GENERATE K(FNU,Z), 0.0D0  <=  FNU  <  0.5D0 AND N=1
            //
            if (caz >= tol) {
                cz = z * z * T(0.25);
                t1 = T(0.25) * caz * caz;
                do {
                    f = (f*ak + p + q) / bk;
                    p = p / ak;
                    q = q / ak;
                    rk = T(1.) / ak;
                    ck *= cz * rk;
                    s1 += ck * f;
                    a1 *= t1 * rk;
                    bk += ak + ak + T(1.);
                    ak += T(1.);
                } while (a1 > tol);
            }
            y[0] = s1;
            return nz;
        }
        //
        // GENERATE K(DNU,Z) AND K(DNU+1,Z) FOR FORWARD RECURRENCE
        //
        if (caz >= tol) {
            cz = z * z * T(0.25);
            t1 = T(0.25) * caz * caz;
            do {
                f = (f*ak + p + q) / bk;
                p *= T(1.) / ak;
                q *= T(1.) / ak;
                rk = T(1.) / ak;
                ck *= cz * rk;
                s1 += ck * f;
                s2 += ck * (p - f*ak);
                a1 *= t1 * rk;
                bk += ak + ak + T(1.);
                ak += T(1.);
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
            pt = a1*c10::complex<T>(cos(yy), -sin(yy));
            coef *= pt;
        }

        // MILLER ALGORITHM FOR ABS(Z) > R1
    
        ak = 1.;
        fhs = 0.25;
        //
        // COMPUTE R2=F(E). IF ABS(Z) >= R2, USE FORWARD RECURRENCE TO
        // DETERMINE THE BACKWARD INDEX K. R2=F(E) IS A STRAIGHT LINE ON
        // 12 <= E <= 60. E IS COMPUTED FROM 2**(-E)=B**(1-DIGITS(0.0_dp))=
        // TOL WHERE B IS THE BASE OF THE ARITHMETIC.
        //
        t1 = (xx == 0.) ? hpi : fabs(atan(yy/xx));
        if (t2 <= caz) {
            //
            // FORWARD RECURRENCE LOOP WHEN ABS(Z) >= R2
            //
            etest = ak / (pi*caz*tol);
            fk = 1.;
            if (etest >= 1.) {
                fks = 2.;
                rk = caz + caz + T(2.);
                a1 = 0.;
                a2 = 1.;
                for (i = 1; i < (kmax+1); i++)
                {
                    ak = fhs / fks;
                    bk = rk / (fk + T(1.));
                    tm = a2;
                    a2 = bk * a2 - ak * a1;
                    a1 = tm;
                    rk += T(2.);
                    fks += fk + fk + T(2.);
                    fhs += fk + fk;
                    fk += T(1.);
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
            ak = (log(ak) + caz*cos(T(3.) * t1 / (T(1.) + caz))/(T(1.)  + T(0.008)*caz)) / cos(T(14.7) * t1 / (T(28.) + caz));
            fk = T(0.12125) * ak * ak / caz + T(1.5);
        }
        //
        // BACKWARD RECURRENCE LOOP FOR MILLER ALGORITHM
        //
        k = (int)fk;
        fk = (T)k;
        fks = fk * fk;
        p1 = 0.;
        p2 = tol;
        cs = p2;
        for (i=1; i < (k+1); i++)
        {
            a1 = fks - fk;
            a2 = (fks+fk) / (a1+fhs);
            rk = T(2.) / (fk + T(1.));
            t1 = (fk + xx) * rk;
            t2 = yy * rk;
            pt = p2;
            p2 = (p2 * c10::complex<T>(t1, t2) - p1) * a2;
            p1 = pt;
            cs += p2;
            fks = a1 - fk + T(1.);
            fk -= T(1.);
        }

        //
        // COMPUTE (P2/CS)=(P2/ABS(CS))*(CONJG(CS)/ABS(CS)) FOR BETTER SCALING
        //
        tm = std::abs(cs);
        pt = T(1.) / tm;
        s1 = pt * p2;
        cs = std::conj(cs) * pt;
        s1 *= coef * cs;
        if (n > 1) {
            //
            // COMPUTE P1/P2=(P1/ABS(P2)*CONJG(P2)/ABS(P2) FOR SCALING
            //
            tm = std::abs(p2);
            pt = T(1.) / tm;
            p1 = pt * p1;
            p2 = std::conj(p2) * pt;
            pt = p1 * p2;
            s2 = s1 * (T(1.) + (T(0.5) - pt)/z);
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
    nz = kscl0(z, n, &y[0], rz, ascle, tol, elim);
    if (nz >= n) { return nz; }
    kk = nz + 1;
    s1 = y[kk-1];
    y[kk-1] = s1 * csr[0];
    if (nz == n - 1) { return nz; }
    kk = nz + 2;
    s2 = y[kk-1];
    y[kk-1] = s2 * csr[0];
    // since 0 < n <= 2 and 0 <= nz <= 2, here we must have nz == n - 2, so we can just return
    return nz;
}


template <typename T>
inline C10_HOST_DEVICE int kscl0(
    c10::complex<T> zr,
    int n,
    c10::complex<T> *y,
    c10::complex<T> rz,
    T ascle,
    T tol,
    T elim
) {
    c10::complex<T> s1, cs;
    int nz = 0;
    int ic = 0;
    int i;

    for (i = 1; i < (n + 1); i++)
    {
        s1 = y[i-1];
        nz += 1;
        y[i-1] = 0.;
        if (-std::real(zr) + log(std::abs(s1)) < -elim) {
            continue;
        }
        cs = -zr + std::log(s1);
        cs = (exp(std::real(cs))/tol)*c10::complex<T>(cos(std::imag(cs)), sin(std::imag(cs)));
        if (!uchk(cs, ascle, tol)) {
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
    return nz;
}

template <typename T>
inline C10_HOST_DEVICE int uchk(c10::complex<T> y, T ascle, T tol) {
    T yr = fabs(std::real(y));
    T yi = fabs(std::imag(y));
    T ss = fmax(yr, yi);
    T st = fmin(yr, yi);
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
