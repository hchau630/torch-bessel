/* fortran/cbesk/cshch.f -- translated by f2c (version 20240504).
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

/* Subroutine */ int cshch_(complex *z__, complex *csh, complex *cch)
{
    /* System generated locals */
    complex q__1;

    /* Builtin functions */
    double r_imag(complex *), sinh(doublereal), cosh(doublereal), sin(
	    doublereal), cos(doublereal);

    /* Local variables */
    static real x, y, ch, cn, sh, sn, cchi, cchr, cshi, cshr;

/* ***BEGIN PROLOGUE  CSHCH */
/* ***REFER TO  CBESK,CBESH */

/*     CSHCH COMPUTES THE COMPLEX HYPERBOLIC FUNCTIONS CSH=SINH(X+I*Y) */
/*     AND CCH=COSH(X+I*Y), WHERE I**2=-1. */

/* ***ROUTINES CALLED  (NONE) */
/* ***END PROLOGUE  CSHCH */
    x = z__->r;
    y = r_imag(z__);
    sh = sinh(x);
    ch = cosh(x);
    sn = sin(y);
    cn = cos(y);
    cshr = sh * cn;
    cshi = ch * sn;
    q__1.r = cshr, q__1.i = cshi;
    csh->r = q__1.r, csh->i = q__1.i;
    cchr = ch * cn;
    cchi = sh * sn;
    q__1.r = cchr, q__1.i = cchi;
    cch->r = q__1.r, cch->i = q__1.i;
    return 0;
} /* cshch_ */

#ifdef __cplusplus
	}
#endif
