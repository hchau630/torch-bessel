/* fortran/cbesk/cwrsk.f -- translated by f2c (version 20240504).
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

static integer c__2 = 2;
static integer c__1 = 1;

/* Subroutine */ int cwrsk_(complex *zr, real *fnu, integer *kode, integer *n,
	 complex *y, integer *nz, complex *cw, real *tol, real *elim, real *
	alim)
{
    /* System generated locals */
    integer i__1, i__2;
    real r__1;
    complex q__1, q__2, q__3;

    /* Builtin functions */
    double r_imag(complex *), cos(doublereal), sin(doublereal), c_abs(complex 
	    *);
    void r_cnjg(complex *, complex *);

    /* Local variables */
    static integer i__;
    static complex c1, c2;
    static real s1, s2;
    static complex ct;
    static integer nw;
    static complex st;
    static real yy, act, acw;
    static complex rct, cscl, cinu;
    static real ascle;
    extern /* Subroutine */ int cbknu_(complex *, real *, integer *, integer *
	    , complex *, integer *, real *, real *, real *), crati_(complex *,
	     real *, integer *, complex *, real *);
    extern doublereal r1mach_(integer *);

/* ***BEGIN PROLOGUE  CWRSK */
/* ***REFER TO  CBESI,CBESK */

/*     CWRSK COMPUTES THE I BESSEL FUNCTION FOR RE(Z).GE.0.0 BY */
/*     NORMALIZING THE I FUNCTION RATIOS FROM CRATI BY THE WRONSKIAN */

/* ***ROUTINES CALLED  CBKNU,CRATI,R1MACH */
/* ***END PROLOGUE  CWRSK */
/* ----------------------------------------------------------------------- */
/*     I(FNU+I-1,Z) BY BACKWARD RECURRENCE FOR RATIOS */
/*     Y(I)=I(FNU+I,Z)/I(FNU+I-1,Z) FROM CRATI NORMALIZED BY THE */
/*     WRONSKIAN WITH K(FNU,Z) AND K(FNU+1,Z) FROM CBKNU. */
/* ----------------------------------------------------------------------- */
    /* Parameter adjustments */
    --y;
    --cw;

    /* Function Body */
    *nz = 0;
    cbknu_(zr, fnu, kode, &c__2, &cw[1], &nw, tol, elim, alim);
    if (nw != 0) {
	goto L50;
    }
    crati_(zr, fnu, n, &y[1], tol);
/* ----------------------------------------------------------------------- */
/*     RECUR FORWARD ON I(FNU+1,Z) = R(FNU,Z)*I(FNU,Z), */
/*     R(FNU+J-1,Z)=Y(J),  J=1,...,N */
/* ----------------------------------------------------------------------- */
    cinu.r = (float)1., cinu.i = (float)0.;
    if (*kode == 1) {
	goto L10;
    }
    yy = r_imag(zr);
    s1 = cos(yy);
    s2 = sin(yy);
    q__1.r = s1, q__1.i = s2;
    cinu.r = q__1.r, cinu.i = q__1.i;
L10:
/* ----------------------------------------------------------------------- */
/*     ON LOW EXPONENT MACHINES THE K FUNCTIONS CAN BE CLOSE TO BOTH */
/*     THE UNDER AND OVERFLOW LIMITS AND THE NORMALIZATION MUST BE */
/*     SCALED TO PREVENT OVER OR UNDERFLOW. CUOIK HAS DETERMINED THAT */
/*     THE RESULT IS ON SCALE. */
/* ----------------------------------------------------------------------- */
    acw = c_abs(&cw[2]);
    ascle = r1mach_(&c__1) * (float)1e3 / *tol;
    cscl.r = (float)1., cscl.i = (float)0.;
    if (acw > ascle) {
	goto L20;
    }
    r__1 = (float)1. / *tol;
    q__1.r = r__1, q__1.i = (float)0.;
    cscl.r = q__1.r, cscl.i = q__1.i;
    goto L30;
L20:
    ascle = (float)1. / ascle;
    if (acw < ascle) {
	goto L30;
    }
    q__1.r = *tol, q__1.i = (float)0.;
    cscl.r = q__1.r, cscl.i = q__1.i;
L30:
    q__1.r = cw[1].r * cscl.r - cw[1].i * cscl.i, q__1.i = cw[1].r * cscl.i + 
	    cw[1].i * cscl.r;
    c1.r = q__1.r, c1.i = q__1.i;
    q__1.r = cw[2].r * cscl.r - cw[2].i * cscl.i, q__1.i = cw[2].r * cscl.i + 
	    cw[2].i * cscl.r;
    c2.r = q__1.r, c2.i = q__1.i;
    st.r = y[1].r, st.i = y[1].i;
/* ----------------------------------------------------------------------- */
/*     CINU=CINU*(CONJG(CT)/CABS(CT))*(1.0E0/CABS(CT) PREVENTS */
/*     UNDER- OR OVERFLOW PREMATURELY BY SQUARING CABS(CT) */
/* ----------------------------------------------------------------------- */
    q__3.r = st.r * c1.r - st.i * c1.i, q__3.i = st.r * c1.i + st.i * c1.r;
    q__2.r = c2.r + q__3.r, q__2.i = c2.i + q__3.i;
    q__1.r = zr->r * q__2.r - zr->i * q__2.i, q__1.i = zr->r * q__2.i + zr->i 
	    * q__2.r;
    ct.r = q__1.r, ct.i = q__1.i;
    act = c_abs(&ct);
    r__1 = (float)1. / act;
    q__1.r = r__1, q__1.i = (float)0.;
    rct.r = q__1.r, rct.i = q__1.i;
    r_cnjg(&q__2, &ct);
    q__1.r = q__2.r * rct.r - q__2.i * rct.i, q__1.i = q__2.r * rct.i + 
	    q__2.i * rct.r;
    ct.r = q__1.r, ct.i = q__1.i;
    q__2.r = cinu.r * rct.r - cinu.i * rct.i, q__2.i = cinu.r * rct.i + 
	    cinu.i * rct.r;
    q__1.r = q__2.r * ct.r - q__2.i * ct.i, q__1.i = q__2.r * ct.i + q__2.i * 
	    ct.r;
    cinu.r = q__1.r, cinu.i = q__1.i;
    q__1.r = cinu.r * cscl.r - cinu.i * cscl.i, q__1.i = cinu.r * cscl.i + 
	    cinu.i * cscl.r;
    y[1].r = q__1.r, y[1].i = q__1.i;
    if (*n == 1) {
	return 0;
    }
    i__1 = *n;
    for (i__ = 2; i__ <= i__1; ++i__) {
	q__1.r = st.r * cinu.r - st.i * cinu.i, q__1.i = st.r * cinu.i + st.i 
		* cinu.r;
	cinu.r = q__1.r, cinu.i = q__1.i;
	i__2 = i__;
	st.r = y[i__2].r, st.i = y[i__2].i;
	i__2 = i__;
	q__1.r = cinu.r * cscl.r - cinu.i * cscl.i, q__1.i = cinu.r * cscl.i 
		+ cinu.i * cscl.r;
	y[i__2].r = q__1.r, y[i__2].i = q__1.i;
/* L40: */
    }
    return 0;
L50:
    *nz = -1;
    if (nw == -2) {
	*nz = -2;
    }
    return 0;
} /* cwrsk_ */

#ifdef __cplusplus
	}
#endif
