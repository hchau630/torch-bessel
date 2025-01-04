/* fortran/cbesk/cuoik.f -- translated by f2c (version 20240504).
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

/* Subroutine */ int cuoik_(complex *z__, real *fnu, integer *kode, integer *
	ikflg, integer *n, complex *y, integer *nuf, real *tol, real *elim, 
	real *alim)
{
    /* Initialized data */

    static complex czero = {(float)0.,(float)0.};
    static real aic = (float)1.265512123484645396;

    /* System generated locals */
    integer i__1, i__2;
    real r__1, r__2;
    complex q__1, q__2, q__3, q__4, q__5;

    /* Builtin functions */
    double r_imag(complex *);
    void r_cnjg(complex *, complex *);
    double c_abs(complex *), log(doublereal);
    void c_log(complex *, complex *);
    double exp(doublereal), cos(doublereal), sin(doublereal);

    /* Local variables */
    static integer i__;
    static real x, ax, ay;
    static complex zb, cz;
    static integer nn, nw;
    static complex zn, zr;
    static real yy;
    static complex arg, phi;
    static real fnn, gnn, gnu, rcz;
    static complex sum;
    static real aarg, aphi;
    static integer init;
    static complex asum, bsum, cwrk[16], zeta1, zeta2;
    static real ascle;
    extern /* Subroutine */ int cuchk_(complex *, integer *, real *, real *), 
	    cunhj_(complex *, real *, integer *, real *, complex *, complex *,
	     complex *, complex *, complex *, complex *), cunik_(complex *, 
	    real *, integer *, integer *, real *, integer *, complex *, 
	    complex *, complex *, complex *, complex *);
    static integer iform;
    extern doublereal r1mach_(integer *);

/* ***BEGIN PROLOGUE  CUOIK */
/* ***REFER TO  CBESI,CBESK,CBESH */

/*     CUOIK COMPUTES THE LEADING TERMS OF THE UNIFORM ASYMPTOTIC */
/*     EXPANSIONS FOR THE I AND K FUNCTIONS AND COMPARES THEM */
/*     (IN LOGARITHMIC FORM) TO ALIM AND ELIM FOR OVER AND UNDERFLOW */
/*     WHERE ALIM.LT.ELIM. IF THE MAGNITUDE, BASED ON THE LEADING */
/*     EXPONENTIAL, IS LESS THAN ALIM OR GREATER THAN -ALIM, THEN */
/*     THE RESULT IS ON SCALE. IF NOT, THEN A REFINED TEST USING OTHER */
/*     MULTIPLIERS (IN LOGARITHMIC FORM) IS MADE BASED ON ELIM. HERE */
/*     EXP(-ELIM)=SMALLEST MACHINE NUMBER*1.0E+3 AND EXP(-ALIM)= */
/*     EXP(-ELIM)/TOL */

/*     IKFLG=1 MEANS THE I SEQUENCE IS TESTED */
/*          =2 MEANS THE K SEQUENCE IS TESTED */
/*     NUF = 0 MEANS THE LAST MEMBER OF THE SEQUENCE IS ON SCALE */
/*         =-1 MEANS AN OVERFLOW WOULD OCCUR */
/*     IKFLG=1 AND NUF.GT.0 MEANS THE LAST NUF Y VALUES WERE SET TO ZERO */
/*             THE FIRST N-NUF VALUES MUST BE SET BY ANOTHER ROUTINE */
/*     IKFLG=2 AND NUF.EQ.N MEANS ALL Y VALUES WERE SET TO ZERO */
/*     IKFLG=2 AND 0.LT.NUF.LT.N NOT CONSIDERED. Y MUST BE SET BY */
/*             ANOTHER ROUTINE */

/* ***ROUTINES CALLED  CUCHK,CUNHJ,CUNIK,R1MACH */
/* ***END PROLOGUE  CUOIK */
    /* Parameter adjustments */
    --y;

    /* Function Body */
    *nuf = 0;
    nn = *n;
    x = z__->r;
    zr.r = z__->r, zr.i = z__->i;
    if (x < (float)0.) {
	q__1.r = -z__->r, q__1.i = -z__->i;
	zr.r = q__1.r, zr.i = q__1.i;
    }
    zb.r = zr.r, zb.i = zr.i;
    yy = r_imag(&zr);
    ax = dabs(x) * (float)1.7321;
    ay = dabs(yy);
    iform = 1;
    if (ay > ax) {
	iform = 2;
    }
    gnu = dmax(*fnu,(float)1.);
    if (*ikflg == 1) {
	goto L10;
    }
    fnn = (real) nn;
    gnn = *fnu + fnn - (float)1.;
    gnu = dmax(gnn,fnn);
L10:
/* ----------------------------------------------------------------------- */
/*     ONLY THE MAGNITUDE OF ARG AND PHI ARE NEEDED ALONG WITH THE */
/*     REAL PARTS OF ZETA1, ZETA2 AND ZB. NO ATTEMPT IS MADE TO GET */
/*     THE SIGN OF THE IMAGINARY PART CORRECT. */
/* ----------------------------------------------------------------------- */
    if (iform == 2) {
	goto L20;
    }
    init = 0;
    cunik_(&zr, &gnu, ikflg, &c__1, tol, &init, &phi, &zeta1, &zeta2, &sum, 
	    cwrk);
    q__2.r = -zeta1.r, q__2.i = -zeta1.i;
    q__1.r = q__2.r + zeta2.r, q__1.i = q__2.i + zeta2.i;
    cz.r = q__1.r, cz.i = q__1.i;
    goto L40;
L20:
    q__2.r = -zr.r, q__2.i = -zr.i;
    q__1.r = q__2.r * (float)0. - q__2.i * (float)1., q__1.i = q__2.r * (
	    float)1. + q__2.i * (float)0.;
    zn.r = q__1.r, zn.i = q__1.i;
    if (yy > (float)0.) {
	goto L30;
    }
    q__2.r = -zn.r, q__2.i = -zn.i;
    r_cnjg(&q__1, &q__2);
    zn.r = q__1.r, zn.i = q__1.i;
L30:
    cunhj_(&zn, &gnu, &c__1, tol, &phi, &arg, &zeta1, &zeta2, &asum, &bsum);
    q__2.r = -zeta1.r, q__2.i = -zeta1.i;
    q__1.r = q__2.r + zeta2.r, q__1.i = q__2.i + zeta2.i;
    cz.r = q__1.r, cz.i = q__1.i;
    aarg = c_abs(&arg);
L40:
    if (*kode == 2) {
	q__1.r = cz.r - zb.r, q__1.i = cz.i - zb.i;
	cz.r = q__1.r, cz.i = q__1.i;
    }
    if (*ikflg == 2) {
	q__1.r = -cz.r, q__1.i = -cz.i;
	cz.r = q__1.r, cz.i = q__1.i;
    }
    aphi = c_abs(&phi);
    rcz = cz.r;
/* ----------------------------------------------------------------------- */
/*     OVERFLOW TEST */
/* ----------------------------------------------------------------------- */
    if (rcz > *elim) {
	goto L170;
    }
    if (rcz < *alim) {
	goto L50;
    }
    rcz += log(aphi);
    if (iform == 2) {
	rcz = rcz - log(aarg) * (float).25 - aic;
    }
    if (rcz > *elim) {
	goto L170;
    }
    goto L100;
L50:
/* ----------------------------------------------------------------------- */
/*     UNDERFLOW TEST */
/* ----------------------------------------------------------------------- */
    if (rcz < -(*elim)) {
	goto L60;
    }
    if (rcz > -(*alim)) {
	goto L100;
    }
    rcz += log(aphi);
    if (iform == 2) {
	rcz = rcz - log(aarg) * (float).25 - aic;
    }
    if (rcz > -(*elim)) {
	goto L80;
    }
L60:
    i__1 = nn;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	y[i__2].r = czero.r, y[i__2].i = czero.i;
/* L70: */
    }
    *nuf = nn;
    return 0;
L80:
    ascle = r1mach_(&c__1) * (float)1e3 / *tol;
    c_log(&q__2, &phi);
    q__1.r = cz.r + q__2.r, q__1.i = cz.i + q__2.i;
    cz.r = q__1.r, cz.i = q__1.i;
    if (iform == 1) {
	goto L90;
    }
    c_log(&q__4, &arg);
    q__3.r = q__4.r * (float).25 - q__4.i * (float)0., q__3.i = q__4.r * (
	    float)0. + q__4.i * (float).25;
    q__2.r = cz.r - q__3.r, q__2.i = cz.i - q__3.i;
    q__5.r = aic, q__5.i = (float)0.;
    q__1.r = q__2.r - q__5.r, q__1.i = q__2.i - q__5.i;
    cz.r = q__1.r, cz.i = q__1.i;
L90:
    ax = exp(rcz) / *tol;
    ay = r_imag(&cz);
    q__2.r = ax, q__2.i = (float)0.;
    r__1 = cos(ay);
    r__2 = sin(ay);
    q__3.r = r__1, q__3.i = r__2;
    q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i + 
	    q__2.i * q__3.r;
    cz.r = q__1.r, cz.i = q__1.i;
    cuchk_(&cz, &nw, &ascle, tol);
    if (nw == 1) {
	goto L60;
    }
L100:
    if (*ikflg == 2) {
	return 0;
    }
    if (*n == 1) {
	return 0;
    }
/* ----------------------------------------------------------------------- */
/*     SET UNDERFLOWS ON I SEQUENCE */
/* ----------------------------------------------------------------------- */
L110:
    gnu = *fnu + (real) (nn - 1);
    if (iform == 2) {
	goto L120;
    }
    init = 0;
    cunik_(&zr, &gnu, ikflg, &c__1, tol, &init, &phi, &zeta1, &zeta2, &sum, 
	    cwrk);
    q__2.r = -zeta1.r, q__2.i = -zeta1.i;
    q__1.r = q__2.r + zeta2.r, q__1.i = q__2.i + zeta2.i;
    cz.r = q__1.r, cz.i = q__1.i;
    goto L130;
L120:
    cunhj_(&zn, &gnu, &c__1, tol, &phi, &arg, &zeta1, &zeta2, &asum, &bsum);
    q__2.r = -zeta1.r, q__2.i = -zeta1.i;
    q__1.r = q__2.r + zeta2.r, q__1.i = q__2.i + zeta2.i;
    cz.r = q__1.r, cz.i = q__1.i;
    aarg = c_abs(&arg);
L130:
    if (*kode == 2) {
	q__1.r = cz.r - zb.r, q__1.i = cz.i - zb.i;
	cz.r = q__1.r, cz.i = q__1.i;
    }
    aphi = c_abs(&phi);
    rcz = cz.r;
    if (rcz < -(*elim)) {
	goto L140;
    }
    if (rcz > -(*alim)) {
	return 0;
    }
    rcz += log(aphi);
    if (iform == 2) {
	rcz = rcz - log(aarg) * (float).25 - aic;
    }
    if (rcz > -(*elim)) {
	goto L150;
    }
L140:
    i__1 = nn;
    y[i__1].r = czero.r, y[i__1].i = czero.i;
    --nn;
    ++(*nuf);
    if (nn == 0) {
	return 0;
    }
    goto L110;
L150:
    ascle = r1mach_(&c__1) * (float)1e3 / *tol;
    c_log(&q__2, &phi);
    q__1.r = cz.r + q__2.r, q__1.i = cz.i + q__2.i;
    cz.r = q__1.r, cz.i = q__1.i;
    if (iform == 1) {
	goto L160;
    }
    c_log(&q__4, &arg);
    q__3.r = q__4.r * (float).25 - q__4.i * (float)0., q__3.i = q__4.r * (
	    float)0. + q__4.i * (float).25;
    q__2.r = cz.r - q__3.r, q__2.i = cz.i - q__3.i;
    q__5.r = aic, q__5.i = (float)0.;
    q__1.r = q__2.r - q__5.r, q__1.i = q__2.i - q__5.i;
    cz.r = q__1.r, cz.i = q__1.i;
L160:
    ax = exp(rcz) / *tol;
    ay = r_imag(&cz);
    q__2.r = ax, q__2.i = (float)0.;
    r__1 = cos(ay);
    r__2 = sin(ay);
    q__3.r = r__1, q__3.i = r__2;
    q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i + 
	    q__2.i * q__3.r;
    cz.r = q__1.r, cz.i = q__1.i;
    cuchk_(&cz, &nw, &ascle, tol);
    if (nw == 1) {
	goto L140;
    }
    return 0;
L170:
    *nuf = -1;
    return 0;
} /* cuoik_ */

#ifdef __cplusplus
	}
#endif
