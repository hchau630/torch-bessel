/* fortran/cbesk/cuni1.f -- translated by f2c (version 20240504).
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
static complex c_b18 = {(float)2.,(float)0.};
static integer c__2 = 2;

/* Subroutine */ int cuni1_(complex *z__, real *fnu, integer *kode, integer *
	n, complex *y, integer *nz, integer *nlast, real *fnul, real *tol, 
	real *elim, real *alim)
{
    /* Initialized data */

    static complex czero = {(float)0.,(float)0.};
    static complex cone = {(float)1.,(float)0.};

    /* System generated locals */
    integer i__1, i__2, i__3;
    real r__1, r__2;
    complex q__1, q__2, q__3, q__4, q__5, q__6, q__7;

    /* Builtin functions */
    void c_div(complex *, complex *, complex *);
    double r_imag(complex *), c_abs(complex *), log(doublereal), exp(
	    doublereal), cos(doublereal), sin(doublereal);

    /* Local variables */
    static integer i__, k, m;
    static complex c1, c2, s1, s2;
    static integer nd;
    static real fn;
    static complex cy[2];
    static integer nn, nw;
    static complex rz;
    static real yy, c2i, c2m, c2r, rs1;
    static complex cfn, phi, csr[3], css[3];
    static integer nuf;
    static real bry[3];
    static complex sum;
    static real aphi;
    static complex cscl, crsc;
    static integer init;
    static complex cwrk[16], zeta1, zeta2;
    static integer iflag;
    static real ascle;
    extern /* Subroutine */ int cuchk_(complex *, integer *, real *, real *), 
	    cunik_(complex *, real *, integer *, integer *, real *, integer *,
	     complex *, complex *, complex *, complex *, complex *), cuoik_(
	    complex *, real *, integer *, integer *, integer *, complex *, 
	    integer *, real *, real *, real *);
    extern doublereal r1mach_(integer *);

/* ***BEGIN PROLOGUE  CUNI1 */
/* ***REFER TO  CBESI,CBESK */

/*     CUNI1 COMPUTES I(FNU,Z)  BY MEANS OF THE UNIFORM ASYMPTOTIC */
/*     EXPANSION FOR I(FNU,Z) IN -PI/3.LE.ARG Z.LE.PI/3. */

/*     FNUL IS THE SMALLEST ORDER PERMITTED FOR THE ASYMPTOTIC */
/*     EXPANSION. NLAST=0 MEANS ALL OF THE Y VALUES WERE SET. */
/*     NLAST.NE.0 IS THE NUMBER LEFT TO BE COMPUTED BY ANOTHER */
/*     FORMULA FOR ORDERS FNU TO FNU+NLAST-1 BECAUSE FNU+NLAST-1.LT.FNUL. */
/*     Y(I)=CZERO FOR I=NLAST+1,N */

/* ***ROUTINES CALLED  CUCHK,CUNIK,CUOIK,R1MACH */
/* ***END PROLOGUE  CUNI1 */
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
/* ----------------------------------------------------------------------- */
/*     CHECK FOR UNDERFLOW AND OVERFLOW ON FIRST MEMBER */
/* ----------------------------------------------------------------------- */
    fn = dmax(*fnu,(float)1.);
    init = 0;
    cunik_(z__, &fn, &c__1, &c__1, tol, &init, &phi, &zeta1, &zeta2, &sum, 
	    cwrk);
    if (*kode == 1) {
	goto L10;
    }
    q__1.r = fn, q__1.i = (float)0.;
    cfn.r = q__1.r, cfn.i = q__1.i;
    q__2.r = -zeta1.r, q__2.i = -zeta1.i;
    q__5.r = z__->r + zeta2.r, q__5.i = z__->i + zeta2.i;
    c_div(&q__4, &cfn, &q__5);
    q__3.r = cfn.r * q__4.r - cfn.i * q__4.i, q__3.i = cfn.r * q__4.i + cfn.i 
	    * q__4.r;
    q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
    s1.r = q__1.r, s1.i = q__1.i;
    goto L20;
L10:
    q__2.r = -zeta1.r, q__2.i = -zeta1.i;
    q__1.r = q__2.r + zeta2.r, q__1.i = q__2.i + zeta2.i;
    s1.r = q__1.r, s1.i = q__1.i;
L20:
    rs1 = s1.r;
    if (dabs(rs1) > *elim) {
	goto L130;
    }
L30:
    nn = min(2,nd);
    i__1 = nn;
    for (i__ = 1; i__ <= i__1; ++i__) {
	fn = *fnu + (real) (nd - i__);
	init = 0;
	cunik_(z__, &fn, &c__1, &c__0, tol, &init, &phi, &zeta1, &zeta2, &sum,
		 cwrk);
	if (*kode == 1) {
	    goto L40;
	}
	q__1.r = fn, q__1.i = (float)0.;
	cfn.r = q__1.r, cfn.i = q__1.i;
	yy = r_imag(z__);
	q__3.r = -zeta1.r, q__3.i = -zeta1.i;
	q__6.r = z__->r + zeta2.r, q__6.i = z__->i + zeta2.i;
	c_div(&q__5, &cfn, &q__6);
	q__4.r = cfn.r * q__5.r - cfn.i * q__5.i, q__4.i = cfn.r * q__5.i + 
		cfn.i * q__5.r;
	q__2.r = q__3.r + q__4.r, q__2.i = q__3.i + q__4.i;
	q__7.r = (float)0., q__7.i = yy;
	q__1.r = q__2.r + q__7.r, q__1.i = q__2.i + q__7.i;
	s1.r = q__1.r, s1.i = q__1.i;
	goto L50;
L40:
	q__2.r = -zeta1.r, q__2.i = -zeta1.i;
	q__1.r = q__2.r + zeta2.r, q__1.i = q__2.i + zeta2.i;
	s1.r = q__1.r, s1.i = q__1.i;
L50:
/* ----------------------------------------------------------------------- */
/*     TEST FOR UNDERFLOW AND OVERFLOW */
/* ----------------------------------------------------------------------- */
	rs1 = s1.r;
	if (dabs(rs1) > *elim) {
	    goto L110;
	}
	if (i__ == 1) {
	    iflag = 2;
	}
	if (dabs(rs1) < *alim) {
	    goto L60;
	}
/* ----------------------------------------------------------------------- */
/*     REFINE  TEST AND SCALE */
/* ----------------------------------------------------------------------- */
	aphi = c_abs(&phi);
	rs1 += log(aphi);
	if (dabs(rs1) > *elim) {
	    goto L110;
	}
	if (i__ == 1) {
	    iflag = 1;
	}
	if (rs1 < (float)0.) {
	    goto L60;
	}
	if (i__ == 1) {
	    iflag = 3;
	}
L60:
/* ----------------------------------------------------------------------- */
/*     SCALE S1 IF CABS(S1).LT.ASCLE */
/* ----------------------------------------------------------------------- */
	q__1.r = phi.r * sum.r - phi.i * sum.i, q__1.i = phi.r * sum.i + 
		phi.i * sum.r;
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
	    goto L70;
	}
	cuchk_(&s2, &nw, bry, tol);
	if (nw != 0) {
	    goto L110;
	}
L70:
	m = nd - i__ + 1;
	i__2 = i__ - 1;
	cy[i__2].r = s2.r, cy[i__2].i = s2.i;
	i__2 = m;
	i__3 = iflag - 1;
	q__1.r = s2.r * csr[i__3].r - s2.i * csr[i__3].i, q__1.i = s2.r * csr[
		i__3].i + s2.i * csr[i__3].r;
	y[i__2].r = q__1.r, y[i__2].i = q__1.i;
/* L80: */
    }
    if (nd <= 2) {
	goto L100;
    }
    c_div(&q__1, &c_b18, z__);
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
	    goto L90;
	}
	c2r = c2.r;
	c2i = r_imag(&c2);
	c2r = dabs(c2r);
	c2i = dabs(c2i);
	c2m = dmax(c2r,c2i);
	if (c2m <= ascle) {
	    goto L90;
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
L90:
	;
    }
L100:
    return 0;
/* ----------------------------------------------------------------------- */
/*     SET UNDERFLOW AND UPDATE PARAMETERS */
/* ----------------------------------------------------------------------- */
L110:
    if (rs1 > (float)0.) {
	goto L120;
    }
    i__1 = nd;
    y[i__1].r = czero.r, y[i__1].i = czero.i;
    ++(*nz);
    --nd;
    if (nd == 0) {
	goto L100;
    }
    cuoik_(z__, fnu, kode, &c__1, &nd, &y[1], &nuf, tol, elim, alim);
    if (nuf < 0) {
	goto L120;
    }
    nd -= nuf;
    *nz += nuf;
    if (nd == 0) {
	goto L100;
    }
    fn = *fnu + (real) (nd - 1);
    if (fn >= *fnul) {
	goto L30;
    }
    *nlast = nd;
    return 0;
L120:
    *nz = -1;
    return 0;
L130:
    if (rs1 > (float)0.) {
	goto L120;
    }
    *nz = *n;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	y[i__2].r = czero.r, y[i__2].i = czero.i;
/* L140: */
    }
    return 0;
} /* cuni1_ */

#ifdef __cplusplus
	}
#endif
