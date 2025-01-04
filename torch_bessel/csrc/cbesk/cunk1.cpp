/* fortran/cbesk/cunk1.f -- translated by f2c (version 20240504).
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
static integer c__2 = 2;
static integer c__0 = 0;
static complex c_b14 = {(float)2.,(float)0.};

/* Subroutine */ int cunk1_(complex *z__, real *fnu, integer *kode, integer *
	mr, integer *n, complex *y, integer *nz, real *tol, real *elim, real *
	alim)
{
    /* Initialized data */

    static complex czero = {(float)0.,(float)0.};
    static complex cone = {(float)1.,(float)0.};
    static real pi = (float)3.14159265358979324;

    /* System generated locals */
    integer i__1, i__2, i__3;
    real r__1, r__2;
    complex q__1, q__2, q__3, q__4, q__5;

    /* Builtin functions */
    void c_div(complex *, complex *, complex *);
    double c_abs(complex *), log(doublereal), r_imag(complex *), exp(
	    doublereal), cos(doublereal), sin(doublereal), r_sign(real *, 
	    real *);

    /* Local variables */
    static integer i__, j, k, m;
    static real x;
    static complex c1, c2, s1, s2;
    static integer ib, ic;
    static complex ck;
    static real fn;
    static integer il;
    static complex cs;
    static integer kk;
    static complex cy[2];
    static integer nw;
    static complex rz, zr;
    static real c2i, c2m, c2r, rs1, ang;
    static complex cfn;
    static real asc, fnf;
    static integer ifn;
    static complex phi[2];
    static real cpn;
    static integer iuf;
    static real fmr;
    static complex csr[3], css[3];
    static real sgn;
    static integer inu;
    static real bry[3], spn;
    static complex sum[2];
    static real aphi;
    static complex cscl, phid, crsc, csgn;
    extern /* Subroutine */ int cs1s2_(complex *, complex *, complex *, 
	    integer *, real *, real *, integer *);
    static complex cspn;
    static integer init[2];
    static complex cwrk[48]	/* was [16][3] */, sumd, zeta1[2], zeta2[2];
    static integer iflag, kflag;
    static real ascle;
    static integer kdflg;
    extern /* Subroutine */ int cuchk_(complex *, integer *, real *, real *);
    static integer ipard, initd;
    extern /* Subroutine */ int cunik_(complex *, real *, integer *, integer *
	    , real *, integer *, complex *, complex *, complex *, complex *, 
	    complex *);
    extern doublereal r1mach_(integer *);
    static complex zeta1d, zeta2d;

/* ***BEGIN PROLOGUE  CUNK1 */
/* ***REFER TO  CBESK */

/*     CUNK1 COMPUTES K(FNU,Z) AND ITS ANALYTIC CONTINUATION FROM THE */
/*     RIGHT HALF PLANE TO THE LEFT HALF PLANE BY MEANS OF THE */
/*     UNIFORM ASYMPTOTIC EXPANSION. */
/*     MR INDICATES THE DIRECTION OF ROTATION FOR ANALYTIC CONTINUATION. */
/*     NZ=-1 MEANS AN OVERFLOW WILL OCCUR */

/* ***ROUTINES CALLED  CS1S2,CUCHK,CUNIK,R1MACH */
/* ***END PROLOGUE  CUNK1 */
    /* Parameter adjustments */
    --y;

    /* Function Body */

    kdflg = 1;
    *nz = 0;
/* ----------------------------------------------------------------------- */
/*     EXP(-ALIM)=EXP(-ELIM)/TOL=APPROX. ONE PRECISION GREATER THAN */
/*     THE UNDERFLOW LIMIT */
/* ----------------------------------------------------------------------- */
    r__1 = (float)1. / *tol;
    q__1.r = r__1, q__1.i = (float)0.;
    cscl.r = q__1.r, cscl.i = q__1.i;
    q__1.r = *tol, q__1.i = (float)0.;
    crsc.r = q__1.r, crsc.i = q__1.i;
    css[0].r = cscl.r, css[0].i = cscl.i;
    css[1].r = cone.r, css[1].i = cone.i;
    css[2].r = crsc.r, css[2].i = crsc.i;
    csr[0].r = crsc.r, csr[0].i = crsc.i;
    csr[1].r = cone.r, csr[1].i = cone.i;
    csr[2].r = cscl.r, csr[2].i = cscl.i;
    bry[0] = r1mach_(&c__1) * (float)1e3 / *tol;
    bry[1] = (float)1. / bry[0];
    bry[2] = r1mach_(&c__2);
    x = z__->r;
    zr.r = z__->r, zr.i = z__->i;
    if (x < (float)0.) {
	q__1.r = -z__->r, q__1.i = -z__->i;
	zr.r = q__1.r, zr.i = q__1.i;
    }
    j = 2;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* ----------------------------------------------------------------------- */
/*     J FLIP FLOPS BETWEEN 1 AND 2 IN J = 3 - J */
/* ----------------------------------------------------------------------- */
	j = 3 - j;
	fn = *fnu + (real) (i__ - 1);
	init[j - 1] = 0;
	cunik_(&zr, &fn, &c__2, &c__0, tol, &init[j - 1], &phi[j - 1], &zeta1[
		j - 1], &zeta2[j - 1], &sum[j - 1], &cwrk[(j << 4) - 16]);
	if (*kode == 1) {
	    goto L20;
	}
	q__1.r = fn, q__1.i = (float)0.;
	cfn.r = q__1.r, cfn.i = q__1.i;
	i__2 = j - 1;
	i__3 = j - 1;
	q__4.r = zr.r + zeta2[i__3].r, q__4.i = zr.i + zeta2[i__3].i;
	c_div(&q__3, &cfn, &q__4);
	q__2.r = cfn.r * q__3.r - cfn.i * q__3.i, q__2.i = cfn.r * q__3.i + 
		cfn.i * q__3.r;
	q__1.r = zeta1[i__2].r - q__2.r, q__1.i = zeta1[i__2].i - q__2.i;
	s1.r = q__1.r, s1.i = q__1.i;
	goto L30;
L20:
	i__2 = j - 1;
	i__3 = j - 1;
	q__1.r = zeta1[i__2].r - zeta2[i__3].r, q__1.i = zeta1[i__2].i - 
		zeta2[i__3].i;
	s1.r = q__1.r, s1.i = q__1.i;
L30:
/* ----------------------------------------------------------------------- */
/*     TEST FOR UNDERFLOW AND OVERFLOW */
/* ----------------------------------------------------------------------- */
	rs1 = s1.r;
	if (dabs(rs1) > *elim) {
	    goto L60;
	}
	if (kdflg == 1) {
	    kflag = 2;
	}
	if (dabs(rs1) < *alim) {
	    goto L40;
	}
/* ----------------------------------------------------------------------- */
/*     REFINE  TEST AND SCALE */
/* ----------------------------------------------------------------------- */
	aphi = c_abs(&phi[j - 1]);
	rs1 += log(aphi);
	if (dabs(rs1) > *elim) {
	    goto L60;
	}
	if (kdflg == 1) {
	    kflag = 1;
	}
	if (rs1 < (float)0.) {
	    goto L40;
	}
	if (kdflg == 1) {
	    kflag = 3;
	}
L40:
/* ----------------------------------------------------------------------- */
/*     SCALE S1 TO KEEP INTERMEDIATE ARITHMETIC ON SCALE NEAR */
/*     EXPONENT EXTREMES */
/* ----------------------------------------------------------------------- */
	i__2 = j - 1;
	i__3 = j - 1;
	q__1.r = phi[i__2].r * sum[i__3].r - phi[i__2].i * sum[i__3].i, 
		q__1.i = phi[i__2].r * sum[i__3].i + phi[i__2].i * sum[i__3]
		.r;
	s2.r = q__1.r, s2.i = q__1.i;
	c2r = s1.r;
	c2i = r_imag(&s1);
	i__2 = kflag - 1;
	c2m = exp(c2r) * css[i__2].r;
	q__2.r = c2m, q__2.i = (float)0.;
	r__1 = cos(c2i);
	r__2 = sin(c2i);
	q__3.r = r__1, q__3.i = r__2;
	q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i 
		+ q__2.i * q__3.r;
	s1.r = q__1.r, s1.i = q__1.i;
	q__1.r = s2.r * s1.r - s2.i * s1.i, q__1.i = s2.r * s1.i + s2.i * 
		s1.r;
	s2.r = q__1.r, s2.i = q__1.i;
	if (kflag != 1) {
	    goto L50;
	}
	cuchk_(&s2, &nw, bry, tol);
	if (nw != 0) {
	    goto L60;
	}
L50:
	i__2 = kdflg - 1;
	cy[i__2].r = s2.r, cy[i__2].i = s2.i;
	i__2 = i__;
	i__3 = kflag - 1;
	q__1.r = s2.r * csr[i__3].r - s2.i * csr[i__3].i, q__1.i = s2.r * csr[
		i__3].i + s2.i * csr[i__3].r;
	y[i__2].r = q__1.r, y[i__2].i = q__1.i;
	if (kdflg == 2) {
	    goto L75;
	}
	kdflg = 2;
	goto L70;
L60:
	if (rs1 > (float)0.) {
	    goto L290;
	}
/* ----------------------------------------------------------------------- */
/*     FOR X.LT.0.0, THE I FUNCTION TO BE ADDED WILL OVERFLOW */
/* ----------------------------------------------------------------------- */
	if (x < (float)0.) {
	    goto L290;
	}
	kdflg = 1;
	i__2 = i__;
	y[i__2].r = czero.r, y[i__2].i = czero.i;
	++(*nz);
	if (i__ == 1) {
	    goto L70;
	}
	i__2 = i__ - 1;
	if (y[i__2].r == czero.r && y[i__2].i == czero.i) {
	    goto L70;
	}
	i__2 = i__ - 1;
	y[i__2].r = czero.r, y[i__2].i = czero.i;
	++(*nz);
L70:
	;
    }
    i__ = *n;
L75:
    c_div(&q__1, &c_b14, &zr);
    rz.r = q__1.r, rz.i = q__1.i;
    q__2.r = fn, q__2.i = (float)0.;
    q__1.r = q__2.r * rz.r - q__2.i * rz.i, q__1.i = q__2.r * rz.i + q__2.i * 
	    rz.r;
    ck.r = q__1.r, ck.i = q__1.i;
    ib = i__ + 1;
    if (*n < ib) {
	goto L160;
    }
/* ----------------------------------------------------------------------- */
/*     TEST LAST MEMBER FOR UNDERFLOW AND OVERFLOW, SET SEQUENCE TO ZERO */
/*     ON UNDERFLOW */
/* ----------------------------------------------------------------------- */
    fn = *fnu + (real) (*n - 1);
    ipard = 1;
    if (*mr != 0) {
	ipard = 0;
    }
    initd = 0;
    cunik_(&zr, &fn, &c__2, &ipard, tol, &initd, &phid, &zeta1d, &zeta2d, &
	    sumd, &cwrk[32]);
    if (*kode == 1) {
	goto L80;
    }
    q__1.r = fn, q__1.i = (float)0.;
    cfn.r = q__1.r, cfn.i = q__1.i;
    q__4.r = zr.r + zeta2d.r, q__4.i = zr.i + zeta2d.i;
    c_div(&q__3, &cfn, &q__4);
    q__2.r = cfn.r * q__3.r - cfn.i * q__3.i, q__2.i = cfn.r * q__3.i + cfn.i 
	    * q__3.r;
    q__1.r = zeta1d.r - q__2.r, q__1.i = zeta1d.i - q__2.i;
    s1.r = q__1.r, s1.i = q__1.i;
    goto L90;
L80:
    q__1.r = zeta1d.r - zeta2d.r, q__1.i = zeta1d.i - zeta2d.i;
    s1.r = q__1.r, s1.i = q__1.i;
L90:
    rs1 = s1.r;
    if (dabs(rs1) > *elim) {
	goto L95;
    }
    if (dabs(rs1) < *alim) {
	goto L100;
    }
/* ----------------------------------------------------------------------- */
/*     REFINE ESTIMATE AND TEST */
/* ----------------------------------------------------------------------- */
    aphi = c_abs(&phid);
    rs1 += log(aphi);
    if (dabs(rs1) < *elim) {
	goto L100;
    }
L95:
    if (rs1 > (float)0.) {
	goto L290;
    }
/* ----------------------------------------------------------------------- */
/*     FOR X.LT.0.0, THE I FUNCTION TO BE ADDED WILL OVERFLOW */
/* ----------------------------------------------------------------------- */
    if (x < (float)0.) {
	goto L290;
    }
    *nz = *n;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	y[i__2].r = czero.r, y[i__2].i = czero.i;
/* L96: */
    }
    return 0;
L100:
/* ----------------------------------------------------------------------- */
/*     RECUR FORWARD FOR REMAINDER OF THE SEQUENCE */
/* ----------------------------------------------------------------------- */
    s1.r = cy[0].r, s1.i = cy[0].i;
    s2.r = cy[1].r, s2.i = cy[1].i;
    i__1 = kflag - 1;
    c1.r = csr[i__1].r, c1.i = csr[i__1].i;
    ascle = bry[kflag - 1];
    i__1 = *n;
    for (i__ = ib; i__ <= i__1; ++i__) {
	c2.r = s2.r, c2.i = s2.i;
	q__2.r = ck.r * s2.r - ck.i * s2.i, q__2.i = ck.r * s2.i + ck.i * 
		s2.r;
	q__1.r = q__2.r + s1.r, q__1.i = q__2.i + s1.i;
	s2.r = q__1.r, s2.i = q__1.i;
	s1.r = c2.r, s1.i = c2.i;
	q__1.r = ck.r + rz.r, q__1.i = ck.i + rz.i;
	ck.r = q__1.r, ck.i = q__1.i;
	q__1.r = s2.r * c1.r - s2.i * c1.i, q__1.i = s2.r * c1.i + s2.i * 
		c1.r;
	c2.r = q__1.r, c2.i = q__1.i;
	i__2 = i__;
	y[i__2].r = c2.r, y[i__2].i = c2.i;
	if (kflag >= 3) {
	    goto L120;
	}
	c2r = c2.r;
	c2i = r_imag(&c2);
	c2r = dabs(c2r);
	c2i = dabs(c2i);
	c2m = dmax(c2r,c2i);
	if (c2m <= ascle) {
	    goto L120;
	}
	++kflag;
	ascle = bry[kflag - 1];
	q__1.r = s1.r * c1.r - s1.i * c1.i, q__1.i = s1.r * c1.i + s1.i * 
		c1.r;
	s1.r = q__1.r, s1.i = q__1.i;
	s2.r = c2.r, s2.i = c2.i;
	i__2 = kflag - 1;
	q__1.r = s1.r * css[i__2].r - s1.i * css[i__2].i, q__1.i = s1.r * css[
		i__2].i + s1.i * css[i__2].r;
	s1.r = q__1.r, s1.i = q__1.i;
	i__2 = kflag - 1;
	q__1.r = s2.r * css[i__2].r - s2.i * css[i__2].i, q__1.i = s2.r * css[
		i__2].i + s2.i * css[i__2].r;
	s2.r = q__1.r, s2.i = q__1.i;
	i__2 = kflag - 1;
	c1.r = csr[i__2].r, c1.i = csr[i__2].i;
L120:
	;
    }
L160:
    if (*mr == 0) {
	return 0;
    }
/* ----------------------------------------------------------------------- */
/*     ANALYTIC CONTINUATION FOR RE(Z).LT.0.0E0 */
/* ----------------------------------------------------------------------- */
    *nz = 0;
    fmr = (real) (*mr);
    sgn = -r_sign(&pi, &fmr);
/* ----------------------------------------------------------------------- */
/*     CSPN AND CSGN ARE COEFF OF K AND I FUNCIONS RESP. */
/* ----------------------------------------------------------------------- */
    q__1.r = (float)0., q__1.i = sgn;
    csgn.r = q__1.r, csgn.i = q__1.i;
    inu = (integer) (*fnu);
    fnf = *fnu - (real) inu;
    ifn = inu + *n - 1;
    ang = fnf * sgn;
    cpn = cos(ang);
    spn = sin(ang);
    q__1.r = cpn, q__1.i = spn;
    cspn.r = q__1.r, cspn.i = q__1.i;
    if (ifn % 2 == 1) {
	q__1.r = -cspn.r, q__1.i = -cspn.i;
	cspn.r = q__1.r, cspn.i = q__1.i;
    }
    asc = bry[0];
    kk = *n;
    iuf = 0;
    kdflg = 1;
    --ib;
    ic = ib - 1;
    i__1 = *n;
    for (k = 1; k <= i__1; ++k) {
	fn = *fnu + (real) (kk - 1);
/* ----------------------------------------------------------------------- */
/*     LOGIC TO SORT OUT CASES WHOSE PARAMETERS WERE SET FOR THE K */
/*     FUNCTION ABOVE */
/* ----------------------------------------------------------------------- */
	m = 3;
	if (*n > 2) {
	    goto L175;
	}
L170:
	initd = init[j - 1];
	i__2 = j - 1;
	phid.r = phi[i__2].r, phid.i = phi[i__2].i;
	i__2 = j - 1;
	zeta1d.r = zeta1[i__2].r, zeta1d.i = zeta1[i__2].i;
	i__2 = j - 1;
	zeta2d.r = zeta2[i__2].r, zeta2d.i = zeta2[i__2].i;
	i__2 = j - 1;
	sumd.r = sum[i__2].r, sumd.i = sum[i__2].i;
	m = j;
	j = 3 - j;
	goto L180;
L175:
	if (kk == *n && ib < *n) {
	    goto L180;
	}
	if (kk == ib || kk == ic) {
	    goto L170;
	}
	initd = 0;
L180:
	cunik_(&zr, &fn, &c__1, &c__0, tol, &initd, &phid, &zeta1d, &zeta2d, &
		sumd, &cwrk[(m << 4) - 16]);
	if (*kode == 1) {
	    goto L190;
	}
	q__1.r = fn, q__1.i = (float)0.;
	cfn.r = q__1.r, cfn.i = q__1.i;
	q__2.r = -zeta1d.r, q__2.i = -zeta1d.i;
	q__5.r = zr.r + zeta2d.r, q__5.i = zr.i + zeta2d.i;
	c_div(&q__4, &cfn, &q__5);
	q__3.r = cfn.r * q__4.r - cfn.i * q__4.i, q__3.i = cfn.r * q__4.i + 
		cfn.i * q__4.r;
	q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
	s1.r = q__1.r, s1.i = q__1.i;
	goto L200;
L190:
	q__2.r = -zeta1d.r, q__2.i = -zeta1d.i;
	q__1.r = q__2.r + zeta2d.r, q__1.i = q__2.i + zeta2d.i;
	s1.r = q__1.r, s1.i = q__1.i;
L200:
/* ----------------------------------------------------------------------- */
/*     TEST FOR UNDERFLOW AND OVERFLOW */
/* ----------------------------------------------------------------------- */
	rs1 = s1.r;
	if (dabs(rs1) > *elim) {
	    goto L250;
	}
	if (kdflg == 1) {
	    iflag = 2;
	}
	if (dabs(rs1) < *alim) {
	    goto L210;
	}
/* ----------------------------------------------------------------------- */
/*     REFINE  TEST AND SCALE */
/* ----------------------------------------------------------------------- */
	aphi = c_abs(&phid);
	rs1 += log(aphi);
	if (dabs(rs1) > *elim) {
	    goto L250;
	}
	if (kdflg == 1) {
	    iflag = 1;
	}
	if (rs1 < (float)0.) {
	    goto L210;
	}
	if (kdflg == 1) {
	    iflag = 3;
	}
L210:
	q__2.r = csgn.r * phid.r - csgn.i * phid.i, q__2.i = csgn.r * phid.i 
		+ csgn.i * phid.r;
	q__1.r = q__2.r * sumd.r - q__2.i * sumd.i, q__1.i = q__2.r * sumd.i 
		+ q__2.i * sumd.r;
	s2.r = q__1.r, s2.i = q__1.i;
	c2r = s1.r;
	c2i = r_imag(&s1);
	i__2 = iflag - 1;
	c2m = exp(c2r) * css[i__2].r;
	q__2.r = c2m, q__2.i = (float)0.;
	r__1 = cos(c2i);
	r__2 = sin(c2i);
	q__3.r = r__1, q__3.i = r__2;
	q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i 
		+ q__2.i * q__3.r;
	s1.r = q__1.r, s1.i = q__1.i;
	q__1.r = s2.r * s1.r - s2.i * s1.i, q__1.i = s2.r * s1.i + s2.i * 
		s1.r;
	s2.r = q__1.r, s2.i = q__1.i;
	if (iflag != 1) {
	    goto L220;
	}
	cuchk_(&s2, &nw, bry, tol);
	if (nw != 0) {
	    s2.r = (float)0., s2.i = (float)0.;
	}
L220:
	i__2 = kdflg - 1;
	cy[i__2].r = s2.r, cy[i__2].i = s2.i;
	c2.r = s2.r, c2.i = s2.i;
	i__2 = iflag - 1;
	q__1.r = s2.r * csr[i__2].r - s2.i * csr[i__2].i, q__1.i = s2.r * csr[
		i__2].i + s2.i * csr[i__2].r;
	s2.r = q__1.r, s2.i = q__1.i;
/* ----------------------------------------------------------------------- */
/*     ADD I AND K FUNCTIONS, K SEQUENCE IN Y(I), I=1,N */
/* ----------------------------------------------------------------------- */
	i__2 = kk;
	s1.r = y[i__2].r, s1.i = y[i__2].i;
	if (*kode == 1) {
	    goto L240;
	}
	cs1s2_(&zr, &s1, &s2, &nw, &asc, alim, &iuf);
	*nz += nw;
L240:
	i__2 = kk;
	q__2.r = s1.r * cspn.r - s1.i * cspn.i, q__2.i = s1.r * cspn.i + s1.i 
		* cspn.r;
	q__1.r = q__2.r + s2.r, q__1.i = q__2.i + s2.i;
	y[i__2].r = q__1.r, y[i__2].i = q__1.i;
	--kk;
	q__1.r = -cspn.r, q__1.i = -cspn.i;
	cspn.r = q__1.r, cspn.i = q__1.i;
	if (c2.r != czero.r || c2.i != czero.i) {
	    goto L245;
	}
	kdflg = 1;
	goto L260;
L245:
	if (kdflg == 2) {
	    goto L265;
	}
	kdflg = 2;
	goto L260;
L250:
	if (rs1 > (float)0.) {
	    goto L290;
	}
	s2.r = czero.r, s2.i = czero.i;
	goto L220;
L260:
	;
    }
    k = *n;
L265:
    il = *n - k;
    if (il == 0) {
	return 0;
    }
/* ----------------------------------------------------------------------- */
/*     RECUR BACKWARD FOR REMAINDER OF I SEQUENCE AND ADD IN THE */
/*     K FUNCTIONS, SCALING THE I SEQUENCE DURING RECURRENCE TO KEEP */
/*     INTERMEDIATE ARITHMETIC ON SCALE NEAR EXPONENT EXTREMES. */
/* ----------------------------------------------------------------------- */
    s1.r = cy[0].r, s1.i = cy[0].i;
    s2.r = cy[1].r, s2.i = cy[1].i;
    i__1 = iflag - 1;
    cs.r = csr[i__1].r, cs.i = csr[i__1].i;
    ascle = bry[iflag - 1];
    fn = (real) (inu + il);
    i__1 = il;
    for (i__ = 1; i__ <= i__1; ++i__) {
	c2.r = s2.r, c2.i = s2.i;
	r__1 = fn + fnf;
	q__4.r = r__1, q__4.i = (float)0.;
	q__3.r = q__4.r * rz.r - q__4.i * rz.i, q__3.i = q__4.r * rz.i + 
		q__4.i * rz.r;
	q__2.r = q__3.r * s2.r - q__3.i * s2.i, q__2.i = q__3.r * s2.i + 
		q__3.i * s2.r;
	q__1.r = s1.r + q__2.r, q__1.i = s1.i + q__2.i;
	s2.r = q__1.r, s2.i = q__1.i;
	s1.r = c2.r, s1.i = c2.i;
	fn += (float)-1.;
	q__1.r = s2.r * cs.r - s2.i * cs.i, q__1.i = s2.r * cs.i + s2.i * 
		cs.r;
	c2.r = q__1.r, c2.i = q__1.i;
	ck.r = c2.r, ck.i = c2.i;
	i__2 = kk;
	c1.r = y[i__2].r, c1.i = y[i__2].i;
	if (*kode == 1) {
	    goto L270;
	}
	cs1s2_(&zr, &c1, &c2, &nw, &asc, alim, &iuf);
	*nz += nw;
L270:
	i__2 = kk;
	q__2.r = c1.r * cspn.r - c1.i * cspn.i, q__2.i = c1.r * cspn.i + c1.i 
		* cspn.r;
	q__1.r = q__2.r + c2.r, q__1.i = q__2.i + c2.i;
	y[i__2].r = q__1.r, y[i__2].i = q__1.i;
	--kk;
	q__1.r = -cspn.r, q__1.i = -cspn.i;
	cspn.r = q__1.r, cspn.i = q__1.i;
	if (iflag >= 3) {
	    goto L280;
	}
	c2r = ck.r;
	c2i = r_imag(&ck);
	c2r = dabs(c2r);
	c2i = dabs(c2i);
	c2m = dmax(c2r,c2i);
	if (c2m <= ascle) {
	    goto L280;
	}
	++iflag;
	ascle = bry[iflag - 1];
	q__1.r = s1.r * cs.r - s1.i * cs.i, q__1.i = s1.r * cs.i + s1.i * 
		cs.r;
	s1.r = q__1.r, s1.i = q__1.i;
	s2.r = ck.r, s2.i = ck.i;
	i__2 = iflag - 1;
	q__1.r = s1.r * css[i__2].r - s1.i * css[i__2].i, q__1.i = s1.r * css[
		i__2].i + s1.i * css[i__2].r;
	s1.r = q__1.r, s1.i = q__1.i;
	i__2 = iflag - 1;
	q__1.r = s2.r * css[i__2].r - s2.i * css[i__2].i, q__1.i = s2.r * css[
		i__2].i + s2.i * css[i__2].r;
	s2.r = q__1.r, s2.i = q__1.i;
	i__2 = iflag - 1;
	cs.r = csr[i__2].r, cs.i = csr[i__2].i;
L280:
	;
    }
    return 0;
L290:
    *nz = -1;
    return 0;
} /* cunk1_ */

#ifdef __cplusplus
	}
#endif
