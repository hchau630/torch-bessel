/* fortran/cbesk/cairy.f -- translated by f2c (version 20240504).
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

static integer c__4 = 4;
static integer c__12 = 12;
static integer c__13 = 13;
static integer c__5 = 5;
static integer c__11 = 11;
static integer c__9 = 9;
static integer c__1 = 1;

/* Subroutine */ int cairy_(complex *z__, integer *id, integer *kode, complex 
	*ai, integer *nz, integer *ierr)
{
    /* Initialized data */

    static real tth = (float).666666666666666667;
    static real c1 = (float).35502805388781724;
    static real c2 = (float).258819403792806799;
    static real coef = (float).183776298473930683;
    static complex cone = {(float)1.,(float)0.};

    /* System generated locals */
    integer i__1, i__2;
    real r__1, r__2;
    doublereal d__1, d__2;
    complex q__1, q__2, q__3, q__4, q__5, q__6;

    /* Builtin functions */
    double c_abs(complex *), r_imag(complex *);
    void c_sqrt(complex *, complex *), c_exp(complex *, complex *);
    double log(doublereal), pow_dd(doublereal *, doublereal *), sqrt(
	    doublereal);

    /* Local variables */
    static integer k;
    static real d1, d2;
    static integer k1, k2;
    static complex s1, s2, z3;
    static real aa, bb, ad, ak, bk, ck, dk, az;
    static complex cy[1];
    static integer nn;
    static real rl;
    static integer mr;
    static real zi, zr, az3, z3i, z3r, fid, dig, r1m5;
    static complex csq;
    static real fnu;
    static complex zta;
    static real tol;
    static complex trm1, trm2;
    static real sfac, alim, elim, alaz, atrm;
    extern /* Subroutine */ int cacai_(complex *, real *, integer *, integer *
	    , integer *, complex *, integer *, real *, real *, real *, real *)
	    ;
    static integer iflag;
    extern /* Subroutine */ int cbknu_(complex *, real *, integer *, integer *
	    , complex *, integer *, real *, real *, real *);
    extern integer i1mach_(integer *);
    extern doublereal r1mach_(integer *);

/* ***BEGIN PROLOGUE  CAIRY */
/* ***DATE WRITTEN   830501   (YYMMDD) */
/* ***REVISION DATE  890801   (YYMMDD) */
/* ***CATEGORY NO.  B5K */
/* ***KEYWORDS  AIRY FUNCTION,BESSEL FUNCTIONS OF ORDER ONE THIRD */
/* ***AUTHOR  AMOS, DONALD E., SANDIA NATIONAL LABORATORIES */
/* ***PURPOSE  TO COMPUTE AIRY FUNCTIONS AI(Z) AND DAI(Z) FOR COMPLEX Z */
/* ***DESCRIPTION */

/*         ON KODE=1, CAIRY COMPUTES THE COMPLEX AIRY FUNCTION AI(Z) OR */
/*         ITS DERIVATIVE DAI(Z)/DZ ON ID=0 OR ID=1 RESPECTIVELY. ON */
/*         KODE=2, A SCALING OPTION CEXP(ZTA)*AI(Z) OR CEXP(ZTA)* */
/*         DAI(Z)/DZ IS PROVIDED TO REMOVE THE EXPONENTIAL DECAY IN */
/*         -PI/3.LT.ARG(Z).LT.PI/3 AND THE EXPONENTIAL GROWTH IN */
/*         PI/3.LT.ABS(ARG(Z)).LT.PI WHERE ZTA=(2/3)*Z*CSQRT(Z) */

/*         WHILE THE AIRY FUNCTIONS AI(Z) AND DAI(Z)/DZ ARE ANALYTIC IN */
/*         THE WHOLE Z PLANE, THE CORRESPONDING SCALED FUNCTIONS DEFINED */
/*         FOR KODE=2 HAVE A CUT ALONG THE NEGATIVE REAL AXIS. */
/*         DEFINITIONS AND NOTATION ARE FOUND IN THE NBS HANDBOOK OF */
/*         MATHEMATICAL FUNCTIONS (REF. 1). */

/*         INPUT */
/*           Z      - Z=CMPLX(X,Y) */
/*           ID     - ORDER OF DERIVATIVE, ID=0 OR ID=1 */
/*           KODE   - A PARAMETER TO INDICATE THE SCALING OPTION */
/*                    KODE= 1  RETURNS */
/*                             AI=AI(Z)                ON ID=0 OR */
/*                             AI=DAI(Z)/DZ            ON ID=1 */
/*                        = 2  RETURNS */
/*                             AI=CEXP(ZTA)*AI(Z)       ON ID=0 OR */
/*                             AI=CEXP(ZTA)*DAI(Z)/DZ   ON ID=1 WHERE */
/*                             ZTA=(2/3)*Z*CSQRT(Z) */

/*         OUTPUT */
/*           AI     - COMPLEX ANSWER DEPENDING ON THE CHOICES FOR ID AND */
/*                    KODE */
/*           NZ     - UNDERFLOW INDICATOR */
/*                    NZ= 0   , NORMAL RETURN */
/*                    NZ= 1   , AI=CMPLX(0.0,0.0) DUE TO UNDERFLOW IN */
/*                              -PI/3.LT.ARG(Z).LT.PI/3 ON KODE=1 */
/*           IERR   - ERROR FLAG */
/*                    IERR=0, NORMAL RETURN - COMPUTATION COMPLETED */
/*                    IERR=1, INPUT ERROR   - NO COMPUTATION */
/*                    IERR=2, OVERFLOW      - NO COMPUTATION, REAL(ZTA) */
/*                            TOO LARGE WITH KODE=1. */
/*                    IERR=3, CABS(Z) LARGE      - COMPUTATION COMPLETED */
/*                            LOSSES OF SIGNIFCANCE BY ARGUMENT REDUCTION */
/*                            PRODUCE LESS THAN HALF OF MACHINE ACCURACY */
/*                    IERR=4, CABS(Z) TOO LARGE  - NO COMPUTATION */
/*                            COMPLETE LOSS OF ACCURACY BY ARGUMENT */
/*                            REDUCTION */
/*                    IERR=5, ERROR              - NO COMPUTATION, */
/*                            ALGORITHM TERMINATION CONDITION NOT MET */


/* ***LONG DESCRIPTION */

/*         AI AND DAI ARE COMPUTED FOR CABS(Z).GT.1.0 FROM THE K BESSEL */
/*         FUNCTIONS BY */

/*            AI(Z)=C*SQRT(Z)*K(1/3,ZTA) , DAI(Z)=-C*Z*K(2/3,ZTA) */
/*                           C=1.0/(PI*SQRT(3.0)) */
/*                           ZTA=(2/3)*Z**(3/2) */

/*         WITH THE POWER SERIES FOR CABS(Z).LE.1.0. */

/*         IN MOST COMPLEX VARIABLE COMPUTATION, ONE MUST EVALUATE ELE- */
/*         MENTARY FUNCTIONS. WHEN THE MAGNITUDE OF Z IS LARGE, LOSSES */
/*         OF SIGNIFICANCE BY ARGUMENT REDUCTION OCCUR. CONSEQUENTLY, IF */
/*         THE MAGNITUDE OF ZETA=(2/3)*Z**1.5 EXCEEDS U1=SQRT(0.5/UR), */
/*         THEN LOSSES EXCEEDING HALF PRECISION ARE LIKELY AND AN ERROR */
/*         FLAG IERR=3 IS TRIGGERED WHERE UR=R1MACH(4)=UNIT ROUNDOFF. */
/*         ALSO, IF THE MAGNITUDE OF ZETA IS LARGER THAN U2=0.5/UR, THEN */
/*         ALL SIGNIFICANCE IS LOST AND IERR=4. IN ORDER TO USE THE INT */
/*         FUNCTION, ZETA MUST BE FURTHER RESTRICTED NOT TO EXCEED THE */
/*         LARGEST INTEGER, U3=I1MACH(9). THUS, THE MAGNITUDE OF ZETA */
/*         MUST BE RESTRICTED BY MIN(U2,U3). ON 32 BIT MACHINES, U1,U2, */
/*         AND U3 ARE APPROXIMATELY 2.0E+3, 4.2E+6, 2.1E+9 IN SINGLE */
/*         PRECISION ARITHMETIC AND 1.3E+8, 1.8E+16, 2.1E+9 IN DOUBLE */
/*         PRECISION ARITHMETIC RESPECTIVELY. THIS MAKES U2 AND U3 LIMIT- */
/*         ING IN THEIR RESPECTIVE ARITHMETICS. THIS MEANS THAT THE MAG- */
/*         NITUDE OF Z CANNOT EXCEED 3.1E+4 IN SINGLE AND 2.1E+6 IN */
/*         DOUBLE PRECISION ARITHMETIC. THIS ALSO MEANS THAT ONE CAN */
/*         EXPECT TO RETAIN, IN THE WORST CASES ON 32 BIT MACHINES, */
/*         NO DIGITS IN SINGLE PRECISION AND ONLY 7 DIGITS IN DOUBLE */
/*         PRECISION ARITHMETIC. SIMILAR CONSIDERATIONS HOLD FOR OTHER */
/*         MACHINES. */

/*         THE APPROXIMATE RELATIVE ERROR IN THE MAGNITUDE OF A COMPLEX */
/*         BESSEL FUNCTION CAN BE EXPRESSED BY P*10**S WHERE P=MAX(UNIT */
/*         ROUNDOFF,1.0E-18) IS THE NOMINAL PRECISION AND 10**S REPRE- */
/*         SENTS THE INCREASE IN ERROR DUE TO ARGUMENT REDUCTION IN THE */
/*         ELEMENTARY FUNCTIONS. HERE, S=MAX(1,ABS(LOG10(CABS(Z))), */
/*         ABS(LOG10(FNU))) APPROXIMATELY (I.E. S=MAX(1,ABS(EXPONENT OF */
/*         CABS(Z),ABS(EXPONENT OF FNU)) ). HOWEVER, THE PHASE ANGLE MAY */
/*         HAVE ONLY ABSOLUTE ACCURACY. THIS IS MOST LIKELY TO OCCUR WHEN */
/*         ONE COMPONENT (IN ABSOLUTE VALUE) IS LARGER THAN THE OTHER BY */
/*         SEVERAL ORDERS OF MAGNITUDE. IF ONE COMPONENT IS 10**K LARGER */
/*         THAN THE OTHER, THEN ONE CAN EXPECT ONLY MAX(ABS(LOG10(P))-K, */
/*         0) SIGNIFICANT DIGITS; OR, STATED ANOTHER WAY, WHEN K EXCEEDS */
/*         THE EXPONENT OF P, NO SIGNIFICANT DIGITS REMAIN IN THE SMALLER */
/*         COMPONENT. HOWEVER, THE PHASE ANGLE RETAINS ABSOLUTE ACCURACY */
/*         BECAUSE, IN COMPLEX ARITHMETIC WITH PRECISION P, THE SMALLER */
/*         COMPONENT WILL NOT (AS A RULE) DECREASE BELOW P TIMES THE */
/*         MAGNITUDE OF THE LARGER COMPONENT. IN THESE EXTREME CASES, */
/*         THE PRINCIPAL PHASE ANGLE IS ON THE ORDER OF +P, -P, PI/2-P, */
/*         OR -PI/2+P. */

/* ***REFERENCES  HANDBOOK OF MATHEMATICAL FUNCTIONS BY M. ABRAMOWITZ */
/*                 AND I. A. STEGUN, NBS AMS SERIES 55, U.S. DEPT. OF */
/*                 COMMERCE, 1955. */

/*               COMPUTATION OF BESSEL FUNCTIONS OF COMPLEX ARGUMENT */
/*                 AND LARGE ORDER BY D. E. AMOS, SAND83-0643, MAY, 1983 */

/*               A SUBROUTINE PACKAGE FOR BESSEL FUNCTIONS OF A COMPLEX */
/*                 ARGUMENT AND NONNEGATIVE ORDER BY D. E. AMOS, SAND85- */
/*                 1018, MAY, 1985 */

/*               A PORTABLE PACKAGE FOR BESSEL FUNCTIONS OF A COMPLEX */
/*                 ARGUMENT AND NONNEGATIVE ORDER BY D. E. AMOS, TRANS. */
/*                 MATH. SOFTWARE, 1986 */

/* ***ROUTINES CALLED  CACAI,CBKNU,I1MACH,R1MACH */
/* ***END PROLOGUE  CAIRY */
/* ***FIRST EXECUTABLE STATEMENT  CAIRY */
    *ierr = 0;
    *nz = 0;
    if (*id < 0 || *id > 1) {
	*ierr = 1;
    }
    if (*kode < 1 || *kode > 2) {
	*ierr = 1;
    }
    if (*ierr != 0) {
	return 0;
    }
    az = c_abs(z__);
/* Computing MAX */
    r__1 = r1mach_(&c__4);
    tol = dmax(r__1,(float)1e-18);
    fid = (real) (*id);
    if (az > (float)1.) {
	goto L60;
    }
/* ----------------------------------------------------------------------- */
/*     POWER SERIES FOR CABS(Z).LE.1. */
/* ----------------------------------------------------------------------- */
    s1.r = cone.r, s1.i = cone.i;
    s2.r = cone.r, s2.i = cone.i;
    if (az < tol) {
	goto L160;
    }
    aa = az * az;
    if (aa < tol / az) {
	goto L40;
    }
    trm1.r = cone.r, trm1.i = cone.i;
    trm2.r = cone.r, trm2.i = cone.i;
    atrm = (float)1.;
    q__2.r = z__->r * z__->r - z__->i * z__->i, q__2.i = z__->r * z__->i + 
	    z__->i * z__->r;
    q__1.r = q__2.r * z__->r - q__2.i * z__->i, q__1.i = q__2.r * z__->i + 
	    q__2.i * z__->r;
    z3.r = q__1.r, z3.i = q__1.i;
    az3 = az * aa;
    ak = fid + (float)2.;
    bk = (float)3. - fid - fid;
    ck = (float)4. - fid;
    dk = fid + (float)3. + fid;
    d1 = ak * dk;
    d2 = bk * ck;
    ad = dmin(d1,d2);
    ak = fid * (float)9. + (float)24.;
    bk = (float)30. - fid * (float)9.;
    z3r = z3.r;
    z3i = r_imag(&z3);
    for (k = 1; k <= 25; ++k) {
	r__1 = z3r / d1;
	r__2 = z3i / d1;
	q__2.r = r__1, q__2.i = r__2;
	q__1.r = trm1.r * q__2.r - trm1.i * q__2.i, q__1.i = trm1.r * q__2.i 
		+ trm1.i * q__2.r;
	trm1.r = q__1.r, trm1.i = q__1.i;
	q__1.r = s1.r + trm1.r, q__1.i = s1.i + trm1.i;
	s1.r = q__1.r, s1.i = q__1.i;
	r__1 = z3r / d2;
	r__2 = z3i / d2;
	q__2.r = r__1, q__2.i = r__2;
	q__1.r = trm2.r * q__2.r - trm2.i * q__2.i, q__1.i = trm2.r * q__2.i 
		+ trm2.i * q__2.r;
	trm2.r = q__1.r, trm2.i = q__1.i;
	q__1.r = s2.r + trm2.r, q__1.i = s2.i + trm2.i;
	s2.r = q__1.r, s2.i = q__1.i;
	atrm = atrm * az3 / ad;
	d1 += ak;
	d2 += bk;
	ad = dmin(d1,d2);
	if (atrm < tol * ad) {
	    goto L40;
	}
	ak += (float)18.;
	bk += (float)18.;
/* L30: */
    }
L40:
    if (*id == 1) {
	goto L50;
    }
    q__3.r = c1, q__3.i = (float)0.;
    q__2.r = s1.r * q__3.r - s1.i * q__3.i, q__2.i = s1.r * q__3.i + s1.i * 
	    q__3.r;
    q__5.r = z__->r * s2.r - z__->i * s2.i, q__5.i = z__->r * s2.i + z__->i * 
	    s2.r;
    q__6.r = c2, q__6.i = (float)0.;
    q__4.r = q__5.r * q__6.r - q__5.i * q__6.i, q__4.i = q__5.r * q__6.i + 
	    q__5.i * q__6.r;
    q__1.r = q__2.r - q__4.r, q__1.i = q__2.i - q__4.i;
    ai->r = q__1.r, ai->i = q__1.i;
    if (*kode == 1) {
	return 0;
    }
    c_sqrt(&q__3, z__);
    q__2.r = z__->r * q__3.r - z__->i * q__3.i, q__2.i = z__->r * q__3.i + 
	    z__->i * q__3.r;
    q__4.r = tth, q__4.i = (float)0.;
    q__1.r = q__2.r * q__4.r - q__2.i * q__4.i, q__1.i = q__2.r * q__4.i + 
	    q__2.i * q__4.r;
    zta.r = q__1.r, zta.i = q__1.i;
    c_exp(&q__2, &zta);
    q__1.r = ai->r * q__2.r - ai->i * q__2.i, q__1.i = ai->r * q__2.i + ai->i 
	    * q__2.r;
    ai->r = q__1.r, ai->i = q__1.i;
    return 0;
L50:
    q__2.r = -s2.r, q__2.i = -s2.i;
    q__3.r = c2, q__3.i = (float)0.;
    q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i + 
	    q__2.i * q__3.r;
    ai->r = q__1.r, ai->i = q__1.i;
    if (az > tol) {
	q__4.r = z__->r * z__->r - z__->i * z__->i, q__4.i = z__->r * z__->i 
		+ z__->i * z__->r;
	q__3.r = q__4.r * s1.r - q__4.i * s1.i, q__3.i = q__4.r * s1.i + 
		q__4.i * s1.r;
	r__1 = c1 / (fid + (float)1.);
	q__5.r = r__1, q__5.i = (float)0.;
	q__2.r = q__3.r * q__5.r - q__3.i * q__5.i, q__2.i = q__3.r * q__5.i 
		+ q__3.i * q__5.r;
	q__1.r = ai->r + q__2.r, q__1.i = ai->i + q__2.i;
	ai->r = q__1.r, ai->i = q__1.i;
    }
    if (*kode == 1) {
	return 0;
    }
    c_sqrt(&q__3, z__);
    q__2.r = z__->r * q__3.r - z__->i * q__3.i, q__2.i = z__->r * q__3.i + 
	    z__->i * q__3.r;
    q__4.r = tth, q__4.i = (float)0.;
    q__1.r = q__2.r * q__4.r - q__2.i * q__4.i, q__1.i = q__2.r * q__4.i + 
	    q__2.i * q__4.r;
    zta.r = q__1.r, zta.i = q__1.i;
    c_exp(&q__2, &zta);
    q__1.r = ai->r * q__2.r - ai->i * q__2.i, q__1.i = ai->r * q__2.i + ai->i 
	    * q__2.r;
    ai->r = q__1.r, ai->i = q__1.i;
    return 0;
/* ----------------------------------------------------------------------- */
/*     CASE FOR CABS(Z).GT.1.0 */
/* ----------------------------------------------------------------------- */
L60:
    fnu = (fid + (float)1.) / (float)3.;
/* ----------------------------------------------------------------------- */
/*     SET PARAMETERS RELATED TO MACHINE CONSTANTS. */
/*     TOL IS THE APPROXIMATE UNIT ROUNDOFF LIMITED TO 1.0E-18. */
/*     ELIM IS THE APPROXIMATE EXPONENTIAL OVER- AND UNDERFLOW LIMIT. */
/*     EXP(-ELIM).LT.EXP(-ALIM)=EXP(-ELIM)/TOL    AND */
/*     EXP(ELIM).GT.EXP(ALIM)=EXP(ELIM)*TOL       ARE INTERVALS NEAR */
/*     UNDERFLOW AND OVERFLOW LIMITS WHERE SCALED ARITHMETIC IS DONE. */
/*     RL IS THE LOWER BOUNDARY OF THE ASYMPTOTIC EXPANSION FOR LARGE Z. */
/*     DIG = NUMBER OF BASE 10 DIGITS IN TOL = 10**(-DIG). */
/* ----------------------------------------------------------------------- */
    k1 = i1mach_(&c__12);
    k2 = i1mach_(&c__13);
    r1m5 = r1mach_(&c__5);
/* Computing MIN */
    i__1 = abs(k1), i__2 = abs(k2);
    k = min(i__1,i__2);
    elim = ((real) k * r1m5 - (float)3.) * (float)2.303;
    k1 = i1mach_(&c__11) - 1;
    aa = r1m5 * (real) k1;
    dig = dmin(aa,(float)18.);
    aa *= (float)2.303;
/* Computing MAX */
    r__1 = -aa;
    alim = elim + dmax(r__1,(float)-41.45);
    rl = dig * (float)1.2 + (float)3.;
    alaz = log(az);
/* ----------------------------------------------------------------------- */
/*     TEST FOR RANGE */
/* ----------------------------------------------------------------------- */
    aa = (float).5 / tol;
    bb = (real) i1mach_(&c__9) * (float).5;
    aa = dmin(aa,bb);
    d__1 = (doublereal) aa;
    d__2 = (doublereal) tth;
    aa = pow_dd(&d__1, &d__2);
    if (az > aa) {
	goto L260;
    }
    aa = sqrt(aa);
    if (az > aa) {
	*ierr = 3;
    }
    c_sqrt(&q__1, z__);
    csq.r = q__1.r, csq.i = q__1.i;
    q__2.r = z__->r * csq.r - z__->i * csq.i, q__2.i = z__->r * csq.i + 
	    z__->i * csq.r;
    q__3.r = tth, q__3.i = (float)0.;
    q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i + 
	    q__2.i * q__3.r;
    zta.r = q__1.r, zta.i = q__1.i;
/* ----------------------------------------------------------------------- */
/*     RE(ZTA).LE.0 WHEN RE(Z).LT.0, ESPECIALLY WHEN IM(Z) IS SMALL */
/* ----------------------------------------------------------------------- */
    iflag = 0;
    sfac = (float)1.;
    zi = r_imag(z__);
    zr = z__->r;
    ak = r_imag(&zta);
    if (zr >= (float)0.) {
	goto L70;
    }
    bk = zta.r;
    ck = -dabs(bk);
    q__1.r = ck, q__1.i = ak;
    zta.r = q__1.r, zta.i = q__1.i;
L70:
    if (zi != (float)0.) {
	goto L80;
    }
    if (zr > (float)0.) {
	goto L80;
    }
    q__1.r = (float)0., q__1.i = ak;
    zta.r = q__1.r, zta.i = q__1.i;
L80:
    aa = zta.r;
    if (aa >= (float)0. && zr > (float)0.) {
	goto L100;
    }
    if (*kode == 2) {
	goto L90;
    }
/* ----------------------------------------------------------------------- */
/*     OVERFLOW TEST */
/* ----------------------------------------------------------------------- */
    if (aa > -alim) {
	goto L90;
    }
    aa = -aa + alaz * (float).25;
    iflag = 1;
    sfac = tol;
    if (aa > elim) {
	goto L240;
    }
L90:
/* ----------------------------------------------------------------------- */
/*     CBKNU AND CACAI RETURN EXP(ZTA)*K(FNU,ZTA) ON KODE=2 */
/* ----------------------------------------------------------------------- */
    mr = 1;
    if (zi < (float)0.) {
	mr = -1;
    }
    cacai_(&zta, &fnu, kode, &mr, &c__1, cy, &nn, &rl, &tol, &elim, &alim);
    if (nn < 0) {
	goto L250;
    }
    *nz += nn;
    goto L120;
L100:
    if (*kode == 2) {
	goto L110;
    }
/* ----------------------------------------------------------------------- */
/*     UNDERFLOW TEST */
/* ----------------------------------------------------------------------- */
    if (aa < alim) {
	goto L110;
    }
    aa = -aa - alaz * (float).25;
    iflag = 2;
    sfac = (float)1. / tol;
    if (aa < -elim) {
	goto L180;
    }
L110:
    cbknu_(&zta, &fnu, kode, &c__1, cy, nz, &tol, &elim, &alim);
L120:
    q__2.r = coef, q__2.i = (float)0.;
    q__1.r = cy[0].r * q__2.r - cy[0].i * q__2.i, q__1.i = cy[0].r * q__2.i + 
	    cy[0].i * q__2.r;
    s1.r = q__1.r, s1.i = q__1.i;
    if (iflag != 0) {
	goto L140;
    }
    if (*id == 1) {
	goto L130;
    }
    q__1.r = csq.r * s1.r - csq.i * s1.i, q__1.i = csq.r * s1.i + csq.i * 
	    s1.r;
    ai->r = q__1.r, ai->i = q__1.i;
    return 0;
L130:
    q__2.r = -z__->r, q__2.i = -z__->i;
    q__1.r = q__2.r * s1.r - q__2.i * s1.i, q__1.i = q__2.r * s1.i + q__2.i * 
	    s1.r;
    ai->r = q__1.r, ai->i = q__1.i;
    return 0;
L140:
    q__2.r = sfac, q__2.i = (float)0.;
    q__1.r = s1.r * q__2.r - s1.i * q__2.i, q__1.i = s1.r * q__2.i + s1.i * 
	    q__2.r;
    s1.r = q__1.r, s1.i = q__1.i;
    if (*id == 1) {
	goto L150;
    }
    q__1.r = s1.r * csq.r - s1.i * csq.i, q__1.i = s1.r * csq.i + s1.i * 
	    csq.r;
    s1.r = q__1.r, s1.i = q__1.i;
    r__1 = (float)1. / sfac;
    q__2.r = r__1, q__2.i = (float)0.;
    q__1.r = s1.r * q__2.r - s1.i * q__2.i, q__1.i = s1.r * q__2.i + s1.i * 
	    q__2.r;
    ai->r = q__1.r, ai->i = q__1.i;
    return 0;
L150:
    q__2.r = -s1.r, q__2.i = -s1.i;
    q__1.r = q__2.r * z__->r - q__2.i * z__->i, q__1.i = q__2.r * z__->i + 
	    q__2.i * z__->r;
    s1.r = q__1.r, s1.i = q__1.i;
    r__1 = (float)1. / sfac;
    q__2.r = r__1, q__2.i = (float)0.;
    q__1.r = s1.r * q__2.r - s1.i * q__2.i, q__1.i = s1.r * q__2.i + s1.i * 
	    q__2.r;
    ai->r = q__1.r, ai->i = q__1.i;
    return 0;
L160:
    aa = r1mach_(&c__1) * (float)1e3;
    s1.r = (float)0., s1.i = (float)0.;
    if (*id == 1) {
	goto L170;
    }
    if (az > aa) {
	q__2.r = c2, q__2.i = (float)0.;
	q__1.r = q__2.r * z__->r - q__2.i * z__->i, q__1.i = q__2.r * z__->i 
		+ q__2.i * z__->r;
	s1.r = q__1.r, s1.i = q__1.i;
    }
    q__2.r = c1, q__2.i = (float)0.;
    q__1.r = q__2.r - s1.r, q__1.i = q__2.i - s1.i;
    ai->r = q__1.r, ai->i = q__1.i;
    return 0;
L170:
    q__2.r = c2, q__2.i = (float)0.;
    q__1.r = -q__2.r, q__1.i = -q__2.i;
    ai->r = q__1.r, ai->i = q__1.i;
    aa = sqrt(aa);
    if (az > aa) {
	q__2.r = z__->r * z__->r - z__->i * z__->i, q__2.i = z__->r * z__->i 
		+ z__->i * z__->r;
	q__1.r = q__2.r * (float).5 - q__2.i * (float)0., q__1.i = q__2.r * (
		float)0. + q__2.i * (float).5;
	s1.r = q__1.r, s1.i = q__1.i;
    }
    q__3.r = c1, q__3.i = (float)0.;
    q__2.r = s1.r * q__3.r - s1.i * q__3.i, q__2.i = s1.r * q__3.i + s1.i * 
	    q__3.r;
    q__1.r = ai->r + q__2.r, q__1.i = ai->i + q__2.i;
    ai->r = q__1.r, ai->i = q__1.i;
    return 0;
L180:
    *nz = 1;
    ai->r = (float)0., ai->i = (float)0.;
    return 0;
L240:
    *nz = 0;
    *ierr = 2;
    return 0;
L250:
    if (nn == -1) {
	goto L240;
    }
    *nz = 0;
    *ierr = 5;
    return 0;
L260:
    *ierr = 4;
    *nz = 0;
    return 0;
} /* cairy_ */

#ifdef __cplusplus
	}
#endif
