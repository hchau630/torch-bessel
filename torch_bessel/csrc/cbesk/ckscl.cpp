/* fortran/cbesk/ckscl.f -- translated by f2c (version 20240504).
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

/* Subroutine */ int ckscl_(complex *zr, real *fnu, integer *n, complex *y, 
	integer *nz, complex *rz, real *ascle, real *tol, real *elim)
{
    /* Initialized data */

    static complex czero = {(float)0.,(float)0.};

    /* System generated locals */
    integer i__1, i__2;
    real r__1, r__2;
    complex q__1, q__2, q__3;

    /* Builtin functions */
    double c_abs(complex *), log(doublereal);
    void c_log(complex *, complex *);
    double r_imag(complex *), exp(doublereal), cos(doublereal), sin(
	    doublereal);

    /* Local variables */
    static integer i__, k;
    static complex s1, s2;
    static real aa;
    static integer ic;
    static complex ck;
    static real as, fn;
    static complex cs;
    static integer kk;
    static complex cy[2];
    static integer nn;
    static complex zd;
    static integer nw;
    static real xx, acs, elm, csi, csr, zri;
    static complex celm;
    static real alas;
    extern /* Subroutine */ int cuchk_(complex *, integer *, real *, real *);
    static real helim;

/* ***BEGIN PROLOGUE  CKSCL */
/* ***REFER TO  CBKNU,CUNK1,CUNK2 */

/*     SET K FUNCTIONS TO ZERO ON UNDERFLOW, CONTINUE RECURRENCE */
/*     ON SCALED FUNCTIONS UNTIL TWO MEMBERS COME ON SCALE, THEN */
/*     RETURN WITH MIN(NZ+2,N) VALUES SCALED BY 1/TOL. */

/* ***ROUTINES CALLED  CUCHK */
/* ***END PROLOGUE  CKSCL */
    /* Parameter adjustments */
    --y;

    /* Function Body */

    *nz = 0;
    ic = 0;
    xx = zr->r;
    nn = min(2,*n);
    i__1 = nn;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	s1.r = y[i__2].r, s1.i = y[i__2].i;
	i__2 = i__ - 1;
	cy[i__2].r = s1.r, cy[i__2].i = s1.i;
	as = c_abs(&s1);
	acs = -xx + log(as);
	++(*nz);
	i__2 = i__;
	y[i__2].r = czero.r, y[i__2].i = czero.i;
	if (acs < -(*elim)) {
	    goto L10;
	}
	q__2.r = -zr->r, q__2.i = -zr->i;
	c_log(&q__3, &s1);
	q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
	cs.r = q__1.r, cs.i = q__1.i;
	csr = cs.r;
	csi = r_imag(&cs);
	aa = exp(csr) / *tol;
	q__2.r = aa, q__2.i = (float)0.;
	r__1 = cos(csi);
	r__2 = sin(csi);
	q__3.r = r__1, q__3.i = r__2;
	q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i 
		+ q__2.i * q__3.r;
	cs.r = q__1.r, cs.i = q__1.i;
	cuchk_(&cs, &nw, ascle, tol);
	if (nw != 0) {
	    goto L10;
	}
	i__2 = i__;
	y[i__2].r = cs.r, y[i__2].i = cs.i;
	--(*nz);
	ic = i__;
L10:
	;
    }
    if (*n == 1) {
	return 0;
    }
    if (ic > 1) {
	goto L20;
    }
    y[1].r = czero.r, y[1].i = czero.i;
    *nz = 2;
L20:
    if (*n == 2) {
	return 0;
    }
    if (*nz == 0) {
	return 0;
    }
    fn = *fnu + (float)1.;
    q__2.r = fn, q__2.i = (float)0.;
    q__1.r = q__2.r * rz->r - q__2.i * rz->i, q__1.i = q__2.r * rz->i + 
	    q__2.i * rz->r;
    ck.r = q__1.r, ck.i = q__1.i;
    s1.r = cy[0].r, s1.i = cy[0].i;
    s2.r = cy[1].r, s2.i = cy[1].i;
    helim = *elim * (float).5;
    elm = exp(-(*elim));
    q__1.r = elm, q__1.i = (float)0.;
    celm.r = q__1.r, celm.i = q__1.i;
    zri = r_imag(zr);
    zd.r = zr->r, zd.i = zr->i;

/*     FIND TWO CONSECUTIVE Y VALUES ON SCALE. SCALE RECURRENCE IF */
/*     S2 GETS LARGER THAN EXP(ELIM/2) */

    i__1 = *n;
    for (i__ = 3; i__ <= i__1; ++i__) {
	kk = i__;
	cs.r = s2.r, cs.i = s2.i;
	q__2.r = ck.r * s2.r - ck.i * s2.i, q__2.i = ck.r * s2.i + ck.i * 
		s2.r;
	q__1.r = q__2.r + s1.r, q__1.i = q__2.i + s1.i;
	s2.r = q__1.r, s2.i = q__1.i;
	s1.r = cs.r, s1.i = cs.i;
	q__1.r = ck.r + rz->r, q__1.i = ck.i + rz->i;
	ck.r = q__1.r, ck.i = q__1.i;
	as = c_abs(&s2);
	alas = log(as);
	acs = -xx + alas;
	++(*nz);
	i__2 = i__;
	y[i__2].r = czero.r, y[i__2].i = czero.i;
	if (acs < -(*elim)) {
	    goto L25;
	}
	q__2.r = -zd.r, q__2.i = -zd.i;
	c_log(&q__3, &s2);
	q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
	cs.r = q__1.r, cs.i = q__1.i;
	csr = cs.r;
	csi = r_imag(&cs);
	aa = exp(csr) / *tol;
	q__2.r = aa, q__2.i = (float)0.;
	r__1 = cos(csi);
	r__2 = sin(csi);
	q__3.r = r__1, q__3.i = r__2;
	q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i 
		+ q__2.i * q__3.r;
	cs.r = q__1.r, cs.i = q__1.i;
	cuchk_(&cs, &nw, ascle, tol);
	if (nw != 0) {
	    goto L25;
	}
	i__2 = i__;
	y[i__2].r = cs.r, y[i__2].i = cs.i;
	--(*nz);
	if (ic == kk - 1) {
	    goto L40;
	}
	ic = kk;
	goto L30;
L25:
	if (alas < helim) {
	    goto L30;
	}
	xx -= *elim;
	q__1.r = s1.r * celm.r - s1.i * celm.i, q__1.i = s1.r * celm.i + s1.i 
		* celm.r;
	s1.r = q__1.r, s1.i = q__1.i;
	q__1.r = s2.r * celm.r - s2.i * celm.i, q__1.i = s2.r * celm.i + s2.i 
		* celm.r;
	s2.r = q__1.r, s2.i = q__1.i;
	q__1.r = xx, q__1.i = zri;
	zd.r = q__1.r, zd.i = q__1.i;
L30:
	;
    }
    *nz = *n;
    if (ic == *n) {
	*nz = *n - 1;
    }
    goto L45;
L40:
    *nz = kk - 2;
L45:
    i__1 = *nz;
    for (k = 1; k <= i__1; ++k) {
	i__2 = k;
	y[i__2].r = czero.r, y[i__2].i = czero.i;
/* L50: */
    }
    return 0;
} /* ckscl_ */

#ifdef __cplusplus
	}
#endif
