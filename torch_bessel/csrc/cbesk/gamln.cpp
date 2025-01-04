/* fortran/cbesk/gamln.f -- translated by f2c (version 20240504).
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
static integer c__11 = 11;
static integer c__5 = 5;

doublereal gamln_(real *z__, integer *ierr)
{
    /* Initialized data */

    static real gln[100] = { (float)0.,(float)0.,(float).693147180559945309,(
	    float)1.791759469228055,(float)3.17805383034794562,(float)
	    4.78749174278204599,(float)6.579251212010101,(float)
	    8.5251613610654143,(float)10.6046029027452502,(float)
	    12.8018274800814696,(float)15.1044125730755153,(float)
	    17.5023078458738858,(float)19.9872144956618861,(float)
	    22.5521638531234229,(float)25.1912211827386815,(float)
	    27.8992713838408916,(float)30.6718601060806728,(float)
	    33.5050734501368889,(float)36.3954452080330536,(float)
	    39.339884187199494,(float)42.335616460753485,(float)
	    45.380138898476908,(float)48.4711813518352239,(float)
	    51.6066755677643736,(float)54.7847293981123192,(float)
	    58.0036052229805199,(float)61.261701761002002,(float)
	    64.5575386270063311,(float)67.889743137181535,(float)
	    71.257038967168009,(float)74.6582363488301644,(float)
	    78.0922235533153106,(float)81.5579594561150372,(float)
	    85.0544670175815174,(float)88.5808275421976788,(float)
	    92.1361756036870925,(float)95.7196945421432025,(float)
	    99.3306124547874269,(float)102.968198614513813,(float)
	    106.631760260643459,(float)110.320639714757395,(float)
	    114.034211781461703,(float)117.771881399745072,(float)
	    121.533081515438634,(float)125.317271149356895,(float)
	    129.123933639127215,(float)132.95257503561631,(float)
	    136.802722637326368,(float)140.673923648234259,(float)
	    144.565743946344886,(float)148.477766951773032,(float)
	    152.409592584497358,(float)156.360836303078785,(float)
	    160.331128216630907,(float)164.320112263195181,(float)
	    168.327445448427652,(float)172.352797139162802,(float)
	    176.395848406997352,(float)180.456291417543771,(float)
	    184.533828861449491,(float)188.628173423671591,(float)
	    192.739047287844902,(float)196.866181672889994,(float)
	    201.009316399281527,(float)205.168199482641199,(float)
	    209.342586752536836,(float)213.532241494563261,(float)
	    217.736934113954227,(float)221.956441819130334,(float)
	    226.190548323727593,(float)230.439043565776952,(float)
	    234.701723442818268,(float)238.978389561834323,(float)
	    243.268849002982714,(float)247.572914096186884,(float)
	    251.890402209723194,(float)256.221135550009525,(float)
	    260.564940971863209,(float)264.921649798552801,(float)
	    269.291097651019823,(float)273.673124285693704,(float)
	    278.067573440366143,(float)282.474292687630396,(float)
	    286.893133295426994,(float)291.323950094270308,(float)
	    295.766601350760624,(float)300.220948647014132,(float)
	    304.686856765668715,(float)309.164193580146922,(float)
	    313.652829949879062,(float)318.152639620209327,(float)
	    322.663499126726177,(float)327.185287703775217,(float)
	    331.717887196928473,(float)336.261181979198477,(float)
	    340.815058870799018,(float)345.379407062266854,(float)
	    349.954118040770237,(float)354.539085519440809,(float)
	    359.134205369575399 };
    static real cf[22] = { (float).0833333333333333333,(float)
	    -.00277777777777777778,(float)7.93650793650793651e-4,(float)
	    -5.95238095238095238e-4,(float)8.41750841750841751e-4,(float)
	    -.00191752691752691753,(float).00641025641025641026,(float)
	    -.0295506535947712418,(float).179644372368830573,(float)
	    -1.39243221690590112,(float)13.402864044168392,(float)
	    -156.848284626002017,(float)2193.10333333333333,(float)
	    -36108.7712537249894,(float)691472.268851313067,(float)
	    -15238221.5394074162,(float)382900751.391414141,(float)
	    -10882266035.7843911,(float)347320283765.002252,(float)
	    -12369602142269.2745,(float)488788064793079.335,(float)
	    -21320333960919373.9 };
    static real con = (float)1.83787706640934548;

    /* System generated locals */
    integer i__1;
    real ret_val;

    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    static integer i__, k;
    static real s, t1, fz;
    static integer mz, nz;
    static real zm, zp;
    static integer i1m;
    static real fln, tlg, rln, trm, tst, zsq, zinc, zmin, zdmy, wdtol;
    extern integer i1mach_(integer *);
    extern doublereal r1mach_(integer *);

/* ***BEGIN PROLOGUE  GAMLN */
/* ***DATE WRITTEN   830501   (YYMMDD) */
/* ***REVISION DATE  830501   (YYMMDD) */
/* ***CATEGORY NO.  B5F */
/* ***KEYWORDS  GAMMA FUNCTION,LOGARITHM OF GAMMA FUNCTION */
/* ***AUTHOR  AMOS, DONALD E., SANDIA NATIONAL LABORATORIES */
/* ***PURPOSE  TO COMPUTE THE LOGARITHM OF THE GAMMA FUNCTION */
/* ***DESCRIPTION */

/*         GAMLN COMPUTES THE NATURAL LOG OF THE GAMMA FUNCTION FOR */
/*         Z.GT.0.  THE ASYMPTOTIC EXPANSION IS USED TO GENERATE VALUES */
/*         GREATER THAN ZMIN WHICH ARE ADJUSTED BY THE RECURSION */
/*         G(Z+1)=Z*G(Z) FOR Z.LE.ZMIN.  THE FUNCTION WAS MADE AS */
/*         PORTABLE AS POSSIBLE BY COMPUTIMG ZMIN FROM THE NUMBER OF BASE */
/*         10 DIGITS IN A WORD, RLN=AMAX1(-ALOG10(R1MACH(4)),0.5E-18) */
/*         LIMITED TO 18 DIGITS OF (RELATIVE) ACCURACY. */

/*         SINCE INTEGER ARGUMENTS ARE COMMON, A TABLE LOOK UP ON 100 */
/*         VALUES IS USED FOR SPEED OF EXECUTION. */

/*     DESCRIPTION OF ARGUMENTS */

/*         INPUT */
/*           Z      - REAL ARGUMENT, Z.GT.0.0E0 */

/*         OUTPUT */
/*           GAMLN  - NATURAL LOG OF THE GAMMA FUNCTION AT Z */
/*           IERR   - ERROR FLAG */
/*                    IERR=0, NORMAL RETURN, COMPUTATION COMPLETED */
/*                    IERR=1, Z.LE.0.0E0,    NO COMPUTATION */

/* ***REFERENCES  COMPUTATION OF BESSEL FUNCTIONS OF COMPLEX ARGUMENT */
/*                 BY D. E. AMOS, SAND83-0083, MAY, 1983. */
/* ***ROUTINES CALLED  I1MACH,R1MACH */
/* ***END PROLOGUE  GAMLN */

/*           LNGAMMA(N), N=1,100 */
/*             COEFFICIENTS OF ASYMPTOTIC EXPANSION */

/*             LN(2*PI) */

/* ***FIRST EXECUTABLE STATEMENT  GAMLN */
    *ierr = 0;
    if (*z__ <= (float)0.) {
	goto L70;
    }
    if (*z__ > (float)101.) {
	goto L10;
    }
    nz = (integer) (*z__);
    fz = *z__ - (real) nz;
    if (fz > (float)0.) {
	goto L10;
    }
    if (nz > 100) {
	goto L10;
    }
    ret_val = gln[nz - 1];
    return ret_val;
L10:
    wdtol = r1mach_(&c__4);
    wdtol = dmax(wdtol,(float)5e-19);
    i1m = i1mach_(&c__11);
    rln = r1mach_(&c__5) * (real) i1m;
    fln = dmin(rln,(float)20.);
    fln = dmax(fln,(float)3.);
    fln += (float)-3.;
    zm = fln * (float).3875 + (float)1.8;
    mz = (integer) zm + 1;
    zmin = (real) mz;
    zdmy = *z__;
    zinc = (float)0.;
    if (*z__ >= zmin) {
	goto L20;
    }
    zinc = zmin - (real) nz;
    zdmy = *z__ + zinc;
L20:
    zp = (float)1. / zdmy;
    t1 = cf[0] * zp;
    s = t1;
    if (zp < wdtol) {
	goto L40;
    }
    zsq = zp * zp;
    tst = t1 * wdtol;
    for (k = 2; k <= 22; ++k) {
	zp *= zsq;
	trm = cf[k - 1] * zp;
	if (dabs(trm) < tst) {
	    goto L40;
	}
	s += trm;
/* L30: */
    }
L40:
    if (zinc != (float)0.) {
	goto L50;
    }
    tlg = log(*z__);
    ret_val = *z__ * (tlg - (float)1.) + (con - tlg) * (float).5 + s;
    return ret_val;
L50:
    zp = (float)1.;
    nz = (integer) zinc;
    i__1 = nz;
    for (i__ = 1; i__ <= i__1; ++i__) {
	zp *= *z__ + (real) (i__ - 1);
/* L60: */
    }
    tlg = log(zdmy);
    ret_val = zdmy * (tlg - (float)1.) - log(zp) + (con - tlg) * (float).5 + 
	    s;
    return ret_val;


L70:
    *ierr = 1;
    return ret_val;
} /* gamln_ */

#ifdef __cplusplus
	}
#endif
