/* fortran/cbesk/casyi.f -- translated by f2c (version 20240504).
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

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int casyi_(complex *z__, real *fnu, integer *kode, integer *
	n, complex *y, integer *nz, real *rl, real *tol, real *elim, real *
	alim)
{
    /* Initialized data */

    static real pi = (float)3.14159265358979324;
    static real rtpi = (float).159154943091895336;
    static complex czero = {(float)0.,(float)0.};
    static complex cone = {(float)1.,(float)0.};

    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    real r__1;
    complex q__1, q__2, q__3, q__4, q__5, q__6;

    /* Builtin functions */
    double c_abs(complex *), sqrt(doublereal);
    void c_div(complex *, complex *, complex *), c_sqrt(complex *, complex *),
	     c_exp(complex *, complex *);
    double r_imag(complex *), sin(doublereal), cos(doublereal);

    /* Local variables */
    static integer i__, j, k, m;
    static real s, x;
    static complex p1, s2;
    static real aa, bb;
    static integer ib;
    static real ak, bk;
    static complex ck, dk;
    static integer il, jl;
    static real az;
    static integer nn;
    static complex cz, ez, rz;
    static real yy;
    static complex ak1, cs1, cs2;
    static real fdn, arg, acz, aez, arm, sgn;
    static integer inu;
    static real sqk, dnu2, rtr1, dfnu, atol;
    static integer koded;
    extern doublereal r1mach_(integer *);

/* ***BEGIN PROLOGUE  CASYI */
/* ***REFER TO  CBESI,CBESK */

/*     CASYI COMPUTES THE I BESSEL FUNCTION FOR REAL(Z).GE.0.0 BY */
/*     MEANS OF THE ASYMPTOTIC EXPANSION FOR LARGE CABS(Z) IN THE */
/*     REGION CABS(Z).GT.MAX(RL,FNU*FNU/2). NZ=0 IS A NORMAL RETURN. */
/*     NZ.LT.0 INDICATES AN OVERFLOW ON KODE=1. */

/* ***ROUTINES CALLED  R1MACH */
/* ***END PROLOGUE  CASYI */
    /* Parameter adjustments */
    --y;

    /* Function Body */

    *nz = 0;
    az = c_abs(z__);
    x = z__->r;
    arm = r1mach_(&c__1) * (float)1e3;
    rtr1 = sqrt(arm);
    il = min(2,*n);
    dfnu = *fnu + (real) (*n - il);
/* ----------------------------------------------------------------------- */
/*     OVERFLOW TEST */
/* ----------------------------------------------------------------------- */
    q__2.r = rtpi, q__2.i = (float)0.;
    c_div(&q__1, &q__2, z__);
    ak1.r = q__1.r, ak1.i = q__1.i;
    c_sqrt(&q__1, &ak1);
    ak1.r = q__1.r, ak1.i = q__1.i;
    cz.r = z__->r, cz.i = z__->i;
    if (*kode == 2) {
	q__2.r = x, q__2.i = (float)0.;
	q__1.r = z__->r - q__2.r, q__1.i = z__->i - q__2.i;
	cz.r = q__1.r, cz.i = q__1.i;
    }
    acz = cz.r;
    if (dabs(acz) > *elim) {
	goto L80;
    }
    dnu2 = dfnu + dfnu;
    koded = 1;
    if (dabs(acz) > *alim && *n > 2) {
	goto L10;
    }
    koded = 0;
    c_exp(&q__2, &cz);
    q__1.r = ak1.r * q__2.r - ak1.i * q__2.i, q__1.i = ak1.r * q__2.i + ak1.i 
	    * q__2.r;
    ak1.r = q__1.r, ak1.i = q__1.i;
L10:
    fdn = (float)0.;
    if (dnu2 > rtr1) {
	fdn = dnu2 * dnu2;
    }
    q__1.r = z__->r * (float)8. - z__->i * (float)0., q__1.i = z__->r * (
	    float)0. + z__->i * (float)8.;
    ez.r = q__1.r, ez.i = q__1.i;
/* ----------------------------------------------------------------------- */
/*     WHEN Z IS IMAGINARY, THE ERROR TEST MUST BE MADE RELATIVE TO THE */
/*     FIRST RECIPROCAL POWER SINCE THIS IS THE LEADING TERM OF THE */
/*     EXPANSION FOR THE IMAGINARY PART. */
/* ----------------------------------------------------------------------- */
    aez = az * (float)8.;
    s = *tol / aez;
    jl = (integer) (*rl + *rl) + 2;
    yy = r_imag(z__);
    p1.r = czero.r, p1.i = czero.i;
    if (yy == (float)0.) {
	goto L20;
    }
/* ----------------------------------------------------------------------- */
/*     CALCULATE EXP(PI*(0.5+FNU+N-IL)*I) TO MINIMIZE LOSSES OF */
/*     SIGNIFICANCE WHEN FNU OR N IS LARGE */
/* ----------------------------------------------------------------------- */
    inu = (integer) (*fnu);
    arg = (*fnu - (real) inu) * pi;
    inu = inu + *n - il;
    ak = -sin(arg);
    bk = cos(arg);
    if (yy < (float)0.) {
	bk = -bk;
    }
    q__1.r = ak, q__1.i = bk;
    p1.r = q__1.r, p1.i = q__1.i;
    if (inu % 2 == 1) {
	q__1.r = -p1.r, q__1.i = -p1.i;
	p1.r = q__1.r, p1.i = q__1.i;
    }
L20:
    i__1 = il;
    for (k = 1; k <= i__1; ++k) {
	sqk = fdn - (float)1.;
	atol = s * dabs(sqk);
	sgn = (float)1.;
	cs1.r = cone.r, cs1.i = cone.i;
	cs2.r = cone.r, cs2.i = cone.i;
	ck.r = cone.r, ck.i = cone.i;
	ak = (float)0.;
	aa = (float)1.;
	bb = aez;
	dk.r = ez.r, dk.i = ez.i;
	i__2 = jl;
	for (j = 1; j <= i__2; ++j) {
	    q__3.r = sqk, q__3.i = (float)0.;
	    q__2.r = ck.r * q__3.r - ck.i * q__3.i, q__2.i = ck.r * q__3.i + 
		    ck.i * q__3.r;
	    c_div(&q__1, &q__2, &dk);
	    ck.r = q__1.r, ck.i = q__1.i;
	    q__1.r = cs2.r + ck.r, q__1.i = cs2.i + ck.i;
	    cs2.r = q__1.r, cs2.i = q__1.i;
	    sgn = -sgn;
	    q__3.r = sgn, q__3.i = (float)0.;
	    q__2.r = ck.r * q__3.r - ck.i * q__3.i, q__2.i = ck.r * q__3.i + 
		    ck.i * q__3.r;
	    q__1.r = cs1.r + q__2.r, q__1.i = cs1.i + q__2.i;
	    cs1.r = q__1.r, cs1.i = q__1.i;
	    q__1.r = dk.r + ez.r, q__1.i = dk.i + ez.i;
	    dk.r = q__1.r, dk.i = q__1.i;
	    aa = aa * dabs(sqk) / bb;
	    bb += aez;
	    ak += (float)8.;
	    sqk -= ak;
	    if (aa <= atol) {
		goto L40;
	    }
/* L30: */
	}
	goto L90;
L40:
	s2.r = cs1.r, s2.i = cs1.i;
	if (x + x < *elim) {
	    q__3.r = p1.r * cs2.r - p1.i * cs2.i, q__3.i = p1.r * cs2.i + 
		    p1.i * cs2.r;
	    q__6.r = -z__->r, q__6.i = -z__->i;
	    q__5.r = q__6.r - z__->r, q__5.i = q__6.i - z__->i;
	    c_exp(&q__4, &q__5);
	    q__2.r = q__3.r * q__4.r - q__3.i * q__4.i, q__2.i = q__3.r * 
		    q__4.i + q__3.i * q__4.r;
	    q__1.r = s2.r + q__2.r, q__1.i = s2.i + q__2.i;
	    s2.r = q__1.r, s2.i = q__1.i;
	}
	fdn = fdn + dfnu * (float)8. + (float)4.;
	q__1.r = -p1.r, q__1.i = -p1.i;
	p1.r = q__1.r, p1.i = q__1.i;
	m = *n - il + k;
	i__2 = m;
	q__1.r = s2.r * ak1.r - s2.i * ak1.i, q__1.i = s2.r * ak1.i + s2.i * 
		ak1.r;
	y[i__2].r = q__1.r, y[i__2].i = q__1.i;
/* L50: */
    }
    if (*n <= 2) {
	return 0;
    }
    nn = *n;
    k = nn - 2;
    ak = (real) k;
    q__2.r = cone.r + cone.r, q__2.i = cone.i + cone.i;
    c_div(&q__1, &q__2, z__);
    rz.r = q__1.r, rz.i = q__1.i;
    ib = 3;
    i__1 = nn;
    for (i__ = ib; i__ <= i__1; ++i__) {
	i__2 = k;
	r__1 = ak + *fnu;
	q__4.r = r__1, q__4.i = (float)0.;
	q__3.r = q__4.r * rz.r - q__4.i * rz.i, q__3.i = q__4.r * rz.i + 
		q__4.i * rz.r;
	i__3 = k + 1;
	q__2.r = q__3.r * y[i__3].r - q__3.i * y[i__3].i, q__2.i = q__3.r * y[
		i__3].i + q__3.i * y[i__3].r;
	i__4 = k + 2;
	q__1.r = q__2.r + y[i__4].r, q__1.i = q__2.i + y[i__4].i;
	y[i__2].r = q__1.r, y[i__2].i = q__1.i;
	ak += (float)-1.;
	--k;
/* L60: */
    }
    if (koded == 0) {
	return 0;
    }
    c_exp(&q__1, &cz);
    ck.r = q__1.r, ck.i = q__1.i;
    i__1 = nn;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	i__3 = i__;
	q__1.r = y[i__3].r * ck.r - y[i__3].i * ck.i, q__1.i = y[i__3].r * 
		ck.i + y[i__3].i * ck.r;
	y[i__2].r = q__1.r, y[i__2].i = q__1.i;
/* L70: */
    }
    return 0;
L80:
    *nz = -1;
    return 0;
L90:
    *nz = -2;
    return 0;
} /* casyi_ */

#ifdef __cplusplus
	}
#endif
