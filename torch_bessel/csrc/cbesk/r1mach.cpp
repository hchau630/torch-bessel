/* fortran/cbesk/r1mach.f -- translated by f2c (version 20240504).
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

static integer c__25 = 25;
static integer c__1 = 1;
static integer c__2 = 2;

/* DECK R1MACH */
doublereal r1mach_(integer *i__)
{
    /* System generated locals */
    real ret_val;
    static real equiv_4[6];

    /* Local variables */
#define log10 ((integer *)equiv_4 + 4)
#define large ((integer *)equiv_4 + 1)
#define rmach (equiv_4)
#define small ((integer *)equiv_4)
#define diver ((integer *)equiv_4 + 3)
#define right ((integer *)equiv_4 + 2)
    extern /* Subroutine */ int xerror_(char *, integer *, integer *, integer 
	    *, ftnlen);

/* ***BEGIN PROLOGUE  R1MACH */
/* ***DATE WRITTEN   790101   (YYMMDD) */
/* ***REVISION DATE  890213   (YYMMDD) */
/* ***CATEGORY NO.  R1 */
/* ***KEYWORDS  LIBRARY=SLATEC,TYPE=SINGLE PRECISION(R1MACH-S D1MACH-D), */
/*             MACHINE CONSTANTS */
/* ***AUTHOR  FOX, P. A., (BELL LABS) */
/*           HALL, A. D., (BELL LABS) */
/*           SCHRYER, N. L., (BELL LABS) */
/* ***PURPOSE  Returns single precision machine dependent constants */
/* ***DESCRIPTION */

/*   R1MACH can be used to obtain machine-dependent parameters */
/*   for the local machine environment.  It is a function */
/*   subroutine with one (input) argument, and can be called */
/*   as follows, for example */

/*        A = R1MACH(I) */

/*   where I=1,...,5.  The (output) value of A above is */
/*   determined by the (input) value of I.  The results for */
/*   various values of I are discussed below. */

/*   Single-Precision Machine Constants */
/*   R1MACH(1) = B**(EMIN-1), the smallest positive magnitude. */
/*   R1MACH(2) = B**EMAX*(1 - B**(-T)), the largest magnitude. */
/*   R1MACH(3) = B**(-T), the smallest relative spacing. */
/*   R1MACH(4) = B**(1-T), the largest relative spacing. */
/*   R1MACH(5) = LOG10(B) */

/*   Assume single precision numbers are represented in the T-digit, */
/*   base-B form */

/*              sign (B**E)*( (X(1)/B) + ... + (X(T)/B**T) ) */

/*   where 0 .LE. X(I) .LT. B for I=1,...,T, 0 .LT. X(1), and */
/*   EMIN .LE. E .LE. EMAX. */

/*   The values of B, T, EMIN and EMAX are provided in I1MACH as */
/*   follows: */
/*   I1MACH(10) = B, the base. */
/*   I1MACH(11) = T, the number of base-B digits. */
/*   I1MACH(12) = EMIN, the smallest exponent E. */
/*   I1MACH(13) = EMAX, the largest exponent E. */

/*   To alter this function for a particular environment, */
/*   the desired set of DATA statements should be activated by */
/*   removing the C from column 1.  Also, the values of */
/*   R1MACH(1) - R1MACH(4) should be checked for consistency */
/*   with the local operating system. */

/* ***REFERENCES  FOX, P.A., HALL, A.D., SCHRYER, N.L, *FRAMEWORK FOR */
/*                 A PORTABLE LIBRARY*, ACM TRANSACTIONS ON MATHE- */
/*                 MATICAL SOFTWARE, VOL. 4, NO. 2, JUNE 1978, */
/*                 PP. 177-188. */
/* ***ROUTINES CALLED  XERROR */
/* ***END PROLOGUE  R1MACH */




/*     MACHINE CONSTANTS FOR THE AMIGA */
/*     ABSOFT FORTRAN COMPILER USING THE 68020/68881 COMPILER OPTION */

/*     DATA SMALL(1) / Z'00800000' / */
/*     DATA LARGE(1) / Z'7F7FFFFF' / */
/*     DATA RIGHT(1) / Z'33800000' / */
/*     DATA DIVER(1) / Z'34000000' / */
/*     DATA LOG10(1) / Z'3E9A209B' / */

/*     MACHINE CONSTANTS FOR THE AMIGA */
/*     ABSOFT FORTRAN COMPILER USING SOFTWARE FLOATING POINT */

/*     DATA SMALL(1) / Z'00800000' / */
/*     DATA LARGE(1) / Z'7EFFFFFF' / */
/*     DATA RIGHT(1) / Z'33800000' / */
/*     DATA DIVER(1) / Z'34000000' / */
/*     DATA LOG10(1) / Z'3E9A209B' / */

/*     MACHINE CONSTANTS FOR THE APOLLO */

/*     DATA SMALL(1) / 16#00800000 / */
/*     DATA LARGE(1) / 16#7FFFFFFF / */
/*     DATA RIGHT(1) / 16#33800000 / */
/*     DATA DIVER(1) / 16#34000000 / */
/*     DATA LOG10(1) / 16#3E9A209B / */

/*     MACHINE CONSTANTS FOR THE BURROUGHS 1700 SYSTEM */

/*     DATA RMACH(1) / Z400800000 / */
/*     DATA RMACH(2) / Z5FFFFFFFF / */
/*     DATA RMACH(3) / Z4E9800000 / */
/*     DATA RMACH(4) / Z4EA800000 / */
/*     DATA RMACH(5) / Z500E730E8 / */

/*     MACHINE CONSTANTS FOR THE BURROUGHS 5700/6700/7700 SYSTEMS */

/*     DATA RMACH(1) / O1771000000000000 / */
/*     DATA RMACH(2) / O0777777777777777 / */
/*     DATA RMACH(3) / O1311000000000000 / */
/*     DATA RMACH(4) / O1301000000000000 / */
/*     DATA RMACH(5) / O1157163034761675 / */

/*     MACHINE CONSTANTS FOR THE CDC 170/180 SERIES USING NOS/VE */

/*     DATA RMACH(1) / Z"3001800000000000" / */
/*     DATA RMACH(2) / Z"4FFEFFFFFFFFFFFE" / */
/*     DATA RMACH(3) / Z"3FD2800000000000" / */
/*     DATA RMACH(4) / Z"3FD3800000000000" / */
/*     DATA RMACH(5) / Z"3FFF9A209A84FBCF" / */

/*     MACHINE CONSTANTS FOR THE CDC 6000/7000 SERIES */

/*     DATA RMACH(1) / 00564000000000000000B / */
/*     DATA RMACH(2) / 37767777777777777776B / */
/*     DATA RMACH(3) / 16414000000000000000B / */
/*     DATA RMACH(4) / 16424000000000000000B / */
/*     DATA RMACH(5) / 17164642023241175720B / */

/*     MACHINE CONSTANTS FOR THE CELERITY C1260 */

/*     DATA SMALL(1) / Z'00800000' / */
/*     DATA LARGE(1) / Z'7F7FFFFF' / */
/*     DATA RIGHT(1) / Z'33800000' / */
/*     DATA DIVER(1) / Z'34000000' / */
/*     DATA LOG10(1) / Z'3E9A209B' / */

/*     MACHINE CONSTANTS FOR THE CONVEX C-1 */

/*     DATA SMALL(1) / '00800000'X / */
/*     DATA LARGE(1) / '7FFFFFFF'X / */
/*     DATA RIGHT(1) / '34800000'X / */
/*     DATA DIVER(1) / '35000000'X / */
/*     DATA LOG10(1) / '3F9A209B'X / */

/*     MACHINE CONSTANTS FOR THE CRAY-1 */

/*     DATA RMACH(1) / 200034000000000000000B / */
/*     DATA RMACH(2) / 577767777777777777776B / */
/*     DATA RMACH(3) / 377224000000000000000B / */
/*     DATA RMACH(4) / 377234000000000000000B / */
/*     DATA RMACH(5) / 377774642023241175720B / */

/*     MACHINE CONSTANTS FOR THE DATA GENERAL ECLIPSE S/200 */

/*     NOTE - IT MAY BE APPROPRIATE TO INCLUDE THE FOLLOWING CARD - */
/*     STATIC RMACH(5) */

/*     DATA SMALL /    20K,       0 / */
/*     DATA LARGE / 77777K, 177777K / */
/*     DATA RIGHT / 35420K,       0 / */
/*     DATA DIVER / 36020K,       0 / */
/*     DATA LOG10 / 40423K,  42023K / */

/*     MACHINE CONSTANTS FOR THE HARRIS 220 */

/*     DATA SMALL(1), SMALL(2) / '20000000, '00000201 / */
/*     DATA LARGE(1), LARGE(2) / '37777777, '00000177 / */
/*     DATA RIGHT(1), RIGHT(2) / '20000000, '00000352 / */
/*     DATA DIVER(1), DIVER(2) / '20000000, '00000353 / */
/*     DATA LOG10(1), LOG10(2) / '23210115, '00000377 / */

/*     MACHINE CONSTANTS FOR THE HONEYWELL 600/6000 SERIES */

/*     DATA RMACH(1) / O402400000000 / */
/*     DATA RMACH(2) / O376777777777 / */
/*     DATA RMACH(3) / O714400000000 / */
/*     DATA RMACH(4) / O716400000000 / */
/*     DATA RMACH(5) / O776464202324 / */

/*     MACHINE CONSTANTS FOR THE HP 2100 */
/*     3 WORD DOUBLE PRECISION WITH FTN4 */

/*     DATA SMALL(1), SMALL(2) / 40000B,       1 / */
/*     DATA LARGE(1), LARGE(2) / 77777B, 177776B / */
/*     DATA RIGHT(1), RIGHT(2) / 40000B,    325B / */
/*     DATA DIVER(1), DIVER(2) / 40000B,    327B / */
/*     DATA LOG10(1), LOG10(2) / 46420B,  46777B / */

/*     MACHINE CONSTANTS FOR THE HP 2100 */
/*     4 WORD DOUBLE PRECISION WITH FTN4 */

/*     DATA SMALL(1), SMALL(2) / 40000B,       1 / */
/*     DATA LARGE91), LARGE(2) / 77777B, 177776B / */
/*     DATA RIGHT(1), RIGHT(2) / 40000B,    325B / */
/*     DATA DIVER(1), DIVER(2) / 40000B,    327B / */
/*     DATA LOG10(1), LOG10(2) / 46420B,  46777B / */

/*     MACHINE CONSTANTS FOR THE HP 9000 */

/*     DATA SMALL(1) / 00004000000B / */
/*     DATA LARGE(1) / 17677777777B / */
/*     DATA RIGHT(1) / 06340000000B / */
/*     DATA DIVER(1) / 06400000000B / */
/*     DATA LOG10(1) / 07646420233B / */

/*     MACHINE CONSTANTS FOR THE ELXSI 6400 */
/*       ASSUMING REAL*4 IS THE DEFAULT REAL */

/*     DATA SMALL(1) / '00800000'X / */
/*     DATA LARGE(1) / '7F7FFFFF'X / */
/*     DATA RIGHT(1) / '33800000'X / */
/*     DATA DIVER(1) / '34000000'X / */
/*     DATA LOG10(1) / '3E9A209B'X / */

/*     MACHINE CONSTANTS FOR THE IBM 360/370 SERIES, */
/*     THE XEROX SIGMA 5/7/9, THE SEL SYSTEMS 85/86  AND */
/*     THE PERKIN ELMER (INTERDATA) 7/32. */

/*     DATA RMACH(1) / Z00100000 / */
/*     DATA RMACH(2) / Z7FFFFFFF / */
/*     DATA RMACH(3) / Z3B100000 / */
/*     DATA RMACH(4) / Z3C100000 / */
/*     DATA RMACH(5) / Z41134413 / */

/*     MACHINE CONSTANTS FOR THE IBM PC */

/*     DATA SMALL(1) /     8420761 / */
/*     DATA LARGE(1) /  2139081118 / */
/*     DATA RIGHT(1) /   863997169 / */
/*     DATA DIVER(1) /   872385777 / */
/*     DATA LOG10(1) /  1050288283 / */

/*     MACHINE CONSTANTS FOR THE IBM RS 6000 */

/*     DATA SMALL(1) / Z'00800000' / */
/*     DATA LARGE(1) / Z'7F7FFFFF' / */
/*     DATA RIGHT(1) / Z'33800000' / */
/*     DATA DIVER(1) / Z'34000000' / */
/*     DATA LOG10(1) / Z'3E9A209B' / */

/*     MACHINE CONSTANTS FOR THE PDP-10 (KA OR KI PROCESSOR) */

/*     DATA RMACH(1) / "000400000000 / */
/*     DATA RMACH(2) / "377777777777 / */
/*     DATA RMACH(3) / "146400000000 / */
/*     DATA RMACH(4) / "147400000000 / */
/*     DATA RMACH(5) / "177464202324 / */

/*     MACHINE CONSTANTS FOR PDP-11 FORTRAN SUPPORTING */
/*     32-BIT INTEGERS (EXPRESSED IN INTEGER AND OCTAL). */

/*     DATA SMALL(1) /    8388608 / */
/*     DATA LARGE(1) / 2147483647 / */
/*     DATA RIGHT(1) /  880803840 / */
/*     DATA DIVER(1) /  889192448 / */
/*     DATA LOG10(1) / 1067065499 / */

/*     DATA RMACH(1) / O00040000000 / */
/*     DATA RMACH(2) / O17777777777 / */
/*     DATA RMACH(3) / O06440000000 / */
/*     DATA RMACH(4) / O06500000000 / */
/*     DATA RMACH(5) / O07746420233 / */

/*     MACHINE CONSTANTS FOR PDP-11 FORTRAN SUPPORTING */
/*     16-BIT INTEGERS  (EXPRESSED IN INTEGER AND OCTAL). */

/*     DATA SMALL(1), SMALL(2) /   128,     0 / */
/*     DATA LARGE(1), LARGE(2) / 32767,    -1 / */
/*     DATA RIGHT(1), RIGHT(2) / 13440,     0 / */
/*     DATA DIVER(1), DIVER(2) / 13568,     0 / */
/*     DATA LOG10(1), LOG10(2) / 16282,  8347 / */

/*     DATA SMALL(1), SMALL(2) / O000200, O000000 / */
/*     DATA LARGE(1), LARGE(2) / O077777, O177777 / */
/*     DATA RIGHT(1), RIGHT(2) / O032200, O000000 / */
/*     DATA DIVER(1), DIVER(2) / O032400, O000000 / */
/*     DATA LOG10(1), LOG10(2) / O037632, O020233 / */

/*     MACHINE CONSTANTS FOR THE SILICON GRAPHICS IRIS */

/*     data rmach(1) / 1.17549 424 e-38 / */
/*     data rmach(2) / 3.40282 356 e+38 / */
/*     data rmach(3) / 1.19209 290 e-07 / */
/*     data rmach(4) / 2.38418 579 e-07 / */
/*     data rmach(5) / 0.30103 001 / */

/*     DATA SMALL(1) / Z'00800000' / */
/*     DATA LARGE(1) / Z'7F7FFFFF' / */
/*     DATA RIGHT(1) / Z'34000000' / */
/*     DATA DIVER(1) / Z'34800000' / */
/*     DATA LOG10(1) / Z'3E9A209B' / */

/*     MACHINE CONSTANTS FOR THE SUN */

/*     DATA SMALL(1) / Z'00800000' / */
/*     DATA LARGE(1) / Z'7F7FFFFF' / */
/*     DATA RIGHT(1) / Z'33800000' / */
/*     DATA DIVER(1) / Z'34000000' / */
/*     DATA LOG10(1) / Z'3E9A209B' / */

/*     MACHINE CONSTANTS FOR THE UNIVAC 1100 SERIES */

/*     DATA RMACH(1) / O000400000000 / */
/*     DATA RMACH(2) / O377777777777 / */
/*     DATA RMACH(3) / O146400000000 / */
/*     DATA RMACH(4) / O147400000000 / */
/*     DATA RMACH(5) / O177464202324 / */

/*     MACHINE CONSTANTS FOR THE VAX 11/780 */
/*     (EXPRESSED IN INTEGER AND HEXADECIMAL) */
/*     THE HEX FORMAT BELOW MAY NOT BE SUITABLE FOR UNIX SYSTEMS */
/*     THE INTEGER FORMAT SHOULD BE OK FOR UNIX SYSTEMS */

/*     DATA SMALL(1) /       128 / */
/*     DATA LARGE(1) /    -32769 / */
/*     DATA RIGHT(1) /     13440 / */
/*     DATA DIVER(1) /     13568 / */
/*     DATA LOG10(1) / 547045274 / */

/*     DATA SMALL(1) / Z00000080 / */
/*     DATA LARGE(1) / ZFFFF7FFF / */
/*     DATA RIGHT(1) / Z00003480 / */
/*     DATA DIVER(1) / Z00003500 / */
/*     DATA LOG10(1) / Z209B3F9A / */

/*     MACHINE CONSTANTS FOR THE Z80 MICROPROCESSOR */

/*     DATA SMALL(1), SMALL(2) /     0,    256/ */
/*     DATA LARGE(1), LARGE(2) /    -1,   -129/ */
/*     DATA RIGHT(1), RIGHT(2) /     0,  26880/ */
/*     DATA DIVER(1), DIVER(2) /     0,  27136/ */
/*     DATA LOG10(1), LOG10(2) /  8347,  32538/ */

	// d1mach variable in scipy/special/xsf/amos/amos.h
	rmach[0] = 2.2250738585072014e-308;  /* np.finfo(np.float64).tiny      */
	rmach[1] = 1.7976931348623157e+308;  /* np.finfo(np.float64).max       */
	rmach[2] = 1.1102230246251565e-16;   /* 0.5 * np.finfo(np.float64).eps */
	rmach[3] = 2.220446049250313e-16;    /* np.finfo(np.float64).eps       */
	rmach[4] = 0.3010299956639812;       /* np.log10(2)                    */

/* ***FIRST EXECUTABLE STATEMENT  R1MACH */
    if (*i__ < 1 || *i__ > 5) {
	xerror_("R1MACH -- I OUT OF BOUNDS", &c__25, &c__1, &c__2, (ftnlen)25)
		;
    }

    ret_val = rmach[*i__ - 1];
    return ret_val;

} /* r1mach_ */

#undef right
#undef diver
#undef small
#undef rmach
#undef large
#undef log10


#ifdef __cplusplus
	}
#endif
