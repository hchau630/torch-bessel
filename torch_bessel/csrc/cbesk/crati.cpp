/* fortran/cbesk/crati.f -- translated by f2c (version 20240504).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#ifdef __cplusplus
extern "C" {
#endif
#include "f2c.h"

/* Subroutine */ int crati_(complex *z__, real *fnu, integer *n, complex *cy, 
	real *tol)
{
    /* Initialized data */

    static complex czero = {(float)0.,(float)0.};
    static complex cone = {(float)1.,(float)0.};

    /* System generated locals */
    integer i__1, i__2;
    real r__1;
    complex q__1, q__2, q__3, q__4;

    /* Builtin functions */
    double c_abs(complex *);
    void c_div(complex *, complex *, complex *);
    double sqrt(doublereal), r_imag(complex *);

    /* Local variables */
    static integer i__, k;
    static complex p1, p2, t1;
    static real ak;
    static integer id, kk;
    static real az;
    static complex pt, rz;
    static real ap1, ap2, arg, rho;
    static integer inu;
    static real rap1, flam, dfnu, fdnu;
    static integer magz, idnu;
    static real fnup, test, test1;
    static complex cdfnu;
    static real amagz;
    static integer itime;

/* ***BEGIN PROLOGUE  CRATI */
/* ***REFER TO  CBESI,CBESK,CBESH */

/*     CRATI COMPUTES RATIOS OF I BESSEL FUNCTIONS BY BACKWARD */
/*     RECURRENCE.  THE STARTING INDEX IS DETERMINED BY FORWARD */
/*     RECURRENCE AS DESCRIBED IN J. RES. OF NAT. BUR. OF STANDARDS-B, */
/*     MATHEMATICAL SCIENCES, VOL 77B, P111-114, SEPTEMBER, 1973, */
/*     BESSEL FUNCTIONS I AND J OF COMPLEX ARGUMENT AND INTEGER ORDER, */
/*     BY D. J. SOOKNE. */

/* ***ROUTINES CALLED  (NONE) */
/* ***END PROLOGUE  CRATI */
    /* Parameter adjustments */
    --cy;

    /* Function Body */
    az = c_abs(z__);
    inu = (integer) (*fnu);
    idnu = inu + *n - 1;
    fdnu = (real) idnu;
    magz = (integer) az;
    amagz = (real) (magz + 1);
    fnup = dmax(amagz,fdnu);
    id = idnu - magz - 1;
    itime = 1;
    k = 1;
    q__2.r = cone.r + cone.r, q__2.i = cone.i + cone.i;
    c_div(&q__1, &q__2, z__);
    rz.r = q__1.r, rz.i = q__1.i;
    q__2.r = fnup, q__2.i = (float)0.;
    q__1.r = q__2.r * rz.r - q__2.i * rz.i, q__1.i = q__2.r * rz.i + q__2.i * 
	    rz.r;
    t1.r = q__1.r, t1.i = q__1.i;
    q__1.r = -t1.r, q__1.i = -t1.i;
    p2.r = q__1.r, p2.i = q__1.i;
    p1.r = cone.r, p1.i = cone.i;
    q__1.r = t1.r + rz.r, q__1.i = t1.i + rz.i;
    t1.r = q__1.r, t1.i = q__1.i;
    if (id > 0) {
	id = 0;
    }
    ap2 = c_abs(&p2);
    ap1 = c_abs(&p1);
/* ----------------------------------------------------------------------- */
/*     THE OVERFLOW TEST ON K(FNU+I-1,Z) BEFORE THE CALL TO CBKNX */
/*     GUARANTEES THAT P2 IS ON SCALE. SCALE TEST1 AND ALL SUBSEQUENT */
/*     P2 VALUES BY AP1 TO ENSURE THAT AN OVERFLOW DOES NOT OCCUR */
/*     PREMATURELY. */
/* ----------------------------------------------------------------------- */
    arg = (ap2 + ap2) / (ap1 * *tol);
    test1 = sqrt(arg);
    test = test1;
    rap1 = (float)1. / ap1;
    q__2.r = rap1, q__2.i = (float)0.;
    q__1.r = p1.r * q__2.r - p1.i * q__2.i, q__1.i = p1.r * q__2.i + p1.i * 
	    q__2.r;
    p1.r = q__1.r, p1.i = q__1.i;
    q__2.r = rap1, q__2.i = (float)0.;
    q__1.r = p2.r * q__2.r - p2.i * q__2.i, q__1.i = p2.r * q__2.i + p2.i * 
	    q__2.r;
    p2.r = q__1.r, p2.i = q__1.i;
    ap2 *= rap1;
L10:
    ++k;
    ap1 = ap2;
    pt.r = p2.r, pt.i = p2.i;
    q__2.r = t1.r * p2.r - t1.i * p2.i, q__2.i = t1.r * p2.i + t1.i * p2.r;
    q__1.r = p1.r - q__2.r, q__1.i = p1.i - q__2.i;
    p2.r = q__1.r, p2.i = q__1.i;
    p1.r = pt.r, p1.i = pt.i;
    q__1.r = t1.r + rz.r, q__1.i = t1.i + rz.i;
    t1.r = q__1.r, t1.i = q__1.i;
    ap2 = c_abs(&p2);
    if (ap1 <= test) {
	goto L10;
    }
    if (itime == 2) {
	goto L20;
    }
    ak = c_abs(&t1) * (float).5;
    flam = ak + sqrt(ak * ak - (float)1.);
/* Computing MIN */
    r__1 = ap2 / ap1;
    rho = dmin(r__1,flam);
    test = test1 * sqrt(rho / (rho * rho - (float)1.));
    itime = 2;
    goto L10;
L20:
    kk = k + 1 - id;
    ak = (real) kk;
    dfnu = *fnu + (real) (*n - 1);
    q__1.r = dfnu, q__1.i = (float)0.;
    cdfnu.r = q__1.r, cdfnu.i = q__1.i;
    q__1.r = ak, q__1.i = (float)0.;
    t1.r = q__1.r, t1.i = q__1.i;
    r__1 = (float)1. / ap2;
    q__1.r = r__1, q__1.i = (float)0.;
    p1.r = q__1.r, p1.i = q__1.i;
    p2.r = czero.r, p2.i = czero.i;
    i__1 = kk;
    for (i__ = 1; i__ <= i__1; ++i__) {
	pt.r = p1.r, pt.i = p1.i;
	q__4.r = cdfnu.r + t1.r, q__4.i = cdfnu.i + t1.i;
	q__3.r = rz.r * q__4.r - rz.i * q__4.i, q__3.i = rz.r * q__4.i + rz.i 
		* q__4.r;
	q__2.r = q__3.r * p1.r - q__3.i * p1.i, q__2.i = q__3.r * p1.i + 
		q__3.i * p1.r;
	q__1.r = q__2.r + p2.r, q__1.i = q__2.i + p2.i;
	p1.r = q__1.r, p1.i = q__1.i;
	p2.r = pt.r, p2.i = pt.i;
	q__1.r = t1.r - cone.r, q__1.i = t1.i - cone.i;
	t1.r = q__1.r, t1.i = q__1.i;
/* L30: */
    }
    if (p1.r != (float)0. || r_imag(&p1) != (float)0.) {
	goto L40;
    }
    q__1.r = *tol, q__1.i = *tol;
    p1.r = q__1.r, p1.i = q__1.i;
L40:
    i__1 = *n;
    c_div(&q__1, &p2, &p1);
    cy[i__1].r = q__1.r, cy[i__1].i = q__1.i;
    if (*n == 1) {
	return 0;
    }
    k = *n - 1;
    ak = (real) k;
    q__1.r = ak, q__1.i = (float)0.;
    t1.r = q__1.r, t1.i = q__1.i;
    q__2.r = *fnu, q__2.i = (float)0.;
    q__1.r = q__2.r * rz.r - q__2.i * rz.i, q__1.i = q__2.r * rz.i + q__2.i * 
	    rz.r;
    cdfnu.r = q__1.r, cdfnu.i = q__1.i;
    i__1 = *n;
    for (i__ = 2; i__ <= i__1; ++i__) {
	q__3.r = t1.r * rz.r - t1.i * rz.i, q__3.i = t1.r * rz.i + t1.i * 
		rz.r;
	q__2.r = cdfnu.r + q__3.r, q__2.i = cdfnu.i + q__3.i;
	i__2 = k + 1;
	q__1.r = q__2.r + cy[i__2].r, q__1.i = q__2.i + cy[i__2].i;
	pt.r = q__1.r, pt.i = q__1.i;
	if (pt.r != (float)0. || r_imag(&pt) != (float)0.) {
	    goto L50;
	}
	q__1.r = *tol, q__1.i = *tol;
	pt.r = q__1.r, pt.i = q__1.i;
L50:
	i__2 = k;
	c_div(&q__1, &cone, &pt);
	cy[i__2].r = q__1.r, cy[i__2].i = q__1.i;
	q__1.r = t1.r - cone.r, q__1.i = t1.i - cone.i;
	t1.r = q__1.r, t1.i = q__1.i;
	--k;
/* L60: */
    }
    return 0;
} /* crati_ */

#ifdef __cplusplus
	}
#endif
