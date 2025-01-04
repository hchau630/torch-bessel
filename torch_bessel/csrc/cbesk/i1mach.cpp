/* fortran/cbesk/i1mach.f -- translated by f2c (version 20240504).
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

/* DECK I1MACH */
integer i1mach_(integer *i__)
{
    /* Format strings */
    static char fmt_9000[] = "(\0021ERROR    1 IN I1MACH - I OUT OF BOUND\
S\002)";

    /* System generated locals */
    integer ret_val;
    static integer equiv_0[16];

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe();
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
#define imach (equiv_0)
#define output (equiv_0 + 3)

    /* Fortran I/O blocks */
    static cilist io___3 = { 0, 0, 0, fmt_9000, 0 };


/* ***BEGIN PROLOGUE  I1MACH */
/* ***DATE WRITTEN   750101   (YYMMDD) */
/* ***REVISION DATE  890213   (YYMMDD) */
/* ***CATEGORY NO.  R1 */
/* ***KEYWORDS  LIBRARY=SLATEC,TYPE=INTEGER(I1MACH-I),MACHINE CONSTANTS */
/* ***AUTHOR  FOX, P. A., (BELL LABS) */
/*           HALL, A. D., (BELL LABS) */
/*           SCHRYER, N. L., (BELL LABS) */
/* ***PURPOSE  Returns integer machine dependent constants */
/* ***DESCRIPTION */

/*     I1MACH can be used to obtain machine-dependent parameters */
/*     for the local machine environment.  It is a function */
/*     subroutine with one (input) argument, and can be called */
/*     as follows, for example */

/*          K = I1MACH(I) */

/*     where I=1,...,16.  The (output) value of K above is */
/*     determined by the (input) value of I.  The results for */
/*     various values of I are discussed below. */

/*  I/O unit numbers. */
/*    I1MACH( 1) = the standard input unit. */
/*    I1MACH( 2) = the standard output unit. */
/*    I1MACH( 3) = the standard punch unit. */
/*    I1MACH( 4) = the standard error message unit. */

/*  Words. */
/*    I1MACH( 5) = the number of bits per integer storage unit. */
/*    I1MACH( 6) = the number of characters per integer storage unit. */

/*  Integers. */
/*    assume integers are represented in the S-digit, base-A form */

/*               sign ( X(S-1)*A**(S-1) + ... + X(1)*A + X(0) ) */

/*               where 0 .LE. X(I) .LT. A for I=0,...,S-1. */
/*    I1MACH( 7) = A, the base. */
/*    I1MACH( 8) = S, the number of base-A digits. */
/*    I1MACH( 9) = A**S - 1, the largest magnitude. */

/*  Floating-Point Numbers. */
/*    Assume floating-point numbers are represented in the T-digit, */
/*    base-B form */
/*               sign (B**E)*( (X(1)/B) + ... + (X(T)/B**T) ) */

/*               where 0 .LE. X(I) .LT. B for I=1,...,T, */
/*               0 .LT. X(1), and EMIN .LE. E .LE. EMAX. */
/*    I1MACH(10) = B, the base. */

/*  Single-Precision */
/*    I1MACH(11) = T, the number of base-B digits. */
/*    I1MACH(12) = EMIN, the smallest exponent E. */
/*    I1MACH(13) = EMAX, the largest exponent E. */

/*  Double-Precision */
/*    I1MACH(14) = T, the number of base-B digits. */
/*    I1MACH(15) = EMIN, the smallest exponent E. */
/*    I1MACH(16) = EMAX, the largest exponent E. */

/*  To alter this function for a particular environment, */
/*  the desired set of DATA statements should be activated by */
/*  removing the C from column 1.  Also, the values of */
/*  I1MACH(1) - I1MACH(4) should be checked for consistency */
/*  with the local operating system. */

/* ***REFERENCES  FOX P.A., HALL A.D., SCHRYER N.L.,*FRAMEWORK FOR A */
/*                 PORTABLE LIBRARY*, ACM TRANSACTIONS ON MATHEMATICAL */
/*                 SOFTWARE, VOL. 4, NO. 2, JUNE 1978, PP. 177-188. */
/* ***ROUTINES CALLED  (NONE) */
/* ***END PROLOGUE  I1MACH */


/*     MACHINE CONSTANTS FOR THE AMIGA */
/*     ABSOFT COMPILER */

/*     DATA IMACH(1) /    5 / */
/*     DATA IMACH(2) /    6 / */
/*     DATA IMACH(3) /    5 / */
/*     DATA IMACH(4) /    6 / */
/*     DATA IMACH(5) /   32 / */
/*     DATA IMACH(6) /    4 / */
/*     DATA IMACH(7) /    2 / */
/*     DATA IMACH(8) /   31 / */
/*     DATA IMACH(9) / 2147483647 / */
/*     DATA IMACH(10)/    2 / */
/*     DATA IMACH(11)/   24 / */
/*     DATA IMACH(12)/ -126 / */
/*     DATA IMACH(13)/  127 / */
/*     DATA IMACH(14)/   53 / */
/*     DATA IMACH(15)/ -1022 / */
/*     DATA IMACH(16)/  1023 / */

/*     MACHINE CONSTANTS FOR THE APOLLO */

/*     DATA IMACH(1) /    5 / */
/*     DATA IMACH(2) /    6 / */
/*     DATA IMACH(3) /    6 / */
/*     DATA IMACH(4) /    6 / */
/*     DATA IMACH(5) /   32 / */
/*     DATA IMACH(6) /    4 / */
/*     DATA IMACH(7) /    2 / */
/*     DATA IMACH(8) /   31 / */
/*     DATA IMACH(9) / 2147483647 / */
/*     DATA IMACH(10)/    2 / */
/*     DATA IMACH(11)/   24 / */
/*     DATA IMACH(12)/ -125 / */
/*     DATA IMACH(13)/  129 / */
/*     DATA IMACH(14)/   53 / */
/*     DATA IMACH(15)/ -1021 / */
/*     DATA IMACH(16)/  1025 / */

/*     MACHINE CONSTANTS FOR THE BURROUGHS 1700 SYSTEM */

/*     DATA IMACH( 1) /    7 / */
/*     DATA IMACH( 2) /    2 / */
/*     DATA IMACH( 3) /    2 / */
/*     DATA IMACH( 4) /    2 / */
/*     DATA IMACH( 5) /   36 / */
/*     DATA IMACH( 6) /    4 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   33 / */
/*     DATA IMACH( 9) / Z1FFFFFFFF / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   24 / */
/*     DATA IMACH(12) / -256 / */
/*     DATA IMACH(13) /  255 / */
/*     DATA IMACH(14) /   60 / */
/*     DATA IMACH(15) / -256 / */
/*     DATA IMACH(16) /  255 / */

/*     MACHINE CONSTANTS FOR THE BURROUGHS 5700 SYSTEM */

/*     DATA IMACH( 1) /   5 / */
/*     DATA IMACH( 2) /   6 / */
/*     DATA IMACH( 3) /   7 / */
/*     DATA IMACH( 4) /   6 / */
/*     DATA IMACH( 5) /  48 / */
/*     DATA IMACH( 6) /   6 / */
/*     DATA IMACH( 7) /   2 / */
/*     DATA IMACH( 8) /  39 / */
/*     DATA IMACH( 9) / O0007777777777777 / */
/*     DATA IMACH(10) /   8 / */
/*     DATA IMACH(11) /  13 / */
/*     DATA IMACH(12) / -50 / */
/*     DATA IMACH(13) /  76 / */
/*     DATA IMACH(14) /  26 / */
/*     DATA IMACH(15) / -50 / */
/*     DATA IMACH(16) /  76 / */

/*     MACHINE CONSTANTS FOR THE BURROUGHS 6700/7700 SYSTEMS */

/*     DATA IMACH( 1) /   5 / */
/*     DATA IMACH( 2) /   6 / */
/*     DATA IMACH( 3) /   7 / */
/*     DATA IMACH( 4) /   6 / */
/*     DATA IMACH( 5) /  48 / */
/*     DATA IMACH( 6) /   6 / */
/*     DATA IMACH( 7) /   2 / */
/*     DATA IMACH( 8) /  39 / */
/*     DATA IMACH( 9) / O0007777777777777 / */
/*     DATA IMACH(10) /   8 / */
/*     DATA IMACH(11) /  13 / */
/*     DATA IMACH(12) / -50 / */
/*     DATA IMACH(13) /  76 / */
/*     DATA IMACH(14) /  26 / */
/*     DATA IMACH(15) / -32754 / */
/*     DATA IMACH(16) /  32780 / */

/*     MACHINE CONSTANTS FOR THE CDC 170/180 SERIES USING NOS/VE */

/*     DATA IMACH( 1) /     5 / */
/*     DATA IMACH( 2) /     6 / */
/*     DATA IMACH( 3) /     7 / */
/*     DATA IMACH( 4) /     6 / */
/*     DATA IMACH( 5) /    64 / */
/*     DATA IMACH( 6) /     8 / */
/*     DATA IMACH( 7) /     2 / */
/*     DATA IMACH( 8) /    63 / */
/*     DATA IMACH( 9) / 9223372036854775807 / */
/*     DATA IMACH(10) /     2 / */
/*     DATA IMACH(11) /    47 / */
/*     DATA IMACH(12) / -4095 / */
/*     DATA IMACH(13) /  4094 / */
/*     DATA IMACH(14) /    94 / */
/*     DATA IMACH(15) / -4095 / */
/*     DATA IMACH(16) /  4094 / */

/*     MACHINE CONSTANTS FOR THE CDC 6000/7000 SERIES */

/*     DATA IMACH( 1) /    5 / */
/*     DATA IMACH( 2) /    6 / */
/*     DATA IMACH( 3) /    7 / */
/*     DATA IMACH( 4) /6LOUTPUT/ */
/*     DATA IMACH( 5) /   60 / */
/*     DATA IMACH( 6) /   10 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   48 / */
/*     DATA IMACH( 9) / 00007777777777777777B / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   47 / */
/*     DATA IMACH(12) / -929 / */
/*     DATA IMACH(13) / 1070 / */
/*     DATA IMACH(14) /   94 / */
/*     DATA IMACH(15) / -929 / */
/*     DATA IMACH(16) / 1069 / */

/*     MACHINE CONSTANTS FOR THE CELERITY C1260 */

/*     DATA IMACH(1) /    5 / */
/*     DATA IMACH(2) /    6 / */
/*     DATA IMACH(3) /    6 / */
/*     DATA IMACH(4) /    0 / */
/*     DATA IMACH(5) /   32 / */
/*     DATA IMACH(6) /    4 / */
/*     DATA IMACH(7) /    2 / */
/*     DATA IMACH(8) /   31 / */
/*     DATA IMACH(9) / Z'7FFFFFFF' / */
/*     DATA IMACH(10)/    2 / */
/*     DATA IMACH(11)/   24 / */
/*     DATA IMACH(12)/ -126 / */
/*     DATA IMACH(13)/  127 / */
/*     DATA IMACH(14)/   53 / */
/*     DATA IMACH(15)/ -1022 / */
/*     DATA IMACH(16)/  1023 / */

/*     MACHINE CONSTANTS FOR THE CONVEX C-1 */

/*     DATA IMACH( 1) /     5/ */
/*     DATA IMACH( 2) /     6/ */
/*     DATA IMACH( 3) /     7/ */
/*     DATA IMACH( 4) /     6/ */
/*     DATA IMACH( 5) /    32/ */
/*     DATA IMACH( 6) /     4/ */
/*     DATA IMACH( 7) /     2/ */
/*     DATA IMACH( 8) /    31/ */
/*     DATA IMACH( 9) /2147483647/ */
/*     DATA IMACH(10) /     2/ */
/*     DATA IMACH(11) /    24/ */
/*     DATA IMACH(12) /  -128/ */
/*     DATA IMACH(13) /   127/ */
/*     DATA IMACH(14) /    53/ */
/*     DATA IMACH(15) / -1024/ */
/*     DATA IMACH(16) /  1023/ */

/*     MACHINE CONSTANTS FOR THE CRAY-1 */

/*     DATA IMACH( 1) /   100 / */
/*     DATA IMACH( 2) /   101 / */
/*     DATA IMACH( 3) /   102 / */
/*     DATA IMACH( 4) /   101 / */
/*     DATA IMACH( 5) /    64 / */
/*     DATA IMACH( 6) /     8 / */
/*     DATA IMACH( 7) /     2 / */
/*     DATA IMACH( 8) /    63 / */
/*     DATA IMACH( 9) /  777777777777777777777B / */
/*     DATA IMACH(10) /     2 / */
/*     DATA IMACH(11) /    47 / */
/*     DATA IMACH(12) / -8189 / */
/*     DATA IMACH(13) /  8190 / */
/*     DATA IMACH(14) /    94 / */
/*     DATA IMACH(15) / -8099 / */
/*     DATA IMACH(16) /  8190 / */

/*     MACHINE CONSTANTS FOR THE DATA GENERAL ECLIPSE S/200 */

/*     DATA IMACH( 1) /   11 / */
/*     DATA IMACH( 2) /   12 / */
/*     DATA IMACH( 3) /    8 / */
/*     DATA IMACH( 4) /   10 / */
/*     DATA IMACH( 5) /   16 / */
/*     DATA IMACH( 6) /    2 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   15 / */
/*     DATA IMACH( 9) /32767 / */
/*     DATA IMACH(10) /   16 / */
/*     DATA IMACH(11) /    6 / */
/*     DATA IMACH(12) /  -64 / */
/*     DATA IMACH(13) /   63 / */
/*     DATA IMACH(14) /   14 / */
/*     DATA IMACH(15) /  -64 / */
/*     DATA IMACH(16) /   63 / */

/*     MACHINE CONSTANTS FOR THE ELXSI 6400 */

/*     DATA IMACH( 1) /     5/ */
/*     DATA IMACH( 2) /     6/ */
/*     DATA IMACH( 3) /     6/ */
/*     DATA IMACH( 4) /     6/ */
/*     DATA IMACH( 5) /    32/ */
/*     DATA IMACH( 6) /     4/ */
/*     DATA IMACH( 7) /     2/ */
/*     DATA IMACH( 8) /    32/ */
/*     DATA IMACH( 9) /2147483647/ */
/*     DATA IMACH(10) /     2/ */
/*     DATA IMACH(11) /    24/ */
/*     DATA IMACH(12) /  -126/ */
/*     DATA IMACH(13) /   127/ */
/*     DATA IMACH(14) /    53/ */
/*     DATA IMACH(15) / -1022/ */
/*     DATA IMACH(16) /  1023/ */

/*     MACHINE CONSTANTS FOR THE HARRIS 220 */

/*     DATA IMACH( 1) /       5 / */
/*     DATA IMACH( 2) /       6 / */
/*     DATA IMACH( 3) /       0 / */
/*     DATA IMACH( 4) /       6 / */
/*     DATA IMACH( 5) /      24 / */
/*     DATA IMACH( 6) /       3 / */
/*     DATA IMACH( 7) /       2 / */
/*     DATA IMACH( 8) /      23 / */
/*     DATA IMACH( 9) / 8388607 / */
/*     DATA IMACH(10) /       2 / */
/*     DATA IMACH(11) /      23 / */
/*     DATA IMACH(12) /    -127 / */
/*     DATA IMACH(13) /     127 / */
/*     DATA IMACH(14) /      38 / */
/*     DATA IMACH(15) /    -127 / */
/*     DATA IMACH(16) /     127 / */

/*     MACHINE CONSTANTS FOR THE HONEYWELL 600/6000 SERIES */

/*     DATA IMACH( 1) /    5 / */
/*     DATA IMACH( 2) /    6 / */
/*     DATA IMACH( 3) /   43 / */
/*     DATA IMACH( 4) /    6 / */
/*     DATA IMACH( 5) /   36 / */
/*     DATA IMACH( 6) /    6 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   35 / */
/*     DATA IMACH( 9) / O377777777777 / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   27 / */
/*     DATA IMACH(12) / -127 / */
/*     DATA IMACH(13) /  127 / */
/*     DATA IMACH(14) /   63 / */
/*     DATA IMACH(15) / -127 / */
/*     DATA IMACH(16) /  127 / */

/*     MACHINE CONSTANTS FOR THE HP 2100 */
/*     3 WORD DOUBLE PRECISION OPTION WITH FTN4 */

/*     DATA IMACH(1) /      5/ */
/*     DATA IMACH(2) /      6 / */
/*     DATA IMACH(3) /      4 / */
/*     DATA IMACH(4) /      1 / */
/*     DATA IMACH(5) /     16 / */
/*     DATA IMACH(6) /      2 / */
/*     DATA IMACH(7) /      2 / */
/*     DATA IMACH(8) /     15 / */
/*     DATA IMACH(9) /  32767 / */
/*     DATA IMACH(10)/      2 / */
/*     DATA IMACH(11)/     23 / */
/*     DATA IMACH(12)/   -128 / */
/*     DATA IMACH(13)/    127 / */
/*     DATA IMACH(14)/     39 / */
/*     DATA IMACH(15)/   -128 / */
/*     DATA IMACH(16)/    127 / */

/*     MACHINE CONSTANTS FOR THE HP 2100 */
/*     4 WORD DOUBLE PRECISION OPTION WITH FTN4 */

/*     DATA IMACH(1) /      5 / */
/*     DATA IMACH(2) /      6 / */
/*     DATA IMACH(3) /      4 / */
/*     DATA IMACH(4) /      1 / */
/*     DATA IMACH(5) /     16 / */
/*     DATA IMACH(6) /      2 / */
/*     DATA IMACH(7) /      2 / */
/*     DATA IMACH(8) /     15 / */
/*     DATA IMACH(9) /  32767 / */
/*     DATA IMACH(10)/      2 / */
/*     DATA IMACH(11)/     23 / */
/*     DATA IMACH(12)/   -128 / */
/*     DATA IMACH(13)/    127 / */
/*     DATA IMACH(14)/     55 / */
/*     DATA IMACH(15)/   -128 / */
/*     DATA IMACH(16)/    127 / */

/*     MACHINE CONSTANTS FOR THE HP 9000 */

/*     DATA IMACH(1)  /    5 / */
/*     DATA IMACH(2)  /    6 / */
/*     DATA IMACH(3)  /    6 / */
/*     DATA IMACH(3)  /    7 / */
/*     DATA IMACH(5)  /   32 / */
/*     DATA IMACH(6)  /    4 / */
/*     DATA IMACH(7)  /    2 / */
/*     DATA IMACH(8)  /   32 / */
/*     DATA IMACH(9)  /2147483647 / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   24 / */
/*     DATA IMACH(12) / -126 / */
/*     DATA IMACH(13) /  127 / */
/*     DATA IMACH(14) /   53 / */
/*     DATA IMACH(15) /-1015 / */
/*     DATA IMACH(16) / 1017 / */

/*     MACHINE CONSTANTS FOR THE IBM 360/370 SERIES, */
/*     THE XEROX SIGMA 5/7/9, THE SEL SYSTEMS 85/86, AND */
/*     THE PERKIN ELMER (INTERDATA) 7/32. */

/*     DATA IMACH( 1) /   5 / */
/*     DATA IMACH( 2) /   6 / */
/*     DATA IMACH( 3) /   7 / */
/*     DATA IMACH( 4) /   6 / */
/*     DATA IMACH( 5) /  32 / */
/*     DATA IMACH( 6) /   4 / */
/*     DATA IMACH( 7) /  16 / */
/*     DATA IMACH( 8) /  31 / */
/*     DATA IMACH( 9) / Z7FFFFFFF / */
/*     DATA IMACH(10) /  16 / */
/*     DATA IMACH(11) /   6 / */
/*     DATA IMACH(12) / -64 / */
/*     DATA IMACH(13) /  63 / */
/*     DATA IMACH(14) /  14 / */
/*     DATA IMACH(15) / -64 / */
/*     DATA IMACH(16) /  63 / */

/*     MACHINE CONSTANTS FOR THE IBM PC */

/*     DATA IMACH( 1) /     5 / */
/*     DATA IMACH( 2) /     6 / */
/*     DATA IMACH( 3) /     0 / */
/*     DATA IMACH( 4) /     0 / */
/*     DATA IMACH( 5) /    32 / */
/*     DATA IMACH( 6) /     4 / */
/*     DATA IMACH( 7) /     2 / */
/*     DATA IMACH( 8) /    31 / */
/*     DATA IMACH( 9) / 2147483647 / */
/*     DATA IMACH(10) /     2 / */
/*     DATA IMACH(11) /    24 / */
/*     DATA IMACH(12) /  -125 / */
/*     DATA IMACH(13) /   127 / */
/*     DATA IMACH(14) /    53 / */
/*     DATA IMACH(15) / -1021 / */
/*     DATA IMACH(16) /  1023 / */

/*     MACHINE CONSTANTS FOR THE IBM RS 6000 */

/*     DATA IMACH( 1) /          5 / */
/*     DATA IMACH( 2) /          6 / */
/*     DATA IMACH( 3) /          6 / */
/*     DATA IMACH( 4) /          0 / */
/*     DATA IMACH( 5) /         32 / */
/*     DATA IMACH( 6) /          4 / */
/*     DATA IMACH( 7) /          2 / */
/*     DATA IMACH( 8) /         31 / */
/*     DATA IMACH( 9) / 2147483647 / */
/*     DATA IMACH(10) /          2 / */
/*     DATA IMACH(11) /         24 / */
/*     DATA IMACH(12) /       -125 / */
/*     DATA IMACH(13) /        128 / */
/*     DATA IMACH(14) /         53 / */
/*     DATA IMACH(15) /      -1021 / */
/*     DATA IMACH(16) /       1024 / */

/*     MACHINE CONSTANTS FOR THE PDP-10 (KA PROCESSOR) */

/*     DATA IMACH( 1) /    5 / */
/*     DATA IMACH( 2) /    6 / */
/*     DATA IMACH( 3) /    5 / */
/*     DATA IMACH( 4) /    6 / */
/*     DATA IMACH( 5) /   36 / */
/*     DATA IMACH( 6) /    5 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   35 / */
/*     DATA IMACH( 9) / "377777777777 / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   27 / */
/*     DATA IMACH(12) / -128 / */
/*     DATA IMACH(13) /  127 / */
/*     DATA IMACH(14) /   54 / */
/*     DATA IMACH(15) / -101 / */
/*     DATA IMACH(16) /  127 / */

/*     MACHINE CONSTANTS FOR THE PDP-10 (KI PROCESSOR) */

/*     DATA IMACH( 1) /    5 / */
/*     DATA IMACH( 2) /    6 / */
/*     DATA IMACH( 3) /    5 / */
/*     DATA IMACH( 4) /    6 / */
/*     DATA IMACH( 5) /   36 / */
/*     DATA IMACH( 6) /    5 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   35 / */
/*     DATA IMACH( 9) / "377777777777 / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   27 / */
/*     DATA IMACH(12) / -128 / */
/*     DATA IMACH(13) /  127 / */
/*     DATA IMACH(14) /   62 / */
/*     DATA IMACH(15) / -128 / */
/*     DATA IMACH(16) /  127 / */

/*     MACHINE CONSTANTS FOR PDP-11 FORTRAN SUPPORTING */
/*     32-BIT INTEGER ARITHMETIC. */

/*     DATA IMACH( 1) /    5 / */
/*     DATA IMACH( 2) /    6 / */
/*     DATA IMACH( 3) /    5 / */
/*     DATA IMACH( 4) /    6 / */
/*     DATA IMACH( 5) /   32 / */
/*     DATA IMACH( 6) /    4 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   31 / */
/*     DATA IMACH( 9) / 2147483647 / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   24 / */
/*     DATA IMACH(12) / -127 / */
/*     DATA IMACH(13) /  127 / */
/*     DATA IMACH(14) /   56 / */
/*     DATA IMACH(15) / -127 / */
/*     DATA IMACH(16) /  127 / */

/*     MACHINE CONSTANTS FOR PDP-11 FORTRAN SUPPORTING */
/*     16-BIT INTEGER ARITHMETIC. */

/*     DATA IMACH( 1) /    5 / */
/*     DATA IMACH( 2) /    6 / */
/*     DATA IMACH( 3) /    5 / */
/*     DATA IMACH( 4) /    6 / */
/*     DATA IMACH( 5) /   16 / */
/*     DATA IMACH( 6) /    2 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   15 / */
/*     DATA IMACH( 9) / 32767 / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   24 / */
/*     DATA IMACH(12) / -127 / */
/*     DATA IMACH(13) /  127 / */
/*     DATA IMACH(14) /   56 / */
/*     DATA IMACH(15) / -127 / */
/*     DATA IMACH(16) /  127 / */

/*     MACHINE CONSTANTS FOR THE SILICON GRAPHICS IRIS */

/*     DATA IMACH( 1) /     5 / */
/*     DATA IMACH( 2) /     6 / */
/*     DATA IMACH( 3) /     6 / */
/*     DATA IMACH( 4) /     0 / */
/*     DATA IMACH( 5) /    32 / */
/*     DATA IMACH( 6) /     4 / */
/*     DATA IMACH( 7) /     2 / */
/*     DATA IMACH( 8) /    31 / */
/*     DATA IMACH( 9) / 2147483647 / */
/*     DATA IMACH(10) /     2 / */
/*     DATA IMACH(11) /    23 / */
/*     DATA IMACH(12) /  -126 / */
/*     DATA IMACH(13) /   127 / */
/*     DATA IMACH(14) /    52 / */
/*     DATA IMACH(15) / -1022 / */
/*     DATA IMACH(16) /  1023 / */

/*     MACHINE CONSTANTS FOR THE SUN */

/*     DATA IMACH(1) /    5 / */
/*     DATA IMACH(2) /    6 / */
/*     DATA IMACH(3) /    6 / */
/*     DATA IMACH(4) /    6 / */
/*     DATA IMACH(5) /   32 / */
/*     DATA IMACH(6) /    4 / */
/*     DATA IMACH(7) /    2 / */
/*     DATA IMACH(8) /   31 / */
/*     DATA IMACH(9) /2147483647 / */
/*     DATA IMACH(10)/    2 / */
/*     DATA IMACH(11)/   24 / */
/*     DATA IMACH(12)/ -125 / */
/*     DATA IMACH(13)/  128 / */
/*     DATA IMACH(14)/   53 / */
/*     DATA IMACH(15)/ -1021 / */
/*     DATA IMACH(16)/  1024 / */

/*     MACHINE CONSTANTS FOR THE UNIVAC 1100 SERIES FTN COMPILER */


/*     DATA IMACH( 1) /    5 / */
/*     DATA IMACH( 2) /    6 / */
/*     DATA IMACH( 3) /    1 / */
/*     DATA IMACH( 4) /    6 / */
/*     DATA IMACH( 5) /   36 / */
/*     DATA IMACH( 6) /    4 / */
/*     DATA IMACH( 7) /    2 / */
/*     DATA IMACH( 8) /   35 / */
/*     DATA IMACH( 9) / O377777777777 / */
/*     DATA IMACH(10) /    2 / */
/*     DATA IMACH(11) /   27 / */
/*     DATA IMACH(12) / -128 / */
/*     DATA IMACH(13) /  127 / */
/*     DATA IMACH(14) /   60 / */
/*     DATA IMACH(15) /-1024 / */
/*     DATA IMACH(16) / 1023 / */

/*     MACHINE CONSTANTS FOR THE VAX 11/780 */

/*     DATA IMACH(1) /    5 / */
/*     DATA IMACH(2) /    6 / */
/*     DATA IMACH(3) /    5 / */
/*     DATA IMACH(4) /    6 / */
/*     DATA IMACH(5) /   32 / */
/*     DATA IMACH(6) /    4 / */
/*     DATA IMACH(7) /    2 / */
/*     DATA IMACH(8) /   31 / */
/*     DATA IMACH(9) /2147483647 / */
/*     DATA IMACH(10)/    2 / */
/*     DATA IMACH(11)/   24 / */
/*     DATA IMACH(12)/ -127 / */
/*     DATA IMACH(13)/  127 / */
/*     DATA IMACH(14)/   56 / */
/*     DATA IMACH(15)/ -127 / */
/*     DATA IMACH(16)/  127 / */

/*     MACHINE CONSTANTS FOR THE VAX 11/780, G-FLOAT OPTION */

/*     DATA IMACH(1) /    5 / */
/*     DATA IMACH(2) /    6 / */
/*     DATA IMACH(3) /    5 / */
/*     DATA IMACH(4) /    6 / */
/*     DATA IMACH(5) /   32 / */
/*     DATA IMACH(6) /    4 / */
/*     DATA IMACH(7) /    2 / */
/*     DATA IMACH(8) /   31 / */
/*     DATA IMACH(9) /2147483647 / */
/*     DATA IMACH(10)/    2 / */
/*     DATA IMACH(11)/   24 / */
/*     DATA IMACH(12)/ -127 / */
/*     DATA IMACH(13)/  127 / */
/*     DATA IMACH(14)/   53 / */
/*     DATA IMACH(15)/ -1022 / */
/*     DATA IMACH(16)/  1023 / */

/*     MACHINE CONSTANTS FOR THE Z80 MICROPROCESSOR */

/*     DATA IMACH( 1) /     1/ */
/*     DATA IMACH( 2) /     1/ */
/*     DATA IMACH( 3) /     0/ */
/*     DATA IMACH( 4) /     1/ */
/*     DATA IMACH( 5) /    16/ */
/*     DATA IMACH( 6) /     2/ */
/*     DATA IMACH( 7) /     2/ */
/*     DATA IMACH( 8) /    15/ */
/*     DATA IMACH( 9) / 32767/ */
/*     DATA IMACH(10) /     2/ */
/*     DATA IMACH(11) /    24/ */
/*     DATA IMACH(12) /  -127/ */
/*     DATA IMACH(13) /   127/ */
/*     DATA IMACH(14) /    56/ */
/*     DATA IMACH(15) /  -127/ */
/*     DATA IMACH(16) /   127/ */

    // i1mach variable in scipy/special/xsf/amos/amos.h
    imach[0] = 5;           /* standard input         */
    imach[1] = 6;           /* standard output        */
    imach[2] = 7;           /* standard punch         */
    imach[3] = 0;           /* standard error         */
    imach[4] = 32;          /* bits per integer       */
    imach[5] = 4;           /* sizeof(int);           */
    imach[6] = 2;           /* base for integers      */
    imach[7] = 31;          /* digits of integer base */
    imach[8] = 2147483647;  /* LONG MAX 2**31 - 1     */
    imach[9] = 2;           /* FLT_RADIX;             */
    imach[10] = 24;          /* FLT_MANT_DIG;          */
    imach[11] = -126;        /* FLT_MIN_EXP;           */
    imach[12] = 128;         /* FLT_MAX_EXP;           */
    imach[13] = 53;          /* DBL_MANT_DIG;          */
    imach[14] = -1021;       /* DBL_MIN_EXP;           */
    imach[15] = 1024;         /* DBL_MAX_EXP;           */


/* ***FIRST EXECUTABLE STATEMENT  I1MACH */
    if (*i__ < 1 || *i__ > 16) {
	goto L10;
    }

    ret_val = imach[*i__ - 1];
    return ret_val;

L10:
    io___3.ciunit = *output;
    s_wsfe(&io___3);
    e_wsfe();

/*     CALL FDUMP */


    s_stop("", (ftnlen)0);
    return ret_val;
} /* i1mach_ */

#undef output
#undef imach


#ifdef __cplusplus
	}
#endif
