/* fortran/cbesk/cbuni.f -- translated by f2c (version 20240504).
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
static complex c_b12 = {(float)2.,(float)0.};

/* Subroutine */ int cbuni_(complex *z__, real *fnu, integer *kode, integer *
	n, complex *y, integer *nz, integer *nui, integer *nlast, real *fnul, 
	real *tol, real *elim, real *alim)
{
    /* System generated locals */
    integer i__1, i__2;
    real r__1;
    complex q__1, q__2, q__3, q__4;

    /* Builtin functions */
    double r_imag(complex *), c_abs(complex *);
    void c_div(complex *, complex *, complex *);

    /* Local variables */
    static integer i__, k;
    static complex s1, s2;
    static real ax, ay;
    static integer nl;
    static complex cy[2];
    static integer nw;
    static complex st, rz;
    static real xx, yy, gnu, bry[3], sti, stm, str;
    static complex cscl, cscr;
    static real dfnu, fnui;
    extern /* Subroutine */ int cuni1_(complex *, real *, integer *, integer *
	    , complex *, integer *, integer *, real *, real *, real *, real *)
	    , cuni2_(complex *, real *, integer *, integer *, complex *, 
	    integer *, integer *, real *, real *, real *, real *);
    static integer iflag;
    static real ascle;
    static integer iform;
    extern doublereal r1mach_(integer *);

/* ***BEGIN PROLOGUE  CBUNI */
/* ***REFER TO  CBESI,CBESK */

/*     CBUNI COMPUTES THE I BESSEL FUNCTION FOR LARGE CABS(Z).GT. */
/*     FNUL AND FNU+N-1.LT.FNUL. THE ORDER IS INCREASED FROM */
/*     FNU+N-1 GREATER THAN FNUL BY ADDING NUI AND COMPUTING */
/*     ACCORDING TO THE UNIFORM ASYMPTOTIC EXPANSION FOR I(FNU,Z) */
/*     ON IFORM=1 AND THE EXPANSION FOR J(FNU,Z) ON IFORM=2 */

/* ***ROUTINES CALLED  CUNI1,CUNI2,R1MACH */
/* ***END PROLOGUE  CBUNI */
    /* Parameter adjustments */
    --y;

    /* Function Body */
    *nz = 0;
    xx = z__->r;
    yy = r_imag(z__);
    ax = dabs(xx) * (float)1.7321;
    ay = dabs(yy);
    iform = 1;
    if (ay > ax) {
	iform = 2;
    }
    if (*nui == 0) {
	goto L60;
    }
    fnui = (real) (*nui);
    dfnu = *fnu + (real) (*n - 1);
    gnu = dfnu + fnui;
    if (iform == 2) {
	goto L10;
    }
/* ----------------------------------------------------------------------- */
/*     ASYMPTOTIC EXPANSION FOR I(FNU,Z) FOR LARGE FNU APPLIED IN */
/*     -PI/3.LE.ARG(Z).LE.PI/3 */
/* ----------------------------------------------------------------------- */
    cuni1_(z__, &gnu, kode, &c__2, cy, &nw, nlast, fnul, tol, elim, alim);
    goto L20;
L10:
/* ----------------------------------------------------------------------- */
/*     ASYMPTOTIC EXPANSION FOR J(FNU,Z*EXP(M*HPI)) FOR LARGE FNU */
/*     APPLIED IN PI/3.LT.ABS(ARG(Z)).LE.PI/2 WHERE M=+I OR -I */
/*     AND HPI=PI/2 */
/* ----------------------------------------------------------------------- */
    cuni2_(z__, &gnu, kode, &c__2, cy, &nw, nlast, fnul, tol, elim, alim);
L20:
    if (nw < 0) {
	goto L50;
    }
    if (nw != 0) {
	goto L90;
    }
    ay = c_abs(cy);
/* ---------------------------------------------------------------------- */
/*     SCALE BACKWARD RECURRENCE, BRY(3) IS DEFINED BUT NEVER USED */
/* ---------------------------------------------------------------------- */
    bry[0] = r1mach_(&c__1) * (float)1e3 / *tol;
    bry[1] = (float)1. / bry[0];
    bry[2] = bry[1];
    iflag = 2;
    ascle = bry[1];
    ax = (float)1.;
    q__1.r = ax, q__1.i = (float)0.;
    cscl.r = q__1.r, cscl.i = q__1.i;
    if (ay > bry[0]) {
	goto L21;
    }
    iflag = 1;
    ascle = bry[0];
    ax = (float)1. / *tol;
    q__1.r = ax, q__1.i = (float)0.;
    cscl.r = q__1.r, cscl.i = q__1.i;
    goto L25;
L21:
    if (ay < bry[1]) {
	goto L25;
    }
    iflag = 3;
    ascle = bry[2];
    ax = *tol;
    q__1.r = ax, q__1.i = (float)0.;
    cscl.r = q__1.r, cscl.i = q__1.i;
L25:
    ay = (float)1. / ax;
    q__1.r = ay, q__1.i = (float)0.;
    cscr.r = q__1.r, cscr.i = q__1.i;
    q__1.r = cy[1].r * cscl.r - cy[1].i * cscl.i, q__1.i = cy[1].r * cscl.i + 
	    cy[1].i * cscl.r;
    s1.r = q__1.r, s1.i = q__1.i;
    q__1.r = cy[0].r * cscl.r - cy[0].i * cscl.i, q__1.i = cy[0].r * cscl.i + 
	    cy[0].i * cscl.r;
    s2.r = q__1.r, s2.i = q__1.i;
    c_div(&q__1, &c_b12, z__);
    rz.r = q__1.r, rz.i = q__1.i;
    i__1 = *nui;
    for (i__ = 1; i__ <= i__1; ++i__) {
	st.r = s2.r, st.i = s2.i;
	r__1 = dfnu + fnui;
	q__4.r = r__1, q__4.i = (float)0.;
	q__3.r = q__4.r * rz.r - q__4.i * rz.i, q__3.i = q__4.r * rz.i + 
		q__4.i * rz.r;
	q__2.r = q__3.r * s2.r - q__3.i * s2.i, q__2.i = q__3.r * s2.i + 
		q__3.i * s2.r;
	q__1.r = q__2.r + s1.r, q__1.i = q__2.i + s1.i;
	s2.r = q__1.r, s2.i = q__1.i;
	s1.r = st.r, s1.i = st.i;
	fnui += (float)-1.;
	if (iflag >= 3) {
	    goto L30;
	}
	q__1.r = s2.r * cscr.r - s2.i * cscr.i, q__1.i = s2.r * cscr.i + s2.i 
		* cscr.r;
	st.r = q__1.r, st.i = q__1.i;
	str = st.r;
	sti = r_imag(&st);
	str = dabs(str);
	sti = dabs(sti);
	stm = dmax(str,sti);
	if (stm <= ascle) {
	    goto L30;
	}
	++iflag;
	ascle = bry[iflag - 1];
	q__1.r = s1.r * cscr.r - s1.i * cscr.i, q__1.i = s1.r * cscr.i + s1.i 
		* cscr.r;
	s1.r = q__1.r, s1.i = q__1.i;
	s2.r = st.r, s2.i = st.i;
	ax *= *tol;
	ay = (float)1. / ax;
	q__1.r = ax, q__1.i = (float)0.;
	cscl.r = q__1.r, cscl.i = q__1.i;
	q__1.r = ay, q__1.i = (float)0.;
	cscr.r = q__1.r, cscr.i = q__1.i;
	q__1.r = s1.r * cscl.r - s1.i * cscl.i, q__1.i = s1.r * cscl.i + s1.i 
		* cscl.r;
	s1.r = q__1.r, s1.i = q__1.i;
	q__1.r = s2.r * cscl.r - s2.i * cscl.i, q__1.i = s2.r * cscl.i + s2.i 
		* cscl.r;
	s2.r = q__1.r, s2.i = q__1.i;
L30:
	;
    }
    i__1 = *n;
    q__1.r = s2.r * cscr.r - s2.i * cscr.i, q__1.i = s2.r * cscr.i + s2.i * 
	    cscr.r;
    y[i__1].r = q__1.r, y[i__1].i = q__1.i;
    if (*n == 1) {
	return 0;
    }
    nl = *n - 1;
    fnui = (real) nl;
    k = nl;
    i__1 = nl;
    for (i__ = 1; i__ <= i__1; ++i__) {
	st.r = s2.r, st.i = s2.i;
	r__1 = *fnu + fnui;
	q__4.r = r__1, q__4.i = (float)0.;
	q__3.r = q__4.r * rz.r - q__4.i * rz.i, q__3.i = q__4.r * rz.i + 
		q__4.i * rz.r;
	q__2.r = q__3.r * s2.r - q__3.i * s2.i, q__2.i = q__3.r * s2.i + 
		q__3.i * s2.r;
	q__1.r = q__2.r + s1.r, q__1.i = q__2.i + s1.i;
	s2.r = q__1.r, s2.i = q__1.i;
	s1.r = st.r, s1.i = st.i;
	q__1.r = s2.r * cscr.r - s2.i * cscr.i, q__1.i = s2.r * cscr.i + s2.i 
		* cscr.r;
	st.r = q__1.r, st.i = q__1.i;
	i__2 = k;
	y[i__2].r = st.r, y[i__2].i = st.i;
	fnui += (float)-1.;
	--k;
	if (iflag >= 3) {
	    goto L40;
	}
	str = st.r;
	sti = r_imag(&st);
	str = dabs(str);
	sti = dabs(sti);
	stm = dmax(str,sti);
	if (stm <= ascle) {
	    goto L40;
	}
	++iflag;
	ascle = bry[iflag - 1];
	q__1.r = s1.r * cscr.r - s1.i * cscr.i, q__1.i = s1.r * cscr.i + s1.i 
		* cscr.r;
	s1.r = q__1.r, s1.i = q__1.i;
	s2.r = st.r, s2.i = st.i;
	ax *= *tol;
	ay = (float)1. / ax;
	q__1.r = ax, q__1.i = (float)0.;
	cscl.r = q__1.r, cscl.i = q__1.i;
	q__1.r = ay, q__1.i = (float)0.;
	cscr.r = q__1.r, cscr.i = q__1.i;
	q__1.r = s1.r * cscl.r - s1.i * cscl.i, q__1.i = s1.r * cscl.i + s1.i 
		* cscl.r;
	s1.r = q__1.r, s1.i = q__1.i;
	q__1.r = s2.r * cscl.r - s2.i * cscl.i, q__1.i = s2.r * cscl.i + s2.i 
		* cscl.r;
	s2.r = q__1.r, s2.i = q__1.i;
L40:
	;
    }
    return 0;
L50:
    *nz = -1;
    if (nw == -2) {
	*nz = -2;
    }
    return 0;
L60:
    if (iform == 2) {
	goto L70;
    }
/* ----------------------------------------------------------------------- */
/*     ASYMPTOTIC EXPANSION FOR I(FNU,Z) FOR LARGE FNU APPLIED IN */
/*     -PI/3.LE.ARG(Z).LE.PI/3 */
/* ----------------------------------------------------------------------- */
    cuni1_(z__, fnu, kode, n, &y[1], &nw, nlast, fnul, tol, elim, alim);
    goto L80;
L70:
/* ----------------------------------------------------------------------- */
/*     ASYMPTOTIC EXPANSION FOR J(FNU,Z*EXP(M*HPI)) FOR LARGE FNU */
/*     APPLIED IN PI/3.LT.ABS(ARG(Z)).LE.PI/2 WHERE M=+I OR -I */
/*     AND HPI=PI/2 */
/* ----------------------------------------------------------------------- */
    cuni2_(z__, fnu, kode, n, &y[1], &nw, nlast, fnul, tol, elim, alim);
L80:
    if (nw < 0) {
	goto L50;
    }
    *nz = nw;
    return 0;
L90:
    *nlast = *n;
    return 0;
} /* cbuni_ */

#ifdef __cplusplus
	}
#endif
