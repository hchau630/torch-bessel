/* fortran/cbesk/cacon.f -- translated by f2c (version 20240504).
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
static complex c_b7 = {(float)2.,(float)0.};
static integer c__2 = 2;

/* Subroutine */ int cacon_(complex *z__, real *fnu, integer *kode, integer *
	mr, integer *n, complex *y, integer *nz, real *rl, real *fnul, real *
	tol, real *elim, real *alim)
{
    /* Initialized data */

    static real pi = (float)3.14159265358979324;
    static complex cone = {(float)1.,(float)0.};

    /* System generated locals */
    integer i__1, i__2;
    real r__1;
    complex q__1, q__2, q__3;

    /* Builtin functions */
    double r_sign(real *, real *), r_imag(complex *), cos(doublereal), sin(
	    doublereal);
    void c_div(complex *, complex *, complex *);
    double c_abs(complex *);

    /* Local variables */
    static integer i__;
    static complex c1, c2, s1, s2, ck, cs, cy[2];
    static integer nn, nw;
    static complex st, zn, rz;
    static real yy, c1i, c1m, as2;
    static complex sc1, sc2;
    static real c1r, arg, cpn;
    static integer iuf;
    static real fmr;
    static complex csr[3], css[3];
    static real sgn;
    static integer inu;
    static real bry[3], spn;
    static complex cscl, cscr, csgn;
    extern /* Subroutine */ int cs1s2_(complex *, complex *, complex *, 
	    integer *, real *, real *, integer *);
    static complex cspn;
    static integer kflag;
    static real ascle, bscle;
    extern /* Subroutine */ int cbinu_(complex *, real *, integer *, integer *
	    , complex *, integer *, real *, real *, real *, real *, real *), 
	    cbknu_(complex *, real *, integer *, integer *, complex *, 
	    integer *, real *, real *, real *);
    extern doublereal r1mach_(integer *);

/* ***BEGIN PROLOGUE  CACON */
/* ***REFER TO  CBESK,CBESH */

/*     CACON APPLIES THE ANALYTIC CONTINUATION FORMULA */

/*         K(FNU,ZN*EXP(MP))=K(FNU,ZN)*EXP(-MP*FNU) - MP*I(FNU,ZN) */
/*                 MP=PI*MR*CMPLX(0.0,1.0) */

/*     TO CONTINUE THE K FUNCTION FROM THE RIGHT HALF TO THE LEFT */
/*     HALF Z PLANE */

/* ***ROUTINES CALLED  CBINU,CBKNU,CS1S2,R1MACH */
/* ***END PROLOGUE  CACON */
    /* Parameter adjustments */
    --y;

    /* Function Body */
    *nz = 0;
    q__1.r = -z__->r, q__1.i = -z__->i;
    zn.r = q__1.r, zn.i = q__1.i;
    nn = *n;
    cbinu_(&zn, fnu, kode, &nn, &y[1], &nw, rl, fnul, tol, elim, alim);
    if (nw < 0) {
	goto L80;
    }
/* ----------------------------------------------------------------------- */
/*     ANALYTIC CONTINUATION TO THE LEFT HALF PLANE FOR THE K FUNCTION */
/* ----------------------------------------------------------------------- */
    nn = min(2,*n);
    cbknu_(&zn, fnu, kode, &nn, cy, &nw, tol, elim, alim);
    if (nw != 0) {
	goto L80;
    }
    s1.r = cy[0].r, s1.i = cy[0].i;
    fmr = (real) (*mr);
    sgn = -r_sign(&pi, &fmr);
    q__1.r = (float)0., q__1.i = sgn;
    csgn.r = q__1.r, csgn.i = q__1.i;
    if (*kode == 1) {
	goto L10;
    }
    yy = -r_imag(&zn);
    cpn = cos(yy);
    spn = sin(yy);
    q__2.r = cpn, q__2.i = spn;
    q__1.r = csgn.r * q__2.r - csgn.i * q__2.i, q__1.i = csgn.r * q__2.i + 
	    csgn.i * q__2.r;
    csgn.r = q__1.r, csgn.i = q__1.i;
L10:
/* ----------------------------------------------------------------------- */
/*     CALCULATE CSPN=EXP(FNU*PI*I) TO MINIMIZE LOSSES OF SIGNIFICANCE */
/*     WHEN FNU IS LARGE */
/* ----------------------------------------------------------------------- */
    inu = (integer) (*fnu);
    arg = (*fnu - (real) inu) * sgn;
    cpn = cos(arg);
    spn = sin(arg);
    q__1.r = cpn, q__1.i = spn;
    cspn.r = q__1.r, cspn.i = q__1.i;
    if (inu % 2 == 1) {
	q__1.r = -cspn.r, q__1.i = -cspn.i;
	cspn.r = q__1.r, cspn.i = q__1.i;
    }
    iuf = 0;
    c1.r = s1.r, c1.i = s1.i;
    c2.r = y[1].r, c2.i = y[1].i;
    ascle = r1mach_(&c__1) * (float)1e3 / *tol;
    if (*kode == 1) {
	goto L20;
    }
    cs1s2_(&zn, &c1, &c2, &nw, &ascle, alim, &iuf);
    *nz += nw;
    sc1.r = c1.r, sc1.i = c1.i;
L20:
    q__2.r = cspn.r * c1.r - cspn.i * c1.i, q__2.i = cspn.r * c1.i + cspn.i * 
	    c1.r;
    q__3.r = csgn.r * c2.r - csgn.i * c2.i, q__3.i = csgn.r * c2.i + csgn.i * 
	    c2.r;
    q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
    y[1].r = q__1.r, y[1].i = q__1.i;
    if (*n == 1) {
	return 0;
    }
    q__1.r = -cspn.r, q__1.i = -cspn.i;
    cspn.r = q__1.r, cspn.i = q__1.i;
    s2.r = cy[1].r, s2.i = cy[1].i;
    c1.r = s2.r, c1.i = s2.i;
    c2.r = y[2].r, c2.i = y[2].i;
    if (*kode == 1) {
	goto L30;
    }
    cs1s2_(&zn, &c1, &c2, &nw, &ascle, alim, &iuf);
    *nz += nw;
    sc2.r = c1.r, sc2.i = c1.i;
L30:
    q__2.r = cspn.r * c1.r - cspn.i * c1.i, q__2.i = cspn.r * c1.i + cspn.i * 
	    c1.r;
    q__3.r = csgn.r * c2.r - csgn.i * c2.i, q__3.i = csgn.r * c2.i + csgn.i * 
	    c2.r;
    q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
    y[2].r = q__1.r, y[2].i = q__1.i;
    if (*n == 2) {
	return 0;
    }
    q__1.r = -cspn.r, q__1.i = -cspn.i;
    cspn.r = q__1.r, cspn.i = q__1.i;
    c_div(&q__1, &c_b7, &zn);
    rz.r = q__1.r, rz.i = q__1.i;
    r__1 = *fnu + (float)1.;
    q__2.r = r__1, q__2.i = (float)0.;
    q__1.r = q__2.r * rz.r - q__2.i * rz.i, q__1.i = q__2.r * rz.i + q__2.i * 
	    rz.r;
    ck.r = q__1.r, ck.i = q__1.i;
/* ----------------------------------------------------------------------- */
/*     SCALE NEAR EXPONENT EXTREMES DURING RECURRENCE ON K FUNCTIONS */
/* ----------------------------------------------------------------------- */
    r__1 = (float)1. / *tol;
    q__1.r = r__1, q__1.i = (float)0.;
    cscl.r = q__1.r, cscl.i = q__1.i;
    q__1.r = *tol, q__1.i = (float)0.;
    cscr.r = q__1.r, cscr.i = q__1.i;
    css[0].r = cscl.r, css[0].i = cscl.i;
    css[1].r = cone.r, css[1].i = cone.i;
    css[2].r = cscr.r, css[2].i = cscr.i;
    csr[0].r = cscr.r, csr[0].i = cscr.i;
    csr[1].r = cone.r, csr[1].i = cone.i;
    csr[2].r = cscl.r, csr[2].i = cscl.i;
    bry[0] = ascle;
    bry[1] = (float)1. / ascle;
    bry[2] = r1mach_(&c__2);
    as2 = c_abs(&s2);
    kflag = 2;
    if (as2 > bry[0]) {
	goto L40;
    }
    kflag = 1;
    goto L50;
L40:
    if (as2 < bry[1]) {
	goto L50;
    }
    kflag = 3;
L50:
    bscle = bry[kflag - 1];
    i__1 = kflag - 1;
    q__1.r = s1.r * css[i__1].r - s1.i * css[i__1].i, q__1.i = s1.r * css[
	    i__1].i + s1.i * css[i__1].r;
    s1.r = q__1.r, s1.i = q__1.i;
    i__1 = kflag - 1;
    q__1.r = s2.r * css[i__1].r - s2.i * css[i__1].i, q__1.i = s2.r * css[
	    i__1].i + s2.i * css[i__1].r;
    s2.r = q__1.r, s2.i = q__1.i;
    i__1 = kflag - 1;
    cs.r = csr[i__1].r, cs.i = csr[i__1].i;
    i__1 = *n;
    for (i__ = 3; i__ <= i__1; ++i__) {
	st.r = s2.r, st.i = s2.i;
	q__2.r = ck.r * s2.r - ck.i * s2.i, q__2.i = ck.r * s2.i + ck.i * 
		s2.r;
	q__1.r = q__2.r + s1.r, q__1.i = q__2.i + s1.i;
	s2.r = q__1.r, s2.i = q__1.i;
	s1.r = st.r, s1.i = st.i;
	q__1.r = s2.r * cs.r - s2.i * cs.i, q__1.i = s2.r * cs.i + s2.i * 
		cs.r;
	c1.r = q__1.r, c1.i = q__1.i;
	st.r = c1.r, st.i = c1.i;
	i__2 = i__;
	c2.r = y[i__2].r, c2.i = y[i__2].i;
	if (*kode == 1) {
	    goto L60;
	}
	if (iuf < 0) {
	    goto L60;
	}
	cs1s2_(&zn, &c1, &c2, &nw, &ascle, alim, &iuf);
	*nz += nw;
	sc1.r = sc2.r, sc1.i = sc2.i;
	sc2.r = c1.r, sc2.i = c1.i;
	if (iuf != 3) {
	    goto L60;
	}
	iuf = -4;
	i__2 = kflag - 1;
	q__1.r = sc1.r * css[i__2].r - sc1.i * css[i__2].i, q__1.i = sc1.r * 
		css[i__2].i + sc1.i * css[i__2].r;
	s1.r = q__1.r, s1.i = q__1.i;
	i__2 = kflag - 1;
	q__1.r = sc2.r * css[i__2].r - sc2.i * css[i__2].i, q__1.i = sc2.r * 
		css[i__2].i + sc2.i * css[i__2].r;
	s2.r = q__1.r, s2.i = q__1.i;
	st.r = sc2.r, st.i = sc2.i;
L60:
	i__2 = i__;
	q__2.r = cspn.r * c1.r - cspn.i * c1.i, q__2.i = cspn.r * c1.i + 
		cspn.i * c1.r;
	q__3.r = csgn.r * c2.r - csgn.i * c2.i, q__3.i = csgn.r * c2.i + 
		csgn.i * c2.r;
	q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
	y[i__2].r = q__1.r, y[i__2].i = q__1.i;
	q__1.r = ck.r + rz.r, q__1.i = ck.i + rz.i;
	ck.r = q__1.r, ck.i = q__1.i;
	q__1.r = -cspn.r, q__1.i = -cspn.i;
	cspn.r = q__1.r, cspn.i = q__1.i;
	if (kflag >= 3) {
	    goto L70;
	}
	c1r = c1.r;
	c1i = r_imag(&c1);
	c1r = dabs(c1r);
	c1i = dabs(c1i);
	c1m = dmax(c1r,c1i);
	if (c1m <= bscle) {
	    goto L70;
	}
	++kflag;
	bscle = bry[kflag - 1];
	q__1.r = s1.r * cs.r - s1.i * cs.i, q__1.i = s1.r * cs.i + s1.i * 
		cs.r;
	s1.r = q__1.r, s1.i = q__1.i;
	s2.r = st.r, s2.i = st.i;
	i__2 = kflag - 1;
	q__1.r = s1.r * css[i__2].r - s1.i * css[i__2].i, q__1.i = s1.r * css[
		i__2].i + s1.i * css[i__2].r;
	s1.r = q__1.r, s1.i = q__1.i;
	i__2 = kflag - 1;
	q__1.r = s2.r * css[i__2].r - s2.i * css[i__2].i, q__1.i = s2.r * css[
		i__2].i + s2.i * css[i__2].r;
	s2.r = q__1.r, s2.i = q__1.i;
	i__2 = kflag - 1;
	cs.r = csr[i__2].r, cs.i = csr[i__2].i;
L70:
	;
    }
    return 0;
L80:
    *nz = -1;
    if (nw == -2) {
	*nz = -2;
    }
    return 0;
} /* cacon_ */

#ifdef __cplusplus
	}
#endif
