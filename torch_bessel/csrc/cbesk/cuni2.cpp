/* fortran/cbesk/cuni2.f -- translated by f2c (version 20240504).
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
static integer c__0 = 0;
static integer c__2 = 2;
static complex c_b21 = {(float)2.,(float)0.};

/* Subroutine */ int cuni2_(complex *z__, real *fnu, integer *kode, integer *
	n, complex *y, integer *nz, integer *nlast, real *fnul, real *tol, 
	real *elim, real *alim)
{
    /* Initialized data */

    static complex czero = {(float)0.,(float)0.};
    static complex cone = {(float)1.,(float)0.};
    static complex ci = {(float)0.,(float)1.};
    static complex cip[4] = { {(float)1.,(float)0.},{(float)0.,(float)1.},{(
	    float)-1.,(float)0.},{(float)0.,(float)-1.} };
    static real hpi = (float)1.57079632679489662;
    static real aic = (float)1.265512123484645396;

    /* System generated locals */
    integer i__1, i__2, i__3;
    real r__1, r__2;
    complex q__1, q__2, q__3, q__4, q__5, q__6, q__7;

    /* Builtin functions */
    double r_imag(complex *), cos(doublereal), sin(doublereal);
    void r_cnjg(complex *, complex *), c_div(complex *, complex *, complex *);
    double c_abs(complex *), log(doublereal), exp(doublereal);

    /* Local variables */
    static integer i__, j, k;
    static complex c1, c2, s1, s2, ai;
    static integer nd;
    static real fn;
    static integer in;
    static real ay;
    static complex cy[2], zb;
    static integer nn, nw;
    static complex zn, rz;
    static real yy, c2i, c2m, c2r, rs1;
    static complex dai, cid;
    static real ang;
    static complex cfn;
    static real car;
    static integer nai;
    static complex arg, phi;
    static real sar;
    static complex csr[3], css[3];
    static integer nuf, inu;
    static complex zar;
    static real bry[3], aarg;
    static integer ndai;
    static real aphi;
    static complex cscl, crsc;
    static integer idum;
    static complex asum, bsum, zeta1, zeta2;
    static integer iflag;
    static real ascle;
    extern /* Subroutine */ int cuchk_(complex *, integer *, real *, real *), 
	    cunhj_(complex *, real *, integer *, real *, complex *, complex *,
	     complex *, complex *, complex *, complex *), cairy_(complex *, 
	    integer *, integer *, complex *, integer *, integer *), cuoik_(
	    complex *, real *, integer *, integer *, integer *, complex *, 
	    integer *, real *, real *, real *);
    extern doublereal r1mach_(integer *);

/* ***BEGIN PROLOGUE  CUNI2 */
/* ***REFER TO  CBESI,CBESK */

/*     CUNI2 COMPUTES I(FNU,Z) IN THE RIGHT HALF PLANE BY MEANS OF */
/*     UNIFORM ASYMPTOTIC EXPANSION FOR J(FNU,ZN) WHERE ZN IS Z*I */
/*     OR -Z*I AND ZN IS IN THE RIGHT HALF PLANE ALSO. */

/*     FNUL IS THE SMALLEST ORDER PERMITTED FOR THE ASYMPTOTIC */
/*     EXPANSION. NLAST=0 MEANS ALL OF THE Y VALUES WERE SET. */
/*     NLAST.NE.0 IS THE NUMBER LEFT TO BE COMPUTED BY ANOTHER */
/*     FORMULA FOR ORDERS FNU TO FNU+NLAST-1 BECAUSE FNU+NLAST-1.LT.FNUL. */
/*     Y(I)=CZERO FOR I=NLAST+1,N */

/* ***ROUTINES CALLED  CAIRY,CUCHK,CUNHJ,CUOIK,R1MACH */
/* ***END PROLOGUE  CUNI2 */
    /* Parameter adjustments */
    --y;

    /* Function Body */

    *nz = 0;
    nd = *n;
    *nlast = 0;
/* ----------------------------------------------------------------------- */
/*     COMPUTED VALUES WITH EXPONENTS BETWEEN ALIM AND ELIM IN MAG- */
/*     NITUDE ARE SCALED TO KEEP INTERMEDIATE ARITHMETIC ON SCALE, */
/*     EXP(ALIM)=EXP(ELIM)*TOL */
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
    yy = r_imag(z__);
/* ----------------------------------------------------------------------- */
/*     ZN IS IN THE RIGHT HALF PLANE AFTER ROTATION BY CI OR -CI */
/* ----------------------------------------------------------------------- */
    q__2.r = -z__->r, q__2.i = -z__->i;
    q__1.r = q__2.r * ci.r - q__2.i * ci.i, q__1.i = q__2.r * ci.i + q__2.i * 
	    ci.r;
    zn.r = q__1.r, zn.i = q__1.i;
    zb.r = z__->r, zb.i = z__->i;
    q__1.r = -ci.r, q__1.i = -ci.i;
    cid.r = q__1.r, cid.i = q__1.i;
    inu = (integer) (*fnu);
    ang = hpi * (*fnu - (real) inu);
    car = cos(ang);
    sar = sin(ang);
    q__1.r = car, q__1.i = sar;
    c2.r = q__1.r, c2.i = q__1.i;
    zar.r = c2.r, zar.i = c2.i;
    in = inu + *n - 1;
    in %= 4;
    i__1 = in;
    q__1.r = c2.r * cip[i__1].r - c2.i * cip[i__1].i, q__1.i = c2.r * cip[
	    i__1].i + c2.i * cip[i__1].r;
    c2.r = q__1.r, c2.i = q__1.i;
    if (yy > (float)0.) {
	goto L10;
    }
    q__2.r = -zn.r, q__2.i = -zn.i;
    r_cnjg(&q__1, &q__2);
    zn.r = q__1.r, zn.i = q__1.i;
    r_cnjg(&q__1, &zb);
    zb.r = q__1.r, zb.i = q__1.i;
    q__1.r = -cid.r, q__1.i = -cid.i;
    cid.r = q__1.r, cid.i = q__1.i;
    r_cnjg(&q__1, &c2);
    c2.r = q__1.r, c2.i = q__1.i;
L10:
/* ----------------------------------------------------------------------- */
/*     CHECK FOR UNDERFLOW AND OVERFLOW ON FIRST MEMBER */
/* ----------------------------------------------------------------------- */
    fn = dmax(*fnu,(float)1.);
    cunhj_(&zn, &fn, &c__1, tol, &phi, &arg, &zeta1, &zeta2, &asum, &bsum);
    if (*kode == 1) {
	goto L20;
    }
    q__1.r = *fnu, q__1.i = (float)0.;
    cfn.r = q__1.r, cfn.i = q__1.i;
    q__2.r = -zeta1.r, q__2.i = -zeta1.i;
    q__5.r = zb.r + zeta2.r, q__5.i = zb.i + zeta2.i;
    c_div(&q__4, &cfn, &q__5);
    q__3.r = cfn.r * q__4.r - cfn.i * q__4.i, q__3.i = cfn.r * q__4.i + cfn.i 
	    * q__4.r;
    q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
    s1.r = q__1.r, s1.i = q__1.i;
    goto L30;
L20:
    q__2.r = -zeta1.r, q__2.i = -zeta1.i;
    q__1.r = q__2.r + zeta2.r, q__1.i = q__2.i + zeta2.i;
    s1.r = q__1.r, s1.i = q__1.i;
L30:
    rs1 = s1.r;
    if (dabs(rs1) > *elim) {
	goto L150;
    }
L40:
    nn = min(2,nd);
    i__1 = nn;
    for (i__ = 1; i__ <= i__1; ++i__) {
	fn = *fnu + (real) (nd - i__);
	cunhj_(&zn, &fn, &c__0, tol, &phi, &arg, &zeta1, &zeta2, &asum, &bsum)
		;
	if (*kode == 1) {
	    goto L50;
	}
	q__1.r = fn, q__1.i = (float)0.;
	cfn.r = q__1.r, cfn.i = q__1.i;
	ay = dabs(yy);
	q__3.r = -zeta1.r, q__3.i = -zeta1.i;
	q__6.r = zb.r + zeta2.r, q__6.i = zb.i + zeta2.i;
	c_div(&q__5, &cfn, &q__6);
	q__4.r = cfn.r * q__5.r - cfn.i * q__5.i, q__4.i = cfn.r * q__5.i + 
		cfn.i * q__5.r;
	q__2.r = q__3.r + q__4.r, q__2.i = q__3.i + q__4.i;
	q__7.r = (float)0., q__7.i = ay;
	q__1.r = q__2.r + q__7.r, q__1.i = q__2.i + q__7.i;
	s1.r = q__1.r, s1.i = q__1.i;
	goto L60;
L50:
	q__2.r = -zeta1.r, q__2.i = -zeta1.i;
	q__1.r = q__2.r + zeta2.r, q__1.i = q__2.i + zeta2.i;
	s1.r = q__1.r, s1.i = q__1.i;
L60:
/* ----------------------------------------------------------------------- */
/*     TEST FOR UNDERFLOW AND OVERFLOW */
/* ----------------------------------------------------------------------- */
	rs1 = s1.r;
	if (dabs(rs1) > *elim) {
	    goto L120;
	}
	if (i__ == 1) {
	    iflag = 2;
	}
	if (dabs(rs1) < *alim) {
	    goto L70;
	}
/* ----------------------------------------------------------------------- */
/*     REFINE  TEST AND SCALE */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
	aphi = c_abs(&phi);
	aarg = c_abs(&arg);
	rs1 = rs1 + log(aphi) - log(aarg) * (float).25 - aic;
	if (dabs(rs1) > *elim) {
	    goto L120;
	}
	if (i__ == 1) {
	    iflag = 1;
	}
	if (rs1 < (float)0.) {
	    goto L70;
	}
	if (i__ == 1) {
	    iflag = 3;
	}
L70:
/* ----------------------------------------------------------------------- */
/*     SCALE S1 TO KEEP INTERMEDIATE ARITHMETIC ON SCALE NEAR */
/*     EXPONENT EXTREMES */
/* ----------------------------------------------------------------------- */
	cairy_(&arg, &c__0, &c__2, &ai, &nai, &idum);
	cairy_(&arg, &c__1, &c__2, &dai, &ndai, &idum);
	q__3.r = ai.r * asum.r - ai.i * asum.i, q__3.i = ai.r * asum.i + ai.i 
		* asum.r;
	q__4.r = dai.r * bsum.r - dai.i * bsum.i, q__4.i = dai.r * bsum.i + 
		dai.i * bsum.r;
	q__2.r = q__3.r + q__4.r, q__2.i = q__3.i + q__4.i;
	q__1.r = phi.r * q__2.r - phi.i * q__2.i, q__1.i = phi.r * q__2.i + 
		phi.i * q__2.r;
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
	    goto L80;
	}
	cuchk_(&s2, &nw, bry, tol);
	if (nw != 0) {
	    goto L120;
	}
L80:
	if (yy <= (float)0.) {
	    r_cnjg(&q__1, &s2);
	    s2.r = q__1.r, s2.i = q__1.i;
	}
	j = nd - i__ + 1;
	q__1.r = s2.r * c2.r - s2.i * c2.i, q__1.i = s2.r * c2.i + s2.i * 
		c2.r;
	s2.r = q__1.r, s2.i = q__1.i;
	i__2 = i__ - 1;
	cy[i__2].r = s2.r, cy[i__2].i = s2.i;
	i__2 = j;
	i__3 = iflag - 1;
	q__1.r = s2.r * csr[i__3].r - s2.i * csr[i__3].i, q__1.i = s2.r * csr[
		i__3].i + s2.i * csr[i__3].r;
	y[i__2].r = q__1.r, y[i__2].i = q__1.i;
	q__1.r = c2.r * cid.r - c2.i * cid.i, q__1.i = c2.r * cid.i + c2.i * 
		cid.r;
	c2.r = q__1.r, c2.i = q__1.i;
/* L90: */
    }
    if (nd <= 2) {
	goto L110;
    }
    c_div(&q__1, &c_b21, z__);
    rz.r = q__1.r, rz.i = q__1.i;
    bry[1] = (float)1. / bry[0];
    bry[2] = r1mach_(&c__2);
    s1.r = cy[0].r, s1.i = cy[0].i;
    s2.r = cy[1].r, s2.i = cy[1].i;
    i__1 = iflag - 1;
    c1.r = csr[i__1].r, c1.i = csr[i__1].i;
    ascle = bry[iflag - 1];
    k = nd - 2;
    fn = (real) k;
    i__1 = nd;
    for (i__ = 3; i__ <= i__1; ++i__) {
	c2.r = s2.r, c2.i = s2.i;
	r__1 = *fnu + fn;
	q__4.r = r__1, q__4.i = (float)0.;
	q__3.r = q__4.r * rz.r - q__4.i * rz.i, q__3.i = q__4.r * rz.i + 
		q__4.i * rz.r;
	q__2.r = q__3.r * s2.r - q__3.i * s2.i, q__2.i = q__3.r * s2.i + 
		q__3.i * s2.r;
	q__1.r = s1.r + q__2.r, q__1.i = s1.i + q__2.i;
	s2.r = q__1.r, s2.i = q__1.i;
	s1.r = c2.r, s1.i = c2.i;
	q__1.r = s2.r * c1.r - s2.i * c1.i, q__1.i = s2.r * c1.i + s2.i * 
		c1.r;
	c2.r = q__1.r, c2.i = q__1.i;
	i__2 = k;
	y[i__2].r = c2.r, y[i__2].i = c2.i;
	--k;
	fn += (float)-1.;
	if (iflag >= 3) {
	    goto L100;
	}
	c2r = c2.r;
	c2i = r_imag(&c2);
	c2r = dabs(c2r);
	c2i = dabs(c2i);
	c2m = dmax(c2r,c2i);
	if (c2m <= ascle) {
	    goto L100;
	}
	++iflag;
	ascle = bry[iflag - 1];
	q__1.r = s1.r * c1.r - s1.i * c1.i, q__1.i = s1.r * c1.i + s1.i * 
		c1.r;
	s1.r = q__1.r, s1.i = q__1.i;
	s2.r = c2.r, s2.i = c2.i;
	i__2 = iflag - 1;
	q__1.r = s1.r * css[i__2].r - s1.i * css[i__2].i, q__1.i = s1.r * css[
		i__2].i + s1.i * css[i__2].r;
	s1.r = q__1.r, s1.i = q__1.i;
	i__2 = iflag - 1;
	q__1.r = s2.r * css[i__2].r - s2.i * css[i__2].i, q__1.i = s2.r * css[
		i__2].i + s2.i * css[i__2].r;
	s2.r = q__1.r, s2.i = q__1.i;
	i__2 = iflag - 1;
	c1.r = csr[i__2].r, c1.i = csr[i__2].i;
L100:
	;
    }
L110:
    return 0;
L120:
    if (rs1 > (float)0.) {
	goto L140;
    }
/* ----------------------------------------------------------------------- */
/*     SET UNDERFLOW AND UPDATE PARAMETERS */
/* ----------------------------------------------------------------------- */
    i__1 = nd;
    y[i__1].r = czero.r, y[i__1].i = czero.i;
    ++(*nz);
    --nd;
    if (nd == 0) {
	goto L110;
    }
    cuoik_(z__, fnu, kode, &c__1, &nd, &y[1], &nuf, tol, elim, alim);
    if (nuf < 0) {
	goto L140;
    }
    nd -= nuf;
    *nz += nuf;
    if (nd == 0) {
	goto L110;
    }
    fn = *fnu + (real) (nd - 1);
    if (fn < *fnul) {
	goto L130;
    }
/*      FN = AIMAG(CID) */
/*      J = NUF + 1 */
/*      K = MOD(J,4) + 1 */
/*      S1 = CIP(K) */
/*      IF (FN.LT.0.0E0) S1 = CONJG(S1) */
/*      C2 = C2*S1 */
    in = inu + nd - 1;
    in = in % 4 + 1;
    i__1 = in - 1;
    q__1.r = zar.r * cip[i__1].r - zar.i * cip[i__1].i, q__1.i = zar.r * cip[
	    i__1].i + zar.i * cip[i__1].r;
    c2.r = q__1.r, c2.i = q__1.i;
    if (yy <= (float)0.) {
	r_cnjg(&q__1, &c2);
	c2.r = q__1.r, c2.i = q__1.i;
    }
    goto L40;
L130:
    *nlast = nd;
    return 0;
L140:
    *nz = -1;
    return 0;
L150:
    if (rs1 > (float)0.) {
	goto L140;
    }
    *nz = *n;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	y[i__2].r = czero.r, y[i__2].i = czero.i;
/* L160: */
    }
    return 0;
} /* cuni2_ */

#ifdef __cplusplus
	}
#endif
