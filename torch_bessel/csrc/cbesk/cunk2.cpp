/* fortran/cbesk/cunk2.f -- translated by f2c (version 20240504).
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
static complex c_b18 = {(float)2.,(float)0.};

/* Subroutine */ int cunk2_(complex *z__, real *fnu, integer *kode, integer *
	mr, integer *n, complex *y, integer *nz, real *tol, real *elim, real *
	alim)
{
    /* Initialized data */

    static complex czero = {(float)0.,(float)0.};
    static complex cone = {(float)1.,(float)0.};
    static complex ci = {(float)0.,(float)1.};
    static complex cr1 = {(float)1.,(float)1.73205080756887729};
    static complex cr2 = {(float)-.5,(float)-.866025403784438647};
    static real hpi = (float)1.57079632679489662;
    static real pi = (float)3.14159265358979324;
    static real aic = (float)1.26551212348464539;
    static complex cip[4] = { {(float)1.,(float)0.},{(float)0.,(float)-1.},{(
	    float)-1.,(float)0.},{(float)0.,(float)1.} };

    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    real r__1, r__2;
    complex q__1, q__2, q__3, q__4, q__5, q__6;

    /* Builtin functions */
    double r_imag(complex *), cos(doublereal), sin(doublereal);
    void r_cnjg(complex *, complex *), c_div(complex *, complex *, complex *);
    double c_abs(complex *), log(doublereal), exp(doublereal), r_sign(real *, 
	    real *);

    /* Local variables */
    static integer i__, j, k;
    static real x;
    static complex c1, c2, s1, s2, ai;
    static integer ib, ic;
    static complex ck;
    static real fn;
    static integer il;
    static complex cs;
    static integer in, kk;
    static complex cy[2], zb;
    static integer nw;
    static complex zn, rz, zr;
    static real yy, c2i, c2m, c2r, rs1;
    static complex dai;
    static real ang;
    static complex cfn;
    static real asc, car;
    static complex arg[2];
    static real fnf;
    static integer ifn, nai;
    static complex phi[2];
    static real cpn;
    static integer iuf;
    static real fmr, sar;
    static complex csr[3], css[3];
    static real sgn;
    static integer inu;
    static real bry[3], spn, aarg;
    static integer ndai;
    static complex argd;
    static real aphi;
    static complex cscl, phid, crsc, csgn;
    extern /* Subroutine */ int cs1s2_(complex *, complex *, complex *, 
	    integer *, real *, real *, integer *);
    static integer idum;
    static complex cspn, asum[2], bsum[2], zeta1[2], zeta2[2];
    static integer iflag, kflag;
    static real ascle;
    static integer kdflg;
    extern /* Subroutine */ int cuchk_(complex *, integer *, real *, real *);
    static integer ipard;
    extern /* Subroutine */ int cunhj_(complex *, real *, integer *, real *, 
	    complex *, complex *, complex *, complex *, complex *, complex *),
	     cairy_(complex *, integer *, integer *, complex *, integer *, 
	    integer *);
    static complex asumd, bsumd;
    extern doublereal r1mach_(integer *);
    static complex zeta1d, zeta2d;

/* ***BEGIN PROLOGUE  CUNK2 */
/* ***REFER TO  CBESK */

/*     CUNK2 COMPUTES K(FNU,Z) AND ITS ANALYTIC CONTINUATION FROM THE */
/*     RIGHT HALF PLANE TO THE LEFT HALF PLANE BY MEANS OF THE */
/*     UNIFORM ASYMPTOTIC EXPANSIONS FOR H(KIND,FNU,ZN) AND J(FNU,ZN) */
/*     WHERE ZN IS IN THE RIGHT HALF PLANE, KIND=(3-MR)/2, MR=+1 OR */
/*     -1. HERE ZN=ZR*I OR -ZR*I WHERE ZR=Z IF Z IS IN THE RIGHT */
/*     HALF PLANE OR ZR=-Z IF Z IS IN THE LEFT HALF PLANE. MR INDIC- */
/*     ATES THE DIRECTION OF ROTATION FOR ANALYTIC CONTINUATION. */
/*     NZ=-1 MEANS AN OVERFLOW WILL OCCUR */

/* ***ROUTINES CALLED  CAIRY,CS1S2,CUCHK,CUNHJ,R1MACH */
/* ***END PROLOGUE  CUNK2 */
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
    yy = r_imag(&zr);
    q__2.r = -zr.r, q__2.i = -zr.i;
    q__1.r = q__2.r * ci.r - q__2.i * ci.i, q__1.i = q__2.r * ci.i + q__2.i * 
	    ci.r;
    zn.r = q__1.r, zn.i = q__1.i;
    zb.r = zr.r, zb.i = zr.i;
    inu = (integer) (*fnu);
    fnf = *fnu - (real) inu;
    ang = -hpi * fnf;
    car = cos(ang);
    sar = sin(ang);
    cpn = -hpi * car;
    spn = -hpi * sar;
    r__1 = -spn;
    q__1.r = r__1, q__1.i = cpn;
    c2.r = q__1.r, c2.i = q__1.i;
    kk = inu % 4 + 1;
    q__2.r = cr1.r * c2.r - cr1.i * c2.i, q__2.i = cr1.r * c2.i + cr1.i * 
	    c2.r;
    i__1 = kk - 1;
    q__1.r = q__2.r * cip[i__1].r - q__2.i * cip[i__1].i, q__1.i = q__2.r * 
	    cip[i__1].i + q__2.i * cip[i__1].r;
    cs.r = q__1.r, cs.i = q__1.i;
    if (yy > (float)0.) {
	goto L10;
    }
    q__2.r = -zn.r, q__2.i = -zn.i;
    r_cnjg(&q__1, &q__2);
    zn.r = q__1.r, zn.i = q__1.i;
    r_cnjg(&q__1, &zb);
    zb.r = q__1.r, zb.i = q__1.i;
L10:
/* ----------------------------------------------------------------------- */
/*     K(FNU,Z) IS COMPUTED FROM H(2,FNU,-I*Z) WHERE Z IS IN THE FIRST */
/*     QUADRANT. FOURTH QUADRANT VALUES (YY.LE.0.0E0) ARE COMPUTED BY */
/*     CONJUGATION SINCE THE K FUNCTION IS REAL ON THE POSITIVE REAL AXIS */
/* ----------------------------------------------------------------------- */
    j = 2;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* ----------------------------------------------------------------------- */
/*     J FLIP FLOPS BETWEEN 1 AND 2 IN J = 3 - J */
/* ----------------------------------------------------------------------- */
	j = 3 - j;
	fn = *fnu + (real) (i__ - 1);
	cunhj_(&zn, &fn, &c__0, tol, &phi[j - 1], &arg[j - 1], &zeta1[j - 1], 
		&zeta2[j - 1], &asum[j - 1], &bsum[j - 1]);
	if (*kode == 1) {
	    goto L20;
	}
	q__1.r = fn, q__1.i = (float)0.;
	cfn.r = q__1.r, cfn.i = q__1.i;
	i__2 = j - 1;
	i__3 = j - 1;
	q__4.r = zb.r + zeta2[i__3].r, q__4.i = zb.i + zeta2[i__3].i;
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
	aarg = c_abs(&arg[j - 1]);
	rs1 = rs1 + log(aphi) - log(aarg) * (float).25 - aic;
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
	q__1.r = arg[i__2].r * cr2.r - arg[i__2].i * cr2.i, q__1.i = arg[i__2]
		.r * cr2.i + arg[i__2].i * cr2.r;
	c2.r = q__1.r, c2.i = q__1.i;
	cairy_(&c2, &c__0, &c__2, &ai, &nai, &idum);
	cairy_(&c2, &c__1, &c__2, &dai, &ndai, &idum);
	i__2 = j - 1;
	q__2.r = cs.r * phi[i__2].r - cs.i * phi[i__2].i, q__2.i = cs.r * phi[
		i__2].i + cs.i * phi[i__2].r;
	i__3 = j - 1;
	q__4.r = ai.r * asum[i__3].r - ai.i * asum[i__3].i, q__4.i = ai.r * 
		asum[i__3].i + ai.i * asum[i__3].r;
	q__6.r = cr2.r * dai.r - cr2.i * dai.i, q__6.i = cr2.r * dai.i + 
		cr2.i * dai.r;
	i__4 = j - 1;
	q__5.r = q__6.r * bsum[i__4].r - q__6.i * bsum[i__4].i, q__5.i = 
		q__6.r * bsum[i__4].i + q__6.i * bsum[i__4].r;
	q__3.r = q__4.r + q__5.r, q__3.i = q__4.i + q__5.i;
	q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i 
		+ q__2.i * q__3.r;
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
	if (yy <= (float)0.) {
	    r_cnjg(&q__1, &s2);
	    s2.r = q__1.r, s2.i = q__1.i;
	}
	i__2 = kdflg - 1;
	cy[i__2].r = s2.r, cy[i__2].i = s2.i;
	i__2 = i__;
	i__3 = kflag - 1;
	q__1.r = s2.r * csr[i__3].r - s2.i * csr[i__3].i, q__1.i = s2.r * csr[
		i__3].i + s2.i * csr[i__3].r;
	y[i__2].r = q__1.r, y[i__2].i = q__1.i;
	q__2.r = -ci.r, q__2.i = -ci.i;
	q__1.r = q__2.r * cs.r - q__2.i * cs.i, q__1.i = q__2.r * cs.i + 
		q__2.i * cs.r;
	cs.r = q__1.r, cs.i = q__1.i;
	if (kdflg == 2) {
	    goto L75;
	}
	kdflg = 2;
	goto L70;
L60:
	if (rs1 > (float)0.) {
	    goto L300;
	}
/* ----------------------------------------------------------------------- */
/*     FOR X.LT.0.0, THE I FUNCTION TO BE ADDED WILL OVERFLOW */
/* ----------------------------------------------------------------------- */
	if (x < (float)0.) {
	    goto L300;
	}
	kdflg = 1;
	i__2 = i__;
	y[i__2].r = czero.r, y[i__2].i = czero.i;
	q__2.r = -ci.r, q__2.i = -ci.i;
	q__1.r = q__2.r * cs.r - q__2.i * cs.i, q__1.i = q__2.r * cs.i + 
		q__2.i * cs.r;
	cs.r = q__1.r, cs.i = q__1.i;
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
    c_div(&q__1, &c_b18, &zr);
    rz.r = q__1.r, rz.i = q__1.i;
    q__2.r = fn, q__2.i = (float)0.;
    q__1.r = q__2.r * rz.r - q__2.i * rz.i, q__1.i = q__2.r * rz.i + q__2.i * 
	    rz.r;
    ck.r = q__1.r, ck.i = q__1.i;
    ib = i__ + 1;
    if (*n < ib) {
	goto L170;
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
    cunhj_(&zn, &fn, &ipard, tol, &phid, &argd, &zeta1d, &zeta2d, &asumd, &
	    bsumd);
    if (*kode == 1) {
	goto L80;
    }
    q__1.r = fn, q__1.i = (float)0.;
    cfn.r = q__1.r, cfn.i = q__1.i;
    q__4.r = zb.r + zeta2d.r, q__4.i = zb.i + zeta2d.i;
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
    aarg = c_abs(&argd);
    rs1 = rs1 + log(aphi) - log(aarg) * (float).25 - aic;
    if (dabs(rs1) < *elim) {
	goto L100;
    }
L95:
    if (rs1 > (float)0.) {
	goto L300;
    }
/* ----------------------------------------------------------------------- */
/*     FOR X.LT.0.0, THE I FUNCTION TO BE ADDED WILL OVERFLOW */
/* ----------------------------------------------------------------------- */
    if (x < (float)0.) {
	goto L300;
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
/*     SCALED FORWARD RECURRENCE FOR REMAINDER OF THE SEQUENCE */
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
L170:
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
/*     CSPN AND CSGN ARE COEFF OF K AND I FUNCTIONS RESP. */
/* ----------------------------------------------------------------------- */
    q__1.r = (float)0., q__1.i = sgn;
    csgn.r = q__1.r, csgn.i = q__1.i;
    if (yy <= (float)0.) {
	r_cnjg(&q__1, &csgn);
	csgn.r = q__1.r, csgn.i = q__1.i;
    }
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
/* ----------------------------------------------------------------------- */
/*     CS=COEFF OF THE J FUNCTION TO GET THE I FUNCTION. I(FNU,Z) IS */
/*     COMPUTED FROM EXP(I*FNU*HPI)*J(FNU,-I*Z) WHERE Z IS IN THE FIRST */
/*     QUADRANT. FOURTH QUADRANT VALUES (YY.LE.0.0E0) ARE COMPUTED BY */
/*     CONJUGATION SINCE THE I FUNCTION IS REAL ON THE POSITIVE REAL AXIS */
/* ----------------------------------------------------------------------- */
    r__1 = -sar;
    q__2.r = car, q__2.i = r__1;
    q__1.r = q__2.r * csgn.r - q__2.i * csgn.i, q__1.i = q__2.r * csgn.i + 
	    q__2.i * csgn.r;
    cs.r = q__1.r, cs.i = q__1.i;
    in = ifn % 4 + 1;
    i__1 = in - 1;
    c2.r = cip[i__1].r, c2.i = cip[i__1].i;
    r_cnjg(&q__2, &c2);
    q__1.r = cs.r * q__2.r - cs.i * q__2.i, q__1.i = cs.r * q__2.i + cs.i * 
	    q__2.r;
    cs.r = q__1.r, cs.i = q__1.i;
    asc = bry[0];
    kk = *n;
    kdflg = 1;
    --ib;
    ic = ib - 1;
    iuf = 0;
    i__1 = *n;
    for (k = 1; k <= i__1; ++k) {
/* ----------------------------------------------------------------------- */
/*     LOGIC TO SORT OUT CASES WHOSE PARAMETERS WERE SET FOR THE K */
/*     FUNCTION ABOVE */
/* ----------------------------------------------------------------------- */
	fn = *fnu + (real) (kk - 1);
	if (*n > 2) {
	    goto L180;
	}
L175:
	i__2 = j - 1;
	phid.r = phi[i__2].r, phid.i = phi[i__2].i;
	i__2 = j - 1;
	argd.r = arg[i__2].r, argd.i = arg[i__2].i;
	i__2 = j - 1;
	zeta1d.r = zeta1[i__2].r, zeta1d.i = zeta1[i__2].i;
	i__2 = j - 1;
	zeta2d.r = zeta2[i__2].r, zeta2d.i = zeta2[i__2].i;
	i__2 = j - 1;
	asumd.r = asum[i__2].r, asumd.i = asum[i__2].i;
	i__2 = j - 1;
	bsumd.r = bsum[i__2].r, bsumd.i = bsum[i__2].i;
	j = 3 - j;
	goto L190;
L180:
	if (kk == *n && ib < *n) {
	    goto L190;
	}
	if (kk == ib || kk == ic) {
	    goto L175;
	}
	cunhj_(&zn, &fn, &c__0, tol, &phid, &argd, &zeta1d, &zeta2d, &asumd, &
		bsumd);
L190:
	if (*kode == 1) {
	    goto L200;
	}
	q__1.r = fn, q__1.i = (float)0.;
	cfn.r = q__1.r, cfn.i = q__1.i;
	q__2.r = -zeta1d.r, q__2.i = -zeta1d.i;
	q__5.r = zb.r + zeta2d.r, q__5.i = zb.i + zeta2d.i;
	c_div(&q__4, &cfn, &q__5);
	q__3.r = cfn.r * q__4.r - cfn.i * q__4.i, q__3.i = cfn.r * q__4.i + 
		cfn.i * q__4.r;
	q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
	s1.r = q__1.r, s1.i = q__1.i;
	goto L210;
L200:
	q__2.r = -zeta1d.r, q__2.i = -zeta1d.i;
	q__1.r = q__2.r + zeta2d.r, q__1.i = q__2.i + zeta2d.i;
	s1.r = q__1.r, s1.i = q__1.i;
L210:
/* ----------------------------------------------------------------------- */
/*     TEST FOR UNDERFLOW AND OVERFLOW */
/* ----------------------------------------------------------------------- */
	rs1 = s1.r;
	if (dabs(rs1) > *elim) {
	    goto L260;
	}
	if (kdflg == 1) {
	    iflag = 2;
	}
	if (dabs(rs1) < *alim) {
	    goto L220;
	}
/* ----------------------------------------------------------------------- */
/*     REFINE  TEST AND SCALE */
/* ----------------------------------------------------------------------- */
	aphi = c_abs(&phid);
	aarg = c_abs(&argd);
	rs1 = rs1 + log(aphi) - log(aarg) * (float).25 - aic;
	if (dabs(rs1) > *elim) {
	    goto L260;
	}
	if (kdflg == 1) {
	    iflag = 1;
	}
	if (rs1 < (float)0.) {
	    goto L220;
	}
	if (kdflg == 1) {
	    iflag = 3;
	}
L220:
	cairy_(&argd, &c__0, &c__2, &ai, &nai, &idum);
	cairy_(&argd, &c__1, &c__2, &dai, &ndai, &idum);
	q__2.r = cs.r * phid.r - cs.i * phid.i, q__2.i = cs.r * phid.i + cs.i 
		* phid.r;
	q__4.r = ai.r * asumd.r - ai.i * asumd.i, q__4.i = ai.r * asumd.i + 
		ai.i * asumd.r;
	q__5.r = dai.r * bsumd.r - dai.i * bsumd.i, q__5.i = dai.r * bsumd.i 
		+ dai.i * bsumd.r;
	q__3.r = q__4.r + q__5.r, q__3.i = q__4.i + q__5.i;
	q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i 
		+ q__2.i * q__3.r;
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
	    goto L230;
	}
	cuchk_(&s2, &nw, bry, tol);
	if (nw != 0) {
	    s2.r = (float)0., s2.i = (float)0.;
	}
L230:
	if (yy <= (float)0.) {
	    r_cnjg(&q__1, &s2);
	    s2.r = q__1.r, s2.i = q__1.i;
	}
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
	    goto L250;
	}
	cs1s2_(&zr, &s1, &s2, &nw, &asc, alim, &iuf);
	*nz += nw;
L250:
	i__2 = kk;
	q__2.r = s1.r * cspn.r - s1.i * cspn.i, q__2.i = s1.r * cspn.i + s1.i 
		* cspn.r;
	q__1.r = q__2.r + s2.r, q__1.i = q__2.i + s2.i;
	y[i__2].r = q__1.r, y[i__2].i = q__1.i;
	--kk;
	q__1.r = -cspn.r, q__1.i = -cspn.i;
	cspn.r = q__1.r, cspn.i = q__1.i;
	q__2.r = -cs.r, q__2.i = -cs.i;
	q__1.r = q__2.r * ci.r - q__2.i * ci.i, q__1.i = q__2.r * ci.i + 
		q__2.i * ci.r;
	cs.r = q__1.r, cs.i = q__1.i;
	if (c2.r != czero.r || c2.i != czero.i) {
	    goto L255;
	}
	kdflg = 1;
	goto L270;
L255:
	if (kdflg == 2) {
	    goto L275;
	}
	kdflg = 2;
	goto L270;
L260:
	if (rs1 > (float)0.) {
	    goto L300;
	}
	s2.r = czero.r, s2.i = czero.i;
	goto L230;
L270:
	;
    }
    k = *n;
L275:
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
	    goto L280;
	}
	cs1s2_(&zr, &c1, &c2, &nw, &asc, alim, &iuf);
	*nz += nw;
L280:
	i__2 = kk;
	q__2.r = c1.r * cspn.r - c1.i * cspn.i, q__2.i = c1.r * cspn.i + c1.i 
		* cspn.r;
	q__1.r = q__2.r + c2.r, q__1.i = q__2.i + c2.i;
	y[i__2].r = q__1.r, y[i__2].i = q__1.i;
	--kk;
	q__1.r = -cspn.r, q__1.i = -cspn.i;
	cspn.r = q__1.r, cspn.i = q__1.i;
	if (iflag >= 3) {
	    goto L290;
	}
	c2r = ck.r;
	c2i = r_imag(&ck);
	c2r = dabs(c2r);
	c2i = dabs(c2i);
	c2m = dmax(c2r,c2i);
	if (c2m <= ascle) {
	    goto L290;
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
L290:
	;
    }
    return 0;
L300:
    *nz = -1;
    return 0;
} /* cunk2_ */

#ifdef __cplusplus
	}
#endif
