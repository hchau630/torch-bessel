/* fortran/cbesk/cbknu.f -- translated by f2c (version 20240504).
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
static integer c__11 = 11;
static integer c__5 = 5;

/* Subroutine */ int cbknu_(complex *z__, real *fnu, integer *kode, integer *
	n, complex *y, integer *nz, real *tol, real *elim, real *alim)
{
    /* Initialized data */

    static integer kmax = 30;
    static real fpi = (float)1.89769999331517738;
    static real tth = (float).666666666666666666;
    static real cc[8] = { (float).577215664901532861,(float)
	    -.0420026350340952355,(float)-.0421977345555443367,(float)
	    .00721894324666309954,(float)-2.15241674114950973e-4,(float)
	    -2.01348547807882387e-5,(float)1.13302723198169588e-6,(float)
	    6.11609510448141582e-9 };
    static real r1 = (float)2.;
    static complex czero = {(float)0.,(float)0.};
    static complex cone = {(float)1.,(float)0.};
    static complex ctwo = {(float)2.,(float)0.};
    static real pi = (float)3.14159265358979324;
    static real rthpi = (float)1.25331413731550025;
    static real spi = (float)1.90985931710274403;
    static real hpi = (float)1.57079632679489662;

    /* System generated locals */
    integer i__1, i__2;
    real r__1, r__2;
    complex q__1, q__2, q__3, q__4, q__5, q__6;

    /* Builtin functions */
    double r_imag(complex *), c_abs(complex *);
    void c_div(complex *, complex *, complex *), c_log(complex *, complex *);
    double sin(doublereal), exp(doublereal);
    void c_exp(complex *, complex *), c_sqrt(complex *, complex *);
    double cos(doublereal), atan(doublereal), sqrt(doublereal), log(
	    doublereal);
    void r_cnjg(complex *, complex *);

    /* Local variables */
    static complex f;
    static integer i__, j, k;
    static complex p, q;
    static real s, a1, a2, g1, g2;
    static complex p1, p2, s1, s2;
    static real t1, t2, aa, bb, fc, ak, bk;
    static complex ck;
    static integer ic;
    static real fk, as;
    static complex cs;
    static integer kk;
    static complex cy[2], cz, zd;
    static real rk, xd, tm, yd;
    static complex pt;
    static integer nw;
    static complex st, rz;
    static real xx, yy, p2i, p2m, p2r;
    static complex cch, csh;
    static real caz, fhs, elm, fks, dnu;
    static complex csr[3], css[3], fmu;
    static real bry[3];
    static integer inu;
    static complex smu;
    static real dnu2;
    static complex coef, celm;
    static real alas;
    static complex cscl, crsc;
    static integer inub, idum, iflag, kflag, koded;
    static real ascle;
    extern /* Subroutine */ int cshch_(complex *, complex *, complex *), 
	    cuchk_(complex *, integer *, real *, real *);
    extern doublereal gamln_(real *, integer *);
    static real helim;
    extern /* Subroutine */ int ckscl_(complex *, real *, integer *, complex *
	    , integer *, complex *, real *, real *, real *);
    static real etest;
    extern integer i1mach_(integer *);
    extern doublereal r1mach_(integer *);

/* ***BEGIN PROLOGUE  CBKNU */
/* ***REFER TO  CBESI,CBESK,CAIRY,CBESH */

/*     CBKNU COMPUTES THE K BESSEL FUNCTION IN THE RIGHT HALF Z PLANE */

/* ***ROUTINES CALLED  CKSCL,CSHCH,GAMLN,I1MACH,R1MACH,CUCHK */
/* ***END PROLOGUE  CBKNU */


    /* Parameter adjustments */
    --y;

    /* Function Body */



    xx = z__->r;
    yy = r_imag(z__);
    caz = c_abs(z__);
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
    *nz = 0;
    iflag = 0;
    koded = *kode;
    c_div(&q__1, &ctwo, z__);
    rz.r = q__1.r, rz.i = q__1.i;
    inu = (integer) (*fnu + (float).5);
    dnu = *fnu - (real) inu;
    if (dabs(dnu) == (float).5) {
	goto L110;
    }
    dnu2 = (float)0.;
    if (dabs(dnu) > *tol) {
	dnu2 = dnu * dnu;
    }
    if (caz > r1) {
	goto L110;
    }
/* ----------------------------------------------------------------------- */
/*     SERIES FOR CABS(Z).LE.R1 */
/* ----------------------------------------------------------------------- */
    fc = (float)1.;
    c_log(&q__1, &rz);
    smu.r = q__1.r, smu.i = q__1.i;
    q__2.r = dnu, q__2.i = (float)0.;
    q__1.r = smu.r * q__2.r - smu.i * q__2.i, q__1.i = smu.r * q__2.i + smu.i 
	    * q__2.r;
    fmu.r = q__1.r, fmu.i = q__1.i;
    cshch_(&fmu, &csh, &cch);
    if (dnu == (float)0.) {
	goto L10;
    }
    fc = dnu * pi;
    fc /= sin(fc);
    r__1 = (float)1. / dnu;
    q__2.r = r__1, q__2.i = (float)0.;
    q__1.r = csh.r * q__2.r - csh.i * q__2.i, q__1.i = csh.r * q__2.i + csh.i 
	    * q__2.r;
    smu.r = q__1.r, smu.i = q__1.i;
L10:
    a2 = dnu + (float)1.;
/* ----------------------------------------------------------------------- */
/*     GAM(1-Z)*GAM(1+Z)=PI*Z/SIN(PI*Z), T1=1/GAM(1-DNU), T2=1/GAM(1+DNU) */
/* ----------------------------------------------------------------------- */
    t2 = exp(-gamln_(&a2, &idum));
    t1 = (float)1. / (t2 * fc);
    if (dabs(dnu) > (float).1) {
	goto L40;
    }
/* ----------------------------------------------------------------------- */
/*     SERIES FOR F0 TO RESOLVE INDETERMINACY FOR SMALL ABS(DNU) */
/* ----------------------------------------------------------------------- */
    ak = (float)1.;
    s = cc[0];
    for (k = 2; k <= 8; ++k) {
	ak *= dnu2;
	tm = cc[k - 1] * ak;
	s += tm;
	if (dabs(tm) < *tol) {
	    goto L30;
	}
/* L20: */
    }
L30:
    g1 = -s;
    goto L50;
L40:
    g1 = (t1 - t2) / (dnu + dnu);
L50:
    g2 = (t1 + t2) * (float).5 * fc;
    g1 *= fc;
    q__3.r = g1, q__3.i = (float)0.;
    q__2.r = q__3.r * cch.r - q__3.i * cch.i, q__2.i = q__3.r * cch.i + 
	    q__3.i * cch.r;
    q__5.r = g2, q__5.i = (float)0.;
    q__4.r = smu.r * q__5.r - smu.i * q__5.i, q__4.i = smu.r * q__5.i + smu.i 
	    * q__5.r;
    q__1.r = q__2.r + q__4.r, q__1.i = q__2.i + q__4.i;
    f.r = q__1.r, f.i = q__1.i;
    c_exp(&q__1, &fmu);
    pt.r = q__1.r, pt.i = q__1.i;
    r__1 = (float).5 / t2;
    q__2.r = r__1, q__2.i = (float)0.;
    q__1.r = q__2.r * pt.r - q__2.i * pt.i, q__1.i = q__2.r * pt.i + q__2.i * 
	    pt.r;
    p.r = q__1.r, p.i = q__1.i;
    r__1 = (float).5 / t1;
    q__2.r = r__1, q__2.i = (float)0.;
    c_div(&q__1, &q__2, &pt);
    q.r = q__1.r, q.i = q__1.i;
    s1.r = f.r, s1.i = f.i;
    s2.r = p.r, s2.i = p.i;
    ak = (float)1.;
    a1 = (float)1.;
    ck.r = cone.r, ck.i = cone.i;
    bk = (float)1. - dnu2;
    if (inu > 0 || *n > 1) {
	goto L80;
    }
/* ----------------------------------------------------------------------- */
/*     GENERATE K(FNU,Z), 0.0D0 .LE. FNU .LT. 0.5D0 AND N=1 */
/* ----------------------------------------------------------------------- */
    if (caz < *tol) {
	goto L70;
    }
    q__2.r = z__->r * z__->r - z__->i * z__->i, q__2.i = z__->r * z__->i + 
	    z__->i * z__->r;
    q__1.r = q__2.r * (float).25 - q__2.i * (float)0., q__1.i = q__2.r * (
	    float)0. + q__2.i * (float).25;
    cz.r = q__1.r, cz.i = q__1.i;
    t1 = caz * (float).25 * caz;
L60:
    q__5.r = ak, q__5.i = (float)0.;
    q__4.r = f.r * q__5.r - f.i * q__5.i, q__4.i = f.r * q__5.i + f.i * 
	    q__5.r;
    q__3.r = q__4.r + p.r, q__3.i = q__4.i + p.i;
    q__2.r = q__3.r + q.r, q__2.i = q__3.i + q.i;
    r__1 = (float)1. / bk;
    q__6.r = r__1, q__6.i = (float)0.;
    q__1.r = q__2.r * q__6.r - q__2.i * q__6.i, q__1.i = q__2.r * q__6.i + 
	    q__2.i * q__6.r;
    f.r = q__1.r, f.i = q__1.i;
    r__1 = (float)1. / (ak - dnu);
    q__2.r = r__1, q__2.i = (float)0.;
    q__1.r = p.r * q__2.r - p.i * q__2.i, q__1.i = p.r * q__2.i + p.i * 
	    q__2.r;
    p.r = q__1.r, p.i = q__1.i;
    r__1 = (float)1. / (ak + dnu);
    q__2.r = r__1, q__2.i = (float)0.;
    q__1.r = q.r * q__2.r - q.i * q__2.i, q__1.i = q.r * q__2.i + q.i * 
	    q__2.r;
    q.r = q__1.r, q.i = q__1.i;
    rk = (float)1. / ak;
    q__2.r = ck.r * cz.r - ck.i * cz.i, q__2.i = ck.r * cz.i + ck.i * cz.r;
    q__3.r = rk, q__3.i = (float)0.;
    q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i + 
	    q__2.i * q__3.r;
    ck.r = q__1.r, ck.i = q__1.i;
    q__2.r = ck.r * f.r - ck.i * f.i, q__2.i = ck.r * f.i + ck.i * f.r;
    q__1.r = s1.r + q__2.r, q__1.i = s1.i + q__2.i;
    s1.r = q__1.r, s1.i = q__1.i;
    a1 = a1 * t1 * rk;
    bk = bk + ak + ak + (float)1.;
    ak += (float)1.;
    if (a1 > *tol) {
	goto L60;
    }
L70:
    y[1].r = s1.r, y[1].i = s1.i;
    if (koded == 1) {
	return 0;
    }
    c_exp(&q__2, z__);
    q__1.r = s1.r * q__2.r - s1.i * q__2.i, q__1.i = s1.r * q__2.i + s1.i * 
	    q__2.r;
    y[1].r = q__1.r, y[1].i = q__1.i;
    return 0;
/* ----------------------------------------------------------------------- */
/*     GENERATE K(DNU,Z) AND K(DNU+1,Z) FOR FORWARD RECURRENCE */
/* ----------------------------------------------------------------------- */
L80:
    if (caz < *tol) {
	goto L100;
    }
    q__2.r = z__->r * z__->r - z__->i * z__->i, q__2.i = z__->r * z__->i + 
	    z__->i * z__->r;
    q__1.r = q__2.r * (float).25 - q__2.i * (float)0., q__1.i = q__2.r * (
	    float)0. + q__2.i * (float).25;
    cz.r = q__1.r, cz.i = q__1.i;
    t1 = caz * (float).25 * caz;
L90:
    q__5.r = ak, q__5.i = (float)0.;
    q__4.r = f.r * q__5.r - f.i * q__5.i, q__4.i = f.r * q__5.i + f.i * 
	    q__5.r;
    q__3.r = q__4.r + p.r, q__3.i = q__4.i + p.i;
    q__2.r = q__3.r + q.r, q__2.i = q__3.i + q.i;
    r__1 = (float)1. / bk;
    q__6.r = r__1, q__6.i = (float)0.;
    q__1.r = q__2.r * q__6.r - q__2.i * q__6.i, q__1.i = q__2.r * q__6.i + 
	    q__2.i * q__6.r;
    f.r = q__1.r, f.i = q__1.i;
    r__1 = (float)1. / (ak - dnu);
    q__2.r = r__1, q__2.i = (float)0.;
    q__1.r = p.r * q__2.r - p.i * q__2.i, q__1.i = p.r * q__2.i + p.i * 
	    q__2.r;
    p.r = q__1.r, p.i = q__1.i;
    r__1 = (float)1. / (ak + dnu);
    q__2.r = r__1, q__2.i = (float)0.;
    q__1.r = q.r * q__2.r - q.i * q__2.i, q__1.i = q.r * q__2.i + q.i * 
	    q__2.r;
    q.r = q__1.r, q.i = q__1.i;
    rk = (float)1. / ak;
    q__2.r = ck.r * cz.r - ck.i * cz.i, q__2.i = ck.r * cz.i + ck.i * cz.r;
    q__3.r = rk, q__3.i = (float)0.;
    q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i + 
	    q__2.i * q__3.r;
    ck.r = q__1.r, ck.i = q__1.i;
    q__2.r = ck.r * f.r - ck.i * f.i, q__2.i = ck.r * f.i + ck.i * f.r;
    q__1.r = s1.r + q__2.r, q__1.i = s1.i + q__2.i;
    s1.r = q__1.r, s1.i = q__1.i;
    q__5.r = ak, q__5.i = (float)0.;
    q__4.r = f.r * q__5.r - f.i * q__5.i, q__4.i = f.r * q__5.i + f.i * 
	    q__5.r;
    q__3.r = p.r - q__4.r, q__3.i = p.i - q__4.i;
    q__2.r = ck.r * q__3.r - ck.i * q__3.i, q__2.i = ck.r * q__3.i + ck.i * 
	    q__3.r;
    q__1.r = s2.r + q__2.r, q__1.i = s2.i + q__2.i;
    s2.r = q__1.r, s2.i = q__1.i;
    a1 = a1 * t1 * rk;
    bk = bk + ak + ak + (float)1.;
    ak += (float)1.;
    if (a1 > *tol) {
	goto L90;
    }
L100:
    kflag = 2;
    bk = smu.r;
    a1 = *fnu + (float)1.;
    ak = a1 * dabs(bk);
    if (ak > *alim) {
	kflag = 3;
    }
    i__1 = kflag - 1;
    q__1.r = s2.r * css[i__1].r - s2.i * css[i__1].i, q__1.i = s2.r * css[
	    i__1].i + s2.i * css[i__1].r;
    p2.r = q__1.r, p2.i = q__1.i;
    q__1.r = p2.r * rz.r - p2.i * rz.i, q__1.i = p2.r * rz.i + p2.i * rz.r;
    s2.r = q__1.r, s2.i = q__1.i;
    i__1 = kflag - 1;
    q__1.r = s1.r * css[i__1].r - s1.i * css[i__1].i, q__1.i = s1.r * css[
	    i__1].i + s1.i * css[i__1].r;
    s1.r = q__1.r, s1.i = q__1.i;
    if (koded == 1) {
	goto L210;
    }
    c_exp(&q__1, z__);
    f.r = q__1.r, f.i = q__1.i;
    q__1.r = s1.r * f.r - s1.i * f.i, q__1.i = s1.r * f.i + s1.i * f.r;
    s1.r = q__1.r, s1.i = q__1.i;
    q__1.r = s2.r * f.r - s2.i * f.i, q__1.i = s2.r * f.i + s2.i * f.r;
    s2.r = q__1.r, s2.i = q__1.i;
    goto L210;
/* ----------------------------------------------------------------------- */
/*     IFLAG=0 MEANS NO UNDERFLOW OCCURRED */
/*     IFLAG=1 MEANS AN UNDERFLOW OCCURRED- COMPUTATION PROCEEDS WITH */
/*     KODED=2 AND A TEST FOR ON SCALE VALUES IS MADE DURING FORWARD */
/*     RECURSION */
/* ----------------------------------------------------------------------- */
L110:
    q__2.r = rthpi, q__2.i = (float)0.;
    c_sqrt(&q__3, z__);
    c_div(&q__1, &q__2, &q__3);
    coef.r = q__1.r, coef.i = q__1.i;
    kflag = 2;
    if (koded == 2) {
	goto L120;
    }
    if (xx > *alim) {
	goto L290;
    }
/*     BLANK LINE */
    i__1 = kflag - 1;
    a1 = exp(-xx) * css[i__1].r;
    q__2.r = a1, q__2.i = (float)0.;
    r__1 = cos(yy);
    r__2 = -sin(yy);
    q__3.r = r__1, q__3.i = r__2;
    q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i + 
	    q__2.i * q__3.r;
    pt.r = q__1.r, pt.i = q__1.i;
    q__1.r = coef.r * pt.r - coef.i * pt.i, q__1.i = coef.r * pt.i + coef.i * 
	    pt.r;
    coef.r = q__1.r, coef.i = q__1.i;
L120:
    if (dabs(dnu) == (float).5) {
	goto L300;
    }
/* ----------------------------------------------------------------------- */
/*     MILLER ALGORITHM FOR CABS(Z).GT.R1 */
/* ----------------------------------------------------------------------- */
    ak = cos(pi * dnu);
    ak = dabs(ak);
    if (ak == (float)0.) {
	goto L300;
    }
    fhs = (r__1 = (float).25 - dnu2, dabs(r__1));
    if (fhs == (float)0.) {
	goto L300;
    }
/* ----------------------------------------------------------------------- */
/*     COMPUTE R2=F(E). IF CABS(Z).GE.R2, USE FORWARD RECURRENCE TO */
/*     DETERMINE THE BACKWARD INDEX K. R2=F(E) IS A STRAIGHT LINE ON */
/*     12.LE.E.LE.60. E IS COMPUTED FROM 2**(-E)=B**(1-I1MACH(11))= */
/*     TOL WHERE B IS THE BASE OF THE ARITHMETIC. */
/* ----------------------------------------------------------------------- */
    t1 = (real) (i1mach_(&c__11) - 1) * r1mach_(&c__5) * (float)3.321928094;
    t1 = dmax(t1,(float)12.);
    t1 = dmin(t1,(float)60.);
    t2 = tth * t1 - (float)6.;
    if (xx != (float)0.) {
	goto L130;
    }
    t1 = hpi;
    goto L140;
L130:
    t1 = atan(yy / xx);
    t1 = dabs(t1);
L140:
    if (t2 > caz) {
	goto L170;
    }
/* ----------------------------------------------------------------------- */
/*     FORWARD RECURRENCE LOOP WHEN CABS(Z).GE.R2 */
/* ----------------------------------------------------------------------- */
    etest = ak / (pi * caz * *tol);
    fk = (float)1.;
    if (etest < (float)1.) {
	goto L180;
    }
    fks = (float)2.;
    rk = caz + caz + (float)2.;
    a1 = (float)0.;
    a2 = (float)1.;
    i__1 = kmax;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ak = fhs / fks;
	bk = rk / (fk + (float)1.);
	tm = a2;
	a2 = bk * a2 - ak * a1;
	a1 = tm;
	rk += (float)2.;
	fks = fks + fk + fk + (float)2.;
	fhs = fhs + fk + fk;
	fk += (float)1.;
	tm = dabs(a2) * fk;
	if (etest < tm) {
	    goto L160;
	}
/* L150: */
    }
    goto L310;
L160:
    fk += spi * t1 * sqrt(t2 / caz);
    fhs = (r__1 = (float).25 - dnu2, dabs(r__1));
    goto L180;
L170:
/* ----------------------------------------------------------------------- */
/*     COMPUTE BACKWARD INDEX K FOR CABS(Z).LT.R2 */
/* ----------------------------------------------------------------------- */
    a2 = sqrt(caz);
    ak = fpi * ak / (*tol * sqrt(a2));
    aa = t1 * (float)3. / (caz + (float)1.);
    bb = t1 * (float)14.7 / (caz + (float)28.);
    ak = (log(ak) + caz * cos(aa) / (caz * (float).008 + (float)1.)) / cos(bb)
	    ;
    fk = ak * (float).12125 * ak / caz + (float)1.5;
L180:
    k = (integer) fk;
/* ----------------------------------------------------------------------- */
/*     BACKWARD RECURRENCE LOOP FOR MILLER ALGORITHM */
/* ----------------------------------------------------------------------- */
    fk = (real) k;
    fks = fk * fk;
    p1.r = czero.r, p1.i = czero.i;
    q__1.r = *tol, q__1.i = (float)0.;
    p2.r = q__1.r, p2.i = q__1.i;
    cs.r = p2.r, cs.i = p2.i;
    i__1 = k;
    for (i__ = 1; i__ <= i__1; ++i__) {
	a1 = fks - fk;
	a2 = (fks + fk) / (a1 + fhs);
	rk = (float)2. / (fk + (float)1.);
	t1 = (fk + xx) * rk;
	t2 = yy * rk;
	pt.r = p2.r, pt.i = p2.i;
	q__4.r = t1, q__4.i = t2;
	q__3.r = p2.r * q__4.r - p2.i * q__4.i, q__3.i = p2.r * q__4.i + p2.i 
		* q__4.r;
	q__2.r = q__3.r - p1.r, q__2.i = q__3.i - p1.i;
	q__5.r = a2, q__5.i = (float)0.;
	q__1.r = q__2.r * q__5.r - q__2.i * q__5.i, q__1.i = q__2.r * q__5.i 
		+ q__2.i * q__5.r;
	p2.r = q__1.r, p2.i = q__1.i;
	p1.r = pt.r, p1.i = pt.i;
	q__1.r = cs.r + p2.r, q__1.i = cs.i + p2.i;
	cs.r = q__1.r, cs.i = q__1.i;
	fks = a1 - fk + (float)1.;
	fk += (float)-1.;
/* L190: */
    }
/* ----------------------------------------------------------------------- */
/*     COMPUTE (P2/CS)=(P2/CABS(CS))*(CONJG(CS)/CABS(CS)) FOR BETTER */
/*     SCALING */
/* ----------------------------------------------------------------------- */
    tm = c_abs(&cs);
    r__1 = (float)1. / tm;
    q__1.r = r__1, q__1.i = (float)0.;
    pt.r = q__1.r, pt.i = q__1.i;
    q__1.r = pt.r * p2.r - pt.i * p2.i, q__1.i = pt.r * p2.i + pt.i * p2.r;
    s1.r = q__1.r, s1.i = q__1.i;
    r_cnjg(&q__2, &cs);
    q__1.r = q__2.r * pt.r - q__2.i * pt.i, q__1.i = q__2.r * pt.i + q__2.i * 
	    pt.r;
    cs.r = q__1.r, cs.i = q__1.i;
    q__2.r = coef.r * s1.r - coef.i * s1.i, q__2.i = coef.r * s1.i + coef.i * 
	    s1.r;
    q__1.r = q__2.r * cs.r - q__2.i * cs.i, q__1.i = q__2.r * cs.i + q__2.i * 
	    cs.r;
    s1.r = q__1.r, s1.i = q__1.i;
    if (inu > 0 || *n > 1) {
	goto L200;
    }
    zd.r = z__->r, zd.i = z__->i;
    if (iflag == 1) {
	goto L270;
    }
    goto L240;
L200:
/* ----------------------------------------------------------------------- */
/*     COMPUTE P1/P2=(P1/CABS(P2)*CONJG(P2)/CABS(P2) FOR SCALING */
/* ----------------------------------------------------------------------- */
    tm = c_abs(&p2);
    r__1 = (float)1. / tm;
    q__1.r = r__1, q__1.i = (float)0.;
    pt.r = q__1.r, pt.i = q__1.i;
    q__1.r = pt.r * p1.r - pt.i * p1.i, q__1.i = pt.r * p1.i + pt.i * p1.r;
    p1.r = q__1.r, p1.i = q__1.i;
    r_cnjg(&q__2, &p2);
    q__1.r = q__2.r * pt.r - q__2.i * pt.i, q__1.i = q__2.r * pt.i + q__2.i * 
	    pt.r;
    p2.r = q__1.r, p2.i = q__1.i;
    q__1.r = p1.r * p2.r - p1.i * p2.i, q__1.i = p1.r * p2.i + p1.i * p2.r;
    pt.r = q__1.r, pt.i = q__1.i;
    r__1 = dnu + (float).5;
    q__5.r = r__1, q__5.i = (float)0.;
    q__4.r = q__5.r - pt.r, q__4.i = q__5.i - pt.i;
    c_div(&q__3, &q__4, z__);
    q__2.r = cone.r + q__3.r, q__2.i = cone.i + q__3.i;
    q__1.r = s1.r * q__2.r - s1.i * q__2.i, q__1.i = s1.r * q__2.i + s1.i * 
	    q__2.r;
    s2.r = q__1.r, s2.i = q__1.i;
/* ----------------------------------------------------------------------- */
/*     FORWARD RECURSION ON THE THREE TERM RECURSION RELATION WITH */
/*     SCALING NEAR EXPONENT EXTREMES ON KFLAG=1 OR KFLAG=3 */
/* ----------------------------------------------------------------------- */
L210:
    r__1 = dnu + (float)1.;
    q__2.r = r__1, q__2.i = (float)0.;
    q__1.r = q__2.r * rz.r - q__2.i * rz.i, q__1.i = q__2.r * rz.i + q__2.i * 
	    rz.r;
    ck.r = q__1.r, ck.i = q__1.i;
    if (*n == 1) {
	--inu;
    }
    if (inu > 0) {
	goto L220;
    }
    if (*n == 1) {
	s1.r = s2.r, s1.i = s2.i;
    }
    zd.r = z__->r, zd.i = z__->i;
    if (iflag == 1) {
	goto L270;
    }
    goto L240;
L220:
    inub = 1;
    if (iflag == 1) {
	goto L261;
    }
L225:
    i__1 = kflag - 1;
    p1.r = csr[i__1].r, p1.i = csr[i__1].i;
    ascle = bry[kflag - 1];
    i__1 = inu;
    for (i__ = inub; i__ <= i__1; ++i__) {
	st.r = s2.r, st.i = s2.i;
	q__2.r = ck.r * s2.r - ck.i * s2.i, q__2.i = ck.r * s2.i + ck.i * 
		s2.r;
	q__1.r = q__2.r + s1.r, q__1.i = q__2.i + s1.i;
	s2.r = q__1.r, s2.i = q__1.i;
	s1.r = st.r, s1.i = st.i;
	q__1.r = ck.r + rz.r, q__1.i = ck.i + rz.i;
	ck.r = q__1.r, ck.i = q__1.i;
	if (kflag >= 3) {
	    goto L230;
	}
	q__1.r = s2.r * p1.r - s2.i * p1.i, q__1.i = s2.r * p1.i + s2.i * 
		p1.r;
	p2.r = q__1.r, p2.i = q__1.i;
	p2r = p2.r;
	p2i = r_imag(&p2);
	p2r = dabs(p2r);
	p2i = dabs(p2i);
	p2m = dmax(p2r,p2i);
	if (p2m <= ascle) {
	    goto L230;
	}
	++kflag;
	ascle = bry[kflag - 1];
	q__1.r = s1.r * p1.r - s1.i * p1.i, q__1.i = s1.r * p1.i + s1.i * 
		p1.r;
	s1.r = q__1.r, s1.i = q__1.i;
	s2.r = p2.r, s2.i = p2.i;
	i__2 = kflag - 1;
	q__1.r = s1.r * css[i__2].r - s1.i * css[i__2].i, q__1.i = s1.r * css[
		i__2].i + s1.i * css[i__2].r;
	s1.r = q__1.r, s1.i = q__1.i;
	i__2 = kflag - 1;
	q__1.r = s2.r * css[i__2].r - s2.i * css[i__2].i, q__1.i = s2.r * css[
		i__2].i + s2.i * css[i__2].r;
	s2.r = q__1.r, s2.i = q__1.i;
	i__2 = kflag - 1;
	p1.r = csr[i__2].r, p1.i = csr[i__2].i;
L230:
	;
    }
    if (*n == 1) {
	s1.r = s2.r, s1.i = s2.i;
    }
L240:
    i__1 = kflag - 1;
    q__1.r = s1.r * csr[i__1].r - s1.i * csr[i__1].i, q__1.i = s1.r * csr[
	    i__1].i + s1.i * csr[i__1].r;
    y[1].r = q__1.r, y[1].i = q__1.i;
    if (*n == 1) {
	return 0;
    }
    i__1 = kflag - 1;
    q__1.r = s2.r * csr[i__1].r - s2.i * csr[i__1].i, q__1.i = s2.r * csr[
	    i__1].i + s2.i * csr[i__1].r;
    y[2].r = q__1.r, y[2].i = q__1.i;
    if (*n == 2) {
	return 0;
    }
    kk = 2;
L250:
    ++kk;
    if (kk > *n) {
	return 0;
    }
    i__1 = kflag - 1;
    p1.r = csr[i__1].r, p1.i = csr[i__1].i;
    ascle = bry[kflag - 1];
    i__1 = *n;
    for (i__ = kk; i__ <= i__1; ++i__) {
	p2.r = s2.r, p2.i = s2.i;
	q__2.r = ck.r * s2.r - ck.i * s2.i, q__2.i = ck.r * s2.i + ck.i * 
		s2.r;
	q__1.r = q__2.r + s1.r, q__1.i = q__2.i + s1.i;
	s2.r = q__1.r, s2.i = q__1.i;
	s1.r = p2.r, s1.i = p2.i;
	q__1.r = ck.r + rz.r, q__1.i = ck.i + rz.i;
	ck.r = q__1.r, ck.i = q__1.i;
	q__1.r = s2.r * p1.r - s2.i * p1.i, q__1.i = s2.r * p1.i + s2.i * 
		p1.r;
	p2.r = q__1.r, p2.i = q__1.i;
	i__2 = i__;
	y[i__2].r = p2.r, y[i__2].i = p2.i;
	if (kflag >= 3) {
	    goto L260;
	}
	p2r = p2.r;
	p2i = r_imag(&p2);
	p2r = dabs(p2r);
	p2i = dabs(p2i);
	p2m = dmax(p2r,p2i);
	if (p2m <= ascle) {
	    goto L260;
	}
	++kflag;
	ascle = bry[kflag - 1];
	q__1.r = s1.r * p1.r - s1.i * p1.i, q__1.i = s1.r * p1.i + s1.i * 
		p1.r;
	s1.r = q__1.r, s1.i = q__1.i;
	s2.r = p2.r, s2.i = p2.i;
	i__2 = kflag - 1;
	q__1.r = s1.r * css[i__2].r - s1.i * css[i__2].i, q__1.i = s1.r * css[
		i__2].i + s1.i * css[i__2].r;
	s1.r = q__1.r, s1.i = q__1.i;
	i__2 = kflag - 1;
	q__1.r = s2.r * css[i__2].r - s2.i * css[i__2].i, q__1.i = s2.r * css[
		i__2].i + s2.i * css[i__2].r;
	s2.r = q__1.r, s2.i = q__1.i;
	i__2 = kflag - 1;
	p1.r = csr[i__2].r, p1.i = csr[i__2].i;
L260:
	;
    }
    return 0;
/* ----------------------------------------------------------------------- */
/*     IFLAG=1 CASES, FORWARD RECURRENCE ON SCALED VALUES ON UNDERFLOW */
/* ----------------------------------------------------------------------- */
L261:
    helim = *elim * (float).5;
    elm = exp(-(*elim));
    q__1.r = elm, q__1.i = (float)0.;
    celm.r = q__1.r, celm.i = q__1.i;
    ascle = bry[0];
    zd.r = z__->r, zd.i = z__->i;
    xd = xx;
    yd = yy;
    ic = -1;
    j = 2;
    i__1 = inu;
    for (i__ = 1; i__ <= i__1; ++i__) {
	st.r = s2.r, st.i = s2.i;
	q__2.r = ck.r * s2.r - ck.i * s2.i, q__2.i = ck.r * s2.i + ck.i * 
		s2.r;
	q__1.r = q__2.r + s1.r, q__1.i = q__2.i + s1.i;
	s2.r = q__1.r, s2.i = q__1.i;
	s1.r = st.r, s1.i = st.i;
	q__1.r = ck.r + rz.r, q__1.i = ck.i + rz.i;
	ck.r = q__1.r, ck.i = q__1.i;
	as = c_abs(&s2);
	alas = log(as);
	p2r = -xd + alas;
	if (p2r < -(*elim)) {
	    goto L263;
	}
	q__2.r = -zd.r, q__2.i = -zd.i;
	c_log(&q__3, &s2);
	q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
	p2.r = q__1.r, p2.i = q__1.i;
	p2r = p2.r;
	p2i = r_imag(&p2);
	p2m = exp(p2r) / *tol;
	q__2.r = p2m, q__2.i = (float)0.;
	r__1 = cos(p2i);
	r__2 = sin(p2i);
	q__3.r = r__1, q__3.i = r__2;
	q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i 
		+ q__2.i * q__3.r;
	p1.r = q__1.r, p1.i = q__1.i;
	cuchk_(&p1, &nw, &ascle, tol);
	if (nw != 0) {
	    goto L263;
	}
	j = 3 - j;
	i__2 = j - 1;
	cy[i__2].r = p1.r, cy[i__2].i = p1.i;
	if (ic == i__ - 1) {
	    goto L264;
	}
	ic = i__;
	goto L262;
L263:
	if (alas < helim) {
	    goto L262;
	}
	xd -= *elim;
	q__1.r = s1.r * celm.r - s1.i * celm.i, q__1.i = s1.r * celm.i + s1.i 
		* celm.r;
	s1.r = q__1.r, s1.i = q__1.i;
	q__1.r = s2.r * celm.r - s2.i * celm.i, q__1.i = s2.r * celm.i + s2.i 
		* celm.r;
	s2.r = q__1.r, s2.i = q__1.i;
	q__1.r = xd, q__1.i = yd;
	zd.r = q__1.r, zd.i = q__1.i;
L262:
	;
    }
    if (*n == 1) {
	s1.r = s2.r, s1.i = s2.i;
    }
    goto L270;
L264:
    kflag = 1;
    inub = i__ + 1;
    i__1 = j - 1;
    s2.r = cy[i__1].r, s2.i = cy[i__1].i;
    j = 3 - j;
    i__1 = j - 1;
    s1.r = cy[i__1].r, s1.i = cy[i__1].i;
    if (inub <= inu) {
	goto L225;
    }
    if (*n == 1) {
	s1.r = s2.r, s1.i = s2.i;
    }
    goto L240;
L270:
    y[1].r = s1.r, y[1].i = s1.i;
    if (*n == 1) {
	goto L280;
    }
    y[2].r = s2.r, y[2].i = s2.i;
L280:
    ascle = bry[0];
    ckscl_(&zd, fnu, n, &y[1], nz, &rz, &ascle, tol, elim);
    inu = *n - *nz;
    if (inu <= 0) {
	return 0;
    }
    kk = *nz + 1;
    i__1 = kk;
    s1.r = y[i__1].r, s1.i = y[i__1].i;
    i__1 = kk;
    q__1.r = s1.r * csr[0].r - s1.i * csr[0].i, q__1.i = s1.r * csr[0].i + 
	    s1.i * csr[0].r;
    y[i__1].r = q__1.r, y[i__1].i = q__1.i;
    if (inu == 1) {
	return 0;
    }
    kk = *nz + 2;
    i__1 = kk;
    s2.r = y[i__1].r, s2.i = y[i__1].i;
    i__1 = kk;
    q__1.r = s2.r * csr[0].r - s2.i * csr[0].i, q__1.i = s2.r * csr[0].i + 
	    s2.i * csr[0].r;
    y[i__1].r = q__1.r, y[i__1].i = q__1.i;
    if (inu == 2) {
	return 0;
    }
    t2 = *fnu + (real) (kk - 1);
    q__2.r = t2, q__2.i = (float)0.;
    q__1.r = q__2.r * rz.r - q__2.i * rz.i, q__1.i = q__2.r * rz.i + q__2.i * 
	    rz.r;
    ck.r = q__1.r, ck.i = q__1.i;
    kflag = 1;
    goto L250;
L290:
/* ----------------------------------------------------------------------- */
/*     SCALE BY EXP(Z), IFLAG = 1 CASES */
/* ----------------------------------------------------------------------- */
    koded = 2;
    iflag = 1;
    kflag = 2;
    goto L120;
/* ----------------------------------------------------------------------- */
/*     FNU=HALF ODD INTEGER CASE, DNU=-0.5 */
/* ----------------------------------------------------------------------- */
L300:
    s1.r = coef.r, s1.i = coef.i;
    s2.r = coef.r, s2.i = coef.i;
    goto L210;
L310:
    *nz = -2;
    return 0;
} /* cbknu_ */

#ifdef __cplusplus
	}
#endif
