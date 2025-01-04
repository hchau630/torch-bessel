/* fortran/cbesk/cunik.f -- translated by f2c (version 20240504).
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

/* Subroutine */ int cunik_(complex *zr, real *fnu, integer *ikflg, integer *
	ipmtr, real *tol, integer *init, complex *phi, complex *zeta1, 
	complex *zeta2, complex *sum, complex *cwrk)
{
    /* Initialized data */

    static complex czero = {(float)0.,(float)0.};
    static complex cone = {(float)1.,(float)0.};
    static complex con[2] = { {(float).398942280401432678,(float)0.},{(float)
	    1.25331413731550025,(float)0.} };
    static real c__[120] = { (float)1.,(float)-.208333333333333333,(float)
	    .125,(float).334201388888888889,(float)-.401041666666666667,(
	    float).0703125,(float)-1.02581259645061728,(float)
	    1.84646267361111111,(float)-.8912109375,(float).0732421875,(float)
	    4.66958442342624743,(float)-11.2070026162229938,(float)
	    8.78912353515625,(float)-2.3640869140625,(float).112152099609375,(
	    float)-28.2120725582002449,(float)84.6362176746007346,(float)
	    -91.8182415432400174,(float)42.5349987453884549,(float)
	    -7.3687943594796317,(float).227108001708984375,(float)
	    212.570130039217123,(float)-765.252468141181642,(float)
	    1059.99045252799988,(float)-699.579627376132541,(float)
	    218.19051174421159,(float)-26.4914304869515555,(float)
	    .572501420974731445,(float)-1919.457662318407,(float)
	    8061.72218173730938,(float)-13586.5500064341374,(float)
	    11655.3933368645332,(float)-5305.64697861340311,(float)
	    1200.90291321635246,(float)-108.090919788394656,(float)
	    1.7277275025844574,(float)20204.2913309661486,(float)
	    -96980.5983886375135,(float)192547.001232531532,(float)
	    -203400.177280415534,(float)122200.46498301746,(float)
	    -41192.6549688975513,(float)7109.51430248936372,(float)
	    -493.915304773088012,(float)6.07404200127348304,(float)
	    -242919.187900551333,(float)1311763.6146629772,(float)
	    -2998015.91853810675,(float)3763271.297656404,(float)
	    -2813563.22658653411,(float)1268365.27332162478,(float)
	    -331645.172484563578,(float)45218.7689813627263,(float)
	    -2499.83048181120962,(float)24.3805296995560639,(float)
	    3284469.85307203782,(float)-19706819.1184322269,(float)
	    50952602.4926646422,(float)-74105148.2115326577,(float)
	    66344512.2747290267,(float)-37567176.6607633513,(float)
	    13288767.1664218183,(float)-2785618.12808645469,(float)
	    308186.404612662398,(float)-13886.0897537170405,(float)
	    110.017140269246738,(float)-49329253.664509962,(float)
	    325573074.185765749,(float)-939462359.681578403,(float)
	    1553596899.57058006,(float)-1621080552.10833708,(float)
	    1106842816.82301447,(float)-495889784.275030309,(float)
	    142062907.797533095,(float)-24474062.7257387285,(float)
	    2243768.17792244943,(float)-84005.4336030240853,(float)
	    551.335896122020586,(float)814789096.118312115,(float)
	    -5866481492.05184723,(float)18688207509.2958249,(float)
	    -34632043388.1587779,(float)41280185579.753974,(float)
	    -33026599749.8007231,(float)17954213731.1556001,(float)
	    -6563293792.61928433,(float)1559279864.87925751,(float)
	    -225105661.889415278,(float)17395107.5539781645,(float)
	    -549842.327572288687,(float)3038.09051092238427,(float)
	    -14679261247.6956167,(float)114498237732.02581,(float)
	    -399096175224.466498,(float)819218669548.577329,(float)
	    -1098375156081.22331,(float)1008158106865.38209,(float)
	    -645364869245.376503,(float)287900649906.150589,(float)
	    -87867072178.0232657,(float)17634730606.8349694,(float)
	    -2167164983.22379509,(float)143157876.718888981,(float)
	    -3871833.44257261262,(float)18257.7554742931747,(float)
	    286464035717.679043,(float)-2406297900028.50396,(float)
	    9109341185239.89896,(float)-20516899410934.4374,(float)
	    30565125519935.3206,(float)-31667088584785.1584,(float)
	    23348364044581.8409,(float)-12320491305598.2872,(float)
	    4612725780849.13197,(float)-1196552880196.1816,(float)
	    205914503232.410016,(float)-21822927757.5292237,(float)
	    1247009293.51271032,(float)-29188388.1222208134,(float)
	    118838.426256783253 };

    /* System generated locals */
    integer i__1, i__2;
    real r__1;
    complex q__1, q__2, q__3;

    /* Builtin functions */
    double r_imag(complex *), log(doublereal);
    void c_sqrt(complex *, complex *), c_div(complex *, complex *, complex *),
	     c_log(complex *, complex *);

    /* Local variables */
    static integer i__, j, k, l;
    static complex s, t, t2;
    static real ac;
    static complex sr, zn, cfn;
    static real rfn;
    static complex crfn;
    static real test, tsti, tstr;
    extern doublereal r1mach_(integer *);

/* ***BEGIN PROLOGUE  CUNIK */
/* ***REFER TO  CBESI,CBESK */

/*        CUNIK COMPUTES PARAMETERS FOR THE UNIFORM ASYMPTOTIC */
/*        EXPANSIONS OF THE I AND K FUNCTIONS ON IKFLG= 1 OR 2 */
/*        RESPECTIVELY BY */

/*        W(FNU,ZR) = PHI*EXP(ZETA)*SUM */

/*        WHERE       ZETA=-ZETA1 + ZETA2       OR */
/*                          ZETA1 - ZETA2 */

/*        THE FIRST CALL MUST HAVE INIT=0. SUBSEQUENT CALLS WITH THE */
/*        SAME ZR AND FNU WILL RETURN THE I OR K FUNCTION ON IKFLG= */
/*        1 OR 2 WITH NO CHANGE IN INIT. CWRK IS A COMPLEX WORK */
/*        ARRAY. IPMTR=0 COMPUTES ALL PARAMETERS. IPMTR=1 COMPUTES PHI, */
/*        ZETA1,ZETA2. */

/* ***ROUTINES CALLED  (NONE) */
/* ***END PROLOGUE  CUNIK */
    /* Parameter adjustments */
    --cwrk;

    /* Function Body */

    if (*init != 0) {
	goto L40;
    }
/* ----------------------------------------------------------------------- */
/*     INITIALIZE ALL VARIABLES */
/* ----------------------------------------------------------------------- */
    rfn = (float)1. / *fnu;
    q__1.r = rfn, q__1.i = (float)0.;
    crfn.r = q__1.r, crfn.i = q__1.i;
/*     T = ZR*CRFN */
/* ----------------------------------------------------------------------- */
/*     OVERFLOW TEST (ZR/FNU TOO SMALL) */
/* ----------------------------------------------------------------------- */
    tstr = zr->r;
    tsti = r_imag(zr);
    test = r1mach_(&c__1) * (float)1e3;
    ac = *fnu * test;
    if (dabs(tstr) > ac || dabs(tsti) > ac) {
	goto L15;
    }
    ac = (r__1 = log(test), dabs(r__1)) * (float)2. + *fnu;
    q__1.r = ac, q__1.i = (float)0.;
    zeta1->r = q__1.r, zeta1->i = q__1.i;
    q__1.r = *fnu, q__1.i = (float)0.;
    zeta2->r = q__1.r, zeta2->i = q__1.i;
    phi->r = cone.r, phi->i = cone.i;
    return 0;
L15:
    q__1.r = zr->r * crfn.r - zr->i * crfn.i, q__1.i = zr->r * crfn.i + zr->i 
	    * crfn.r;
    t.r = q__1.r, t.i = q__1.i;
    q__2.r = t.r * t.r - t.i * t.i, q__2.i = t.r * t.i + t.i * t.r;
    q__1.r = cone.r + q__2.r, q__1.i = cone.i + q__2.i;
    s.r = q__1.r, s.i = q__1.i;
    c_sqrt(&q__1, &s);
    sr.r = q__1.r, sr.i = q__1.i;
    q__1.r = *fnu, q__1.i = (float)0.;
    cfn.r = q__1.r, cfn.i = q__1.i;
    q__2.r = cone.r + sr.r, q__2.i = cone.i + sr.i;
    c_div(&q__1, &q__2, &t);
    zn.r = q__1.r, zn.i = q__1.i;
    c_log(&q__2, &zn);
    q__1.r = cfn.r * q__2.r - cfn.i * q__2.i, q__1.i = cfn.r * q__2.i + cfn.i 
	    * q__2.r;
    zeta1->r = q__1.r, zeta1->i = q__1.i;
    q__1.r = cfn.r * sr.r - cfn.i * sr.i, q__1.i = cfn.r * sr.i + cfn.i * 
	    sr.r;
    zeta2->r = q__1.r, zeta2->i = q__1.i;
    c_div(&q__1, &cone, &sr);
    t.r = q__1.r, t.i = q__1.i;
    q__1.r = t.r * crfn.r - t.i * crfn.i, q__1.i = t.r * crfn.i + t.i * 
	    crfn.r;
    sr.r = q__1.r, sr.i = q__1.i;
    c_sqrt(&q__1, &sr);
    cwrk[16].r = q__1.r, cwrk[16].i = q__1.i;
    i__1 = *ikflg - 1;
    q__1.r = cwrk[16].r * con[i__1].r - cwrk[16].i * con[i__1].i, q__1.i = 
	    cwrk[16].r * con[i__1].i + cwrk[16].i * con[i__1].r;
    phi->r = q__1.r, phi->i = q__1.i;
    if (*ipmtr != 0) {
	return 0;
    }
    c_div(&q__1, &cone, &s);
    t2.r = q__1.r, t2.i = q__1.i;
    cwrk[1].r = cone.r, cwrk[1].i = cone.i;
    crfn.r = cone.r, crfn.i = cone.i;
    ac = (float)1.;
    l = 1;
    for (k = 2; k <= 15; ++k) {
	s.r = czero.r, s.i = czero.i;
	i__1 = k;
	for (j = 1; j <= i__1; ++j) {
	    ++l;
	    q__2.r = s.r * t2.r - s.i * t2.i, q__2.i = s.r * t2.i + s.i * 
		    t2.r;
	    i__2 = l - 1;
	    q__3.r = c__[i__2], q__3.i = (float)0.;
	    q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
	    s.r = q__1.r, s.i = q__1.i;
/* L10: */
	}
	q__1.r = crfn.r * sr.r - crfn.i * sr.i, q__1.i = crfn.r * sr.i + 
		crfn.i * sr.r;
	crfn.r = q__1.r, crfn.i = q__1.i;
	i__1 = k;
	q__1.r = crfn.r * s.r - crfn.i * s.i, q__1.i = crfn.r * s.i + crfn.i *
		 s.r;
	cwrk[i__1].r = q__1.r, cwrk[i__1].i = q__1.i;
	ac *= rfn;
	i__1 = k;
	tstr = cwrk[i__1].r;
	tsti = r_imag(&cwrk[k]);
	test = dabs(tstr) + dabs(tsti);
	if (ac < *tol && test < *tol) {
	    goto L30;
	}
/* L20: */
    }
    k = 15;
L30:
    *init = k;
L40:
    if (*ikflg == 2) {
	goto L60;
    }
/* ----------------------------------------------------------------------- */
/*     COMPUTE SUM FOR THE I FUNCTION */
/* ----------------------------------------------------------------------- */
    s.r = czero.r, s.i = czero.i;
    i__1 = *init;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	q__1.r = s.r + cwrk[i__2].r, q__1.i = s.i + cwrk[i__2].i;
	s.r = q__1.r, s.i = q__1.i;
/* L50: */
    }
    sum->r = s.r, sum->i = s.i;
    q__1.r = cwrk[16].r * con[0].r - cwrk[16].i * con[0].i, q__1.i = cwrk[16]
	    .r * con[0].i + cwrk[16].i * con[0].r;
    phi->r = q__1.r, phi->i = q__1.i;
    return 0;
L60:
/* ----------------------------------------------------------------------- */
/*     COMPUTE SUM FOR THE K FUNCTION */
/* ----------------------------------------------------------------------- */
    s.r = czero.r, s.i = czero.i;
    t.r = cone.r, t.i = cone.i;
    i__1 = *init;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	q__2.r = t.r * cwrk[i__2].r - t.i * cwrk[i__2].i, q__2.i = t.r * cwrk[
		i__2].i + t.i * cwrk[i__2].r;
	q__1.r = s.r + q__2.r, q__1.i = s.i + q__2.i;
	s.r = q__1.r, s.i = q__1.i;
	q__1.r = -t.r, q__1.i = -t.i;
	t.r = q__1.r, t.i = q__1.i;
/* L70: */
    }
    sum->r = s.r, sum->i = s.i;
    q__1.r = cwrk[16].r * con[1].r - cwrk[16].i * con[1].i, q__1.i = cwrk[16]
	    .r * con[1].i + cwrk[16].i * con[1].r;
    phi->r = q__1.r, phi->i = q__1.i;
    return 0;
} /* cunik_ */

#ifdef __cplusplus
	}
#endif
