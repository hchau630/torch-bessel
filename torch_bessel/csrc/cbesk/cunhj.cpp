/* fortran/cbesk/cunhj.f -- translated by f2c (version 20240504).
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

/* Subroutine */ int cunhj_(complex *z__, real *fnu, integer *ipmtr, real *
	tol, complex *phi, complex *arg, complex *zeta1, complex *zeta2, 
	complex *asum, complex *bsum)
{
    /* Initialized data */

    static real ar[14] = { (float)1.,(float).104166666666666667,(float)
	    .0835503472222222222,(float).12822657455632716,(float)
	    .291849026464140464,(float).881627267443757652,(float)
	    3.32140828186276754,(float)14.9957629868625547,(float)
	    78.9230130115865181,(float)474.451538868264323,(float)
	    3207.49009089066193,(float)24086.5496408740049,(float)
	    198923.119169509794,(float)1791902.00777534383 };
    static real pi = (float)3.14159265358979324;
    static real thpi = (float)4.71238898038468986;
    static complex czero = {(float)0.,(float)0.};
    static complex cone = {(float)1.,(float)0.};
    static real br[14] = { (float)1.,(float)-.145833333333333333,(float)
	    -.0987413194444444444,(float)-.143312053915895062,(float)
	    -.317227202678413548,(float)-.942429147957120249,(float)
	    -3.51120304082635426,(float)-15.7272636203680451,(float)
	    -82.2814390971859444,(float)-492.355370523670524,(float)
	    -3316.21856854797251,(float)-24827.6742452085896,(float)
	    -204526.587315129788,(float)-1838444.9170682099 };
    static real c__[105] = { (float)1.,(float)-.208333333333333333,(float)
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
	    -3871833.44257261262,(float)18257.7554742931747 };
    static real alfa[180] = { (float)-.00444444444444444444,(float)
	    -9.22077922077922078e-4,(float)-8.84892884892884893e-5,(float)
	    1.65927687832449737e-4,(float)2.4669137274179291e-4,(float)
	    2.6599558934625478e-4,(float)2.61824297061500945e-4,(float)
	    2.48730437344655609e-4,(float)2.32721040083232098e-4,(float)
	    2.16362485712365082e-4,(float)2.00738858762752355e-4,(float)
	    1.86267636637545172e-4,(float)1.73060775917876493e-4,(float)
	    1.61091705929015752e-4,(float)1.50274774160908134e-4,(float)
	    1.40503497391269794e-4,(float)1.31668816545922806e-4,(float)
	    1.23667445598253261e-4,(float)1.16405271474737902e-4,(float)
	    1.09798298372713369e-4,(float)1.03772410422992823e-4,(float)
	    9.82626078369363448e-5,(float)9.32120517249503256e-5,(float)
	    8.85710852478711718e-5,(float)8.42963105715700223e-5,(float)
	    8.03497548407791151e-5,(float)7.66981345359207388e-5,(float)
	    7.33122157481777809e-5,(float)7.01662625163141333e-5,(float)
	    6.72375633790160292e-5,(float)6.93735541354588974e-4,(float)
	    2.32241745182921654e-4,(float)-1.41986273556691197e-5,(float)
	    -1.1644493167204864e-4,(float)-1.50803558053048762e-4,(float)
	    -1.55121924918096223e-4,(float)-1.46809756646465549e-4,(float)
	    -1.33815503867491367e-4,(float)-1.19744975684254051e-4,(float)
	    -1.0618431920797402e-4,(float)-9.37699549891194492e-5,(float)
	    -8.26923045588193274e-5,(float)-7.29374348155221211e-5,(float)
	    -6.44042357721016283e-5,(float)-5.69611566009369048e-5,(float)
	    -5.04731044303561628e-5,(float)-4.48134868008882786e-5,(float)
	    -3.98688727717598864e-5,(float)-3.55400532972042498e-5,(float)
	    -3.1741425660902248e-5,(float)-2.83996793904174811e-5,(float)
	    -2.54522720634870566e-5,(float)-2.28459297164724555e-5,(float)
	    -2.05352753106480604e-5,(float)-1.84816217627666085e-5,(float)
	    -1.66519330021393806e-5,(float)-1.50179412980119482e-5,(float)
	    -1.35554031379040526e-5,(float)-1.22434746473858131e-5,(float)
	    -1.10641884811308169e-5,(float)-3.54211971457743841e-4,(float)
	    -1.56161263945159416e-4,(float)3.0446550359493641e-5,(float)
	    1.30198655773242693e-4,(float)1.67471106699712269e-4,(float)
	    1.70222587683592569e-4,(float)1.56501427608594704e-4,(float)
	    1.3633917097744512e-4,(float)1.14886692029825128e-4,(float)
	    9.45869093034688111e-5,(float)7.64498419250898258e-5,(float)
	    6.07570334965197354e-5,(float)4.74394299290508799e-5,(float)
	    3.62757512005344297e-5,(float)2.69939714979224901e-5,(float)
	    1.93210938247939253e-5,(float)1.30056674793963203e-5,(float)
	    7.82620866744496661e-6,(float)3.59257485819351583e-6,(float)
	    1.44040049814251817e-7,(float)-2.65396769697939116e-6,(float)
	    -4.9134686709848591e-6,(float)-6.72739296091248287e-6,(float)
	    -8.17269379678657923e-6,(float)-9.31304715093561232e-6,(float)
	    -1.02011418798016441e-5,(float)-1.0880596251059288e-5,(float)
	    -1.13875481509603555e-5,(float)-1.17519675674556414e-5,(float)
	    -1.19987364870944141e-5,(float)3.78194199201772914e-4,(float)
	    2.02471952761816167e-4,(float)-6.37938506318862408e-5,(float)
	    -2.38598230603005903e-4,(float)-3.10916256027361568e-4,(float)
	    -3.13680115247576316e-4,(float)-2.78950273791323387e-4,(float)
	    -2.28564082619141374e-4,(float)-1.75245280340846749e-4,(float)
	    -1.25544063060690348e-4,(float)-8.22982872820208365e-5,(float)
	    -4.62860730588116458e-5,(float)-1.72334302366962267e-5,(float)
	    5.60690482304602267e-6,(float)2.313954431482868e-5,(float)
	    3.62642745856793957e-5,(float)4.58006124490188752e-5,(float)
	    5.2459529495911405e-5,(float)5.68396208545815266e-5,(float)
	    5.94349820393104052e-5,(float)6.06478527578421742e-5,(float)
	    6.08023907788436497e-5,(float)6.01577894539460388e-5,(float)
	    5.891996573446985e-5,(float)5.72515823777593053e-5,(float)
	    5.52804375585852577e-5,(float)5.3106377380288017e-5,(float)
	    5.08069302012325706e-5,(float)4.84418647620094842e-5,(float)
	    4.6056858160747537e-5,(float)-6.91141397288294174e-4,(float)
	    -4.29976633058871912e-4,(float)1.83067735980039018e-4,(float)
	    6.60088147542014144e-4,(float)8.75964969951185931e-4,(float)
	    8.77335235958235514e-4,(float)7.49369585378990637e-4,(float)
	    5.63832329756980918e-4,(float)3.68059319971443156e-4,(float)
	    1.88464535514455599e-4,(float)3.70663057664904149e-5,(float)
	    -8.28520220232137023e-5,(float)-1.72751952869172998e-4,(float)
	    -2.36314873605872983e-4,(float)-2.77966150694906658e-4,(float)
	    -3.02079514155456919e-4,(float)-3.12594712643820127e-4,(float)
	    -3.12872558758067163e-4,(float)-3.05678038466324377e-4,(float)
	    -2.93226470614557331e-4,(float)-2.77255655582934777e-4,(float)
	    -2.59103928467031709e-4,(float)-2.39784014396480342e-4,(float)
	    -2.20048260045422848e-4,(float)-2.00443911094971498e-4,(float)
	    -1.81358692210970687e-4,(float)-1.63057674478657464e-4,(float)
	    -1.45712672175205844e-4,(float)-1.29425421983924587e-4,(float)
	    -1.14245691942445952e-4,(float).00192821964248775885,(float)
	    .00135592576302022234,(float)-7.17858090421302995e-4,(float)
	    -.00258084802575270346,(float)-.00349271130826168475,(float)
	    -.00346986299340960628,(float)-.00282285233351310182,(float)
	    -.00188103076404891354,(float)-8.895317183839476e-4,(float)
	    3.87912102631035228e-6,(float)7.28688540119691412e-4,(float)
	    .00126566373053457758,(float).00162518158372674427,(float)
	    .00183203153216373172,(float).00191588388990527909,(float)
	    .00190588846755546138,(float).00182798982421825727,(float)
	    .0017038950642112153,(float).00155097127171097686,(float)
	    .00138261421852276159,(float).00120881424230064774,(float)
	    .00103676532638344962,(float)8.71437918068619115e-4,(float)
	    7.16080155297701002e-4,(float)5.72637002558129372e-4,(float)
	    4.42089819465802277e-4,(float)3.24724948503090564e-4,(float)
	    2.20342042730246599e-4,(float)1.28412898401353882e-4,(float)
	    4.82005924552095464e-5 };
    static real beta[210] = { (float).0179988721413553309,(float)
	    .00559964911064388073,(float).00288501402231132779,(float)
	    .00180096606761053941,(float).00124753110589199202,(float)
	    9.22878876572938311e-4,(float)7.14430421727287357e-4,(float)
	    5.71787281789704872e-4,(float)4.69431007606481533e-4,(float)
	    3.93232835462916638e-4,(float)3.34818889318297664e-4,(float)
	    2.88952148495751517e-4,(float)2.52211615549573284e-4,(float)
	    2.22280580798883327e-4,(float)1.97541838033062524e-4,(float)
	    1.76836855019718004e-4,(float)1.59316899661821081e-4,(float)
	    1.44347930197333986e-4,(float)1.31448068119965379e-4,(float)
	    1.20245444949302884e-4,(float)1.10449144504599392e-4,(float)
	    1.01828770740567258e-4,(float)9.41998224204237509e-5,(float)
	    8.74130545753834437e-5,(float)8.13466262162801467e-5,(float)
	    7.59002269646219339e-5,(float)7.09906300634153481e-5,(float)
	    6.65482874842468183e-5,(float)6.25146958969275078e-5,(float)
	    5.88403394426251749e-5,(float)-.00149282953213429172,(float)
	    -8.78204709546389328e-4,(float)-5.02916549572034614e-4,(float)
	    -2.94822138512746025e-4,(float)-1.75463996970782828e-4,(float)
	    -1.04008550460816434e-4,(float)-5.96141953046457895e-5,(float)
	    -3.1203892907609834e-5,(float)-1.26089735980230047e-5,(float)
	    -2.42892608575730389e-7,(float)8.05996165414273571e-6,(float)
	    1.36507009262147391e-5,(float)1.73964125472926261e-5,(float)
	    1.9867297884213378e-5,(float)2.14463263790822639e-5,(float)
	    2.23954659232456514e-5,(float)2.28967783814712629e-5,(float)
	    2.30785389811177817e-5,(float)2.30321976080909144e-5,(float)
	    2.28236073720348722e-5,(float)2.25005881105292418e-5,(float)
	    2.20981015361991429e-5,(float)2.16418427448103905e-5,(float)
	    2.11507649256220843e-5,(float)2.06388749782170737e-5,(float)
	    2.01165241997081666e-5,(float)1.95913450141179244e-5,(float)
	    1.9068936791043674e-5,(float)1.85533719641636667e-5,(float)
	    1.80475722259674218e-5,(float)5.5221307672129279e-4,(float)
	    4.47932581552384646e-4,(float)2.79520653992020589e-4,(float)
	    1.52468156198446602e-4,(float)6.93271105657043598e-5,(float)
	    1.76258683069991397e-5,(float)-1.35744996343269136e-5,(float)
	    -3.17972413350427135e-5,(float)-4.18861861696693365e-5,(float)
	    -4.69004889379141029e-5,(float)-4.87665447413787352e-5,(float)
	    -4.87010031186735069e-5,(float)-4.74755620890086638e-5,(float)
	    -4.55813058138628452e-5,(float)-4.33309644511266036e-5,(float)
	    -4.09230193157750364e-5,(float)-3.84822638603221274e-5,(float)
	    -3.60857167535410501e-5,(float)-3.37793306123367417e-5,(float)
	    -3.15888560772109621e-5,(float)-2.95269561750807315e-5,(float)
	    -2.75978914828335759e-5,(float)-2.58006174666883713e-5,(float)
	    -2.413083567612802e-5,(float)-2.25823509518346033e-5,(float)
	    -2.11479656768912971e-5,(float)-1.98200638885294927e-5,(float)
	    -1.85909870801065077e-5,(float)-1.74532699844210224e-5,(float)
	    -1.63997823854497997e-5,(float)-4.74617796559959808e-4,(float)
	    -4.77864567147321487e-4,(float)-3.20390228067037603e-4,(float)
	    -1.61105016119962282e-4,(float)-4.25778101285435204e-5,(float)
	    3.44571294294967503e-5,(float)7.97092684075674924e-5,(float)
	    1.031382367082722e-4,(float)1.12466775262204158e-4,(float)
	    1.13103642108481389e-4,(float)1.08651634848774268e-4,(float)
	    1.01437951597661973e-4,(float)9.29298396593363896e-5,(float)
	    8.40293133016089978e-5,(float)7.52727991349134062e-5,(float)
	    6.69632521975730872e-5,(float)5.92564547323194704e-5,(float)
	    5.22169308826975567e-5,(float)4.58539485165360646e-5,(float)
	    4.01445513891486808e-5,(float)3.50481730031328081e-5,(float)
	    3.05157995034346659e-5,(float)2.64956119950516039e-5,(float)
	    2.29363633690998152e-5,(float)1.97893056664021636e-5,(float)
	    1.70091984636412623e-5,(float)1.45547428261524004e-5,(float)
	    1.23886640995878413e-5,(float)1.04775876076583236e-5,(float)
	    8.79179954978479373e-6,(float)7.36465810572578444e-4,(float)
	    8.72790805146193976e-4,(float)6.22614862573135066e-4,(float)
	    2.85998154194304147e-4,(float)3.84737672879366102e-6,(float)
	    -1.87906003636971558e-4,(float)-2.97603646594554535e-4,(float)
	    -3.45998126832656348e-4,(float)-3.53382470916037712e-4,(float)
	    -3.35715635775048757e-4,(float)-3.04321124789039809e-4,(float)
	    -2.66722723047612821e-4,(float)-2.27654214122819527e-4,(float)
	    -1.89922611854562356e-4,(float)-1.5505891859909387e-4,(float)
	    -1.2377824076187363e-4,(float)-9.62926147717644187e-5,(float)
	    -7.25178327714425337e-5,(float)-5.22070028895633801e-5,(float)
	    -3.50347750511900522e-5,(float)-2.06489761035551757e-5,(float)
	    -8.70106096849767054e-6,(float)1.1369868667510029e-6,(float)
	    9.16426474122778849e-6,(float)1.5647778542887262e-5,(float)
	    2.08223629482466847e-5,(float)2.48923381004595156e-5,(float)
	    2.80340509574146325e-5,(float)3.03987774629861915e-5,(float)
	    3.21156731406700616e-5,(float)-.00180182191963885708,(float)
	    -.00243402962938042533,(float)-.00183422663549856802,(float)
	    -7.62204596354009765e-4,(float)2.39079475256927218e-4,(float)
	    9.49266117176881141e-4,(float).00134467449701540359,(float)
	    .00148457495259449178,(float).00144732339830617591,(float)
	    .00130268261285657186,(float).00110351597375642682,(float)
	    8.86047440419791759e-4,(float)6.73073208165665473e-4,(float)
	    4.77603872856582378e-4,(float)3.05991926358789362e-4,(float)
	    1.6031569459472163e-4,(float)4.00749555270613286e-5,(float)
	    -5.66607461635251611e-5,(float)-1.32506186772982638e-4,(float)
	    -1.90296187989614057e-4,(float)-2.32811450376937408e-4,(float)
	    -2.62628811464668841e-4,(float)-2.82050469867598672e-4,(float)
	    -2.93081563192861167e-4,(float)-2.97435962176316616e-4,(float)
	    -2.96557334239348078e-4,(float)-2.91647363312090861e-4,(float)
	    -2.83696203837734166e-4,(float)-2.73512317095673346e-4,(float)
	    -2.6175015580676858e-4,(float).00638585891212050914,(float)
	    .00962374215806377941,(float).00761878061207001043,(float)
	    .00283219055545628054,(float)-.0020984135201272009,(float)
	    -.00573826764216626498,(float)-.0077080424449541462,(float)
	    -.00821011692264844401,(float)-.00765824520346905413,(float)
	    -.00647209729391045177,(float)-.00499132412004966473,(float)
	    -.0034561228971313328,(float)-.00201785580014170775,(float)
	    -7.59430686781961401e-4,(float)2.84173631523859138e-4,(float)
	    .00110891667586337403,(float).00172901493872728771,(float)
	    .00216812590802684701,(float).00245357710494539735,(float)
	    .00261281821058334862,(float).00267141039656276912,(float)
	    .0026520307339598043,(float).00257411652877287315,(float)
	    .00245389126236094427,(float).00230460058071795494,(float)
	    .00213684837686712662,(float).00195896528478870911,(float)
	    .00177737008679454412,(float).00159690280765839059,(float)
	    .00142111975664438546 };
    static real gama[30] = { (float).629960524947436582,(float)
	    .251984209978974633,(float).154790300415655846,(float)
	    .110713062416159013,(float).0857309395527394825,(float)
	    .0697161316958684292,(float).0586085671893713576,(float)
	    .0504698873536310685,(float).0442600580689154809,(float)
	    .0393720661543509966,(float).0354283195924455368,(float)
	    .0321818857502098231,(float).0294646240791157679,(float)
	    .0271581677112934479,(float).0251768272973861779,(float)
	    .0234570755306078891,(float).0219508390134907203,(float)
	    .020621082823564624,(float).0194388240897880846,(float)
	    .0183810633800683158,(float).0174293213231963172,(float)
	    .0165685837786612353,(float).0157865285987918445,(float)
	    .0150729501494095594,(float).0144193250839954639,(float)
	    .0138184805735341786,(float).0132643378994276568,(float)
	    .0127517121970498651,(float).0122761545318762767,(float)
	    .0118338262398482403 };
    static real ex1 = (float).333333333333333333;
    static real ex2 = (float).666666666666666667;
    static real hpi = (float)1.57079632679489662;

    /* System generated locals */
    integer i__1, i__2, i__3;
    real r__1;
    doublereal d__1, d__2;
    complex q__1, q__2, q__3, q__4, q__5;

    /* Builtin functions */
    double r_imag(complex *), log(doublereal), pow_dd(doublereal *, 
	    doublereal *), c_abs(complex *);
    void c_sqrt(complex *, complex *), c_div(complex *, complex *, complex *),
	     c_log(complex *, complex *);
    double atan(doublereal), cos(doublereal), sin(doublereal);

    /* Local variables */
    static integer j, k, l, m;
    static complex p[30], w;
    static integer l1, l2;
    static complex t2, w2;
    static real ac, ap[30];
    static complex cr[14], dr[14], za, zb, zc;
    static integer is, jr;
    static real pp, wi;
    static integer ju, ks, lr;
    static complex up[14];
    static real wr, aw2;
    static integer kp1;
    static real ang, fn13, fn23;
    static integer ias, ibs;
    static real zci;
    static complex tfn;
    static real zcr;
    static complex zth;
    static integer lrp1;
    static complex rfn13, cfnu;
    static real atol, btol;
    static integer kmax;
    static complex zeta, ptfn, suma, sumb;
    static real azth, rfnu, zthi, test, tsti;
    static complex rzth;
    static real zthr, tstr, rfnu2, zetai, asumi, bsumi, zetar, asumr, bsumr;
    static complex rtzta, przth;
    extern doublereal r1mach_(integer *);

/* ***BEGIN PROLOGUE  CUNHJ */
/* ***REFER TO  CBESI,CBESK */

/*     REFERENCES */
/*         HANDBOOK OF MATHEMATICAL FUNCTIONS BY M. ABRAMOWITZ AND I.A. */
/*         STEGUN, AMS55, NATIONAL BUREAU OF STANDARDS, 1965, CHAPTER 9. */

/*         ASYMPTOTICS AND SPECIAL FUNCTIONS BY F.W.J. OLVER, ACADEMIC */
/*         PRESS, N.Y., 1974, PAGE 420 */

/*     ABSTRACT */
/*         CUNHJ COMPUTES PARAMETERS FOR BESSEL FUNCTIONS C(FNU,Z) = */
/*         J(FNU,Z), Y(FNU,Z) OR H(I,FNU,Z) I=1,2 FOR LARGE ORDERS FNU */
/*         BY MEANS OF THE UNIFORM ASYMPTOTIC EXPANSION */

/*         C(FNU,Z)=C1*PHI*( ASUM*AIRY(ARG) + C2*BSUM*DAIRY(ARG) ) */

/*         FOR PROPER CHOICES OF C1, C2, AIRY AND DAIRY WHERE AIRY IS */
/*         AN AIRY FUNCTION AND DAIRY IS ITS DERIVATIVE. */

/*               (2/3)*FNU*ZETA**1.5 = ZETA1-ZETA2, */

/*         ZETA1=0.5*FNU*CLOG((1+W)/(1-W)), ZETA2=FNU*W FOR SCALING */
/*         PURPOSES IN AIRY FUNCTIONS FROM CAIRY OR CBIRY. */

/*         MCONJ=SIGN OF AIMAG(Z), BUT IS AMBIGUOUS WHEN Z IS REAL AND */
/*         MUST BE SPECIFIED. IPMTR=0 RETURNS ALL PARAMETERS. IPMTR= */
/*         1 COMPUTES ALL EXCEPT ASUM AND BSUM. */

/* ***ROUTINES CALLED  (NONE) */
/* ***END PROLOGUE  CUNHJ */

    rfnu = (float)1. / *fnu;
/*     ZB = Z*CMPLX(RFNU,0.0E0) */
/* ----------------------------------------------------------------------- */
/*     OVERFLOW TEST (Z/FNU TOO SMALL) */
/* ----------------------------------------------------------------------- */
    tstr = z__->r;
    tsti = r_imag(z__);
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
    arg->r = cone.r, arg->i = cone.i;
    return 0;
L15:
    q__2.r = rfnu, q__2.i = (float)0.;
    q__1.r = z__->r * q__2.r - z__->i * q__2.i, q__1.i = z__->r * q__2.i + 
	    z__->i * q__2.r;
    zb.r = q__1.r, zb.i = q__1.i;
    rfnu2 = rfnu * rfnu;
/* ----------------------------------------------------------------------- */
/*     COMPUTE IN THE FOURTH QUADRANT */
/* ----------------------------------------------------------------------- */
    d__1 = (doublereal) (*fnu);
    d__2 = (doublereal) ex1;
    fn13 = pow_dd(&d__1, &d__2);
    fn23 = fn13 * fn13;
    r__1 = (float)1. / fn13;
    q__1.r = r__1, q__1.i = (float)0.;
    rfn13.r = q__1.r, rfn13.i = q__1.i;
    q__2.r = zb.r * zb.r - zb.i * zb.i, q__2.i = zb.r * zb.i + zb.i * zb.r;
    q__1.r = cone.r - q__2.r, q__1.i = cone.i - q__2.i;
    w2.r = q__1.r, w2.i = q__1.i;
    aw2 = c_abs(&w2);
    if (aw2 > (float).25) {
	goto L130;
    }
/* ----------------------------------------------------------------------- */
/*     POWER SERIES FOR CABS(W2).LE.0.25E0 */
/* ----------------------------------------------------------------------- */
    k = 1;
    p[0].r = cone.r, p[0].i = cone.i;
    q__1.r = gama[0], q__1.i = (float)0.;
    suma.r = q__1.r, suma.i = q__1.i;
    ap[0] = (float)1.;
    if (aw2 < *tol) {
	goto L20;
    }
    for (k = 2; k <= 30; ++k) {
	i__1 = k - 1;
	i__2 = k - 2;
	q__1.r = p[i__2].r * w2.r - p[i__2].i * w2.i, q__1.i = p[i__2].r * 
		w2.i + p[i__2].i * w2.r;
	p[i__1].r = q__1.r, p[i__1].i = q__1.i;
	i__1 = k - 1;
	i__2 = k - 1;
	q__3.r = gama[i__2], q__3.i = (float)0.;
	q__2.r = p[i__1].r * q__3.r - p[i__1].i * q__3.i, q__2.i = p[i__1].r *
		 q__3.i + p[i__1].i * q__3.r;
	q__1.r = suma.r + q__2.r, q__1.i = suma.i + q__2.i;
	suma.r = q__1.r, suma.i = q__1.i;
	ap[k - 1] = ap[k - 2] * aw2;
	if (ap[k - 1] < *tol) {
	    goto L20;
	}
/* L10: */
    }
    k = 30;
L20:
    kmax = k;
    q__1.r = w2.r * suma.r - w2.i * suma.i, q__1.i = w2.r * suma.i + w2.i * 
	    suma.r;
    zeta.r = q__1.r, zeta.i = q__1.i;
    q__2.r = fn23, q__2.i = (float)0.;
    q__1.r = zeta.r * q__2.r - zeta.i * q__2.i, q__1.i = zeta.r * q__2.i + 
	    zeta.i * q__2.r;
    arg->r = q__1.r, arg->i = q__1.i;
    c_sqrt(&q__1, &suma);
    za.r = q__1.r, za.i = q__1.i;
    c_sqrt(&q__2, &w2);
    q__3.r = *fnu, q__3.i = (float)0.;
    q__1.r = q__2.r * q__3.r - q__2.i * q__3.i, q__1.i = q__2.r * q__3.i + 
	    q__2.i * q__3.r;
    zeta2->r = q__1.r, zeta2->i = q__1.i;
    q__4.r = zeta.r * za.r - zeta.i * za.i, q__4.i = zeta.r * za.i + zeta.i * 
	    za.r;
    q__5.r = ex2, q__5.i = (float)0.;
    q__3.r = q__4.r * q__5.r - q__4.i * q__5.i, q__3.i = q__4.r * q__5.i + 
	    q__4.i * q__5.r;
    q__2.r = cone.r + q__3.r, q__2.i = cone.i + q__3.i;
    q__1.r = zeta2->r * q__2.r - zeta2->i * q__2.i, q__1.i = zeta2->r * 
	    q__2.i + zeta2->i * q__2.r;
    zeta1->r = q__1.r, zeta1->i = q__1.i;
    q__1.r = za.r + za.r, q__1.i = za.i + za.i;
    za.r = q__1.r, za.i = q__1.i;
    c_sqrt(&q__2, &za);
    q__1.r = q__2.r * rfn13.r - q__2.i * rfn13.i, q__1.i = q__2.r * rfn13.i + 
	    q__2.i * rfn13.r;
    phi->r = q__1.r, phi->i = q__1.i;
    if (*ipmtr == 1) {
	goto L120;
    }
/* ----------------------------------------------------------------------- */
/*     SUM SERIES FOR ASUM AND BSUM */
/* ----------------------------------------------------------------------- */
    sumb.r = czero.r, sumb.i = czero.i;
    i__1 = kmax;
    for (k = 1; k <= i__1; ++k) {
	i__2 = k - 1;
	i__3 = k - 1;
	q__3.r = beta[i__3], q__3.i = (float)0.;
	q__2.r = p[i__2].r * q__3.r - p[i__2].i * q__3.i, q__2.i = p[i__2].r *
		 q__3.i + p[i__2].i * q__3.r;
	q__1.r = sumb.r + q__2.r, q__1.i = sumb.i + q__2.i;
	sumb.r = q__1.r, sumb.i = q__1.i;
/* L30: */
    }
    asum->r = czero.r, asum->i = czero.i;
    bsum->r = sumb.r, bsum->i = sumb.i;
    l1 = 0;
    l2 = 30;
    btol = *tol * c_abs(bsum);
    atol = *tol;
    pp = (float)1.;
    ias = 0;
    ibs = 0;
    if (rfnu2 < *tol) {
	goto L110;
    }
    for (is = 2; is <= 7; ++is) {
	atol /= rfnu2;
	pp *= rfnu2;
	if (ias == 1) {
	    goto L60;
	}
	suma.r = czero.r, suma.i = czero.i;
	i__1 = kmax;
	for (k = 1; k <= i__1; ++k) {
	    m = l1 + k;
	    i__2 = k - 1;
	    i__3 = m - 1;
	    q__3.r = alfa[i__3], q__3.i = (float)0.;
	    q__2.r = p[i__2].r * q__3.r - p[i__2].i * q__3.i, q__2.i = p[i__2]
		    .r * q__3.i + p[i__2].i * q__3.r;
	    q__1.r = suma.r + q__2.r, q__1.i = suma.i + q__2.i;
	    suma.r = q__1.r, suma.i = q__1.i;
	    if (ap[k - 1] < atol) {
		goto L50;
	    }
/* L40: */
	}
L50:
	q__3.r = pp, q__3.i = (float)0.;
	q__2.r = suma.r * q__3.r - suma.i * q__3.i, q__2.i = suma.r * q__3.i 
		+ suma.i * q__3.r;
	q__1.r = asum->r + q__2.r, q__1.i = asum->i + q__2.i;
	asum->r = q__1.r, asum->i = q__1.i;
	if (pp < *tol) {
	    ias = 1;
	}
L60:
	if (ibs == 1) {
	    goto L90;
	}
	sumb.r = czero.r, sumb.i = czero.i;
	i__1 = kmax;
	for (k = 1; k <= i__1; ++k) {
	    m = l2 + k;
	    i__2 = k - 1;
	    i__3 = m - 1;
	    q__3.r = beta[i__3], q__3.i = (float)0.;
	    q__2.r = p[i__2].r * q__3.r - p[i__2].i * q__3.i, q__2.i = p[i__2]
		    .r * q__3.i + p[i__2].i * q__3.r;
	    q__1.r = sumb.r + q__2.r, q__1.i = sumb.i + q__2.i;
	    sumb.r = q__1.r, sumb.i = q__1.i;
	    if (ap[k - 1] < atol) {
		goto L80;
	    }
/* L70: */
	}
L80:
	q__3.r = pp, q__3.i = (float)0.;
	q__2.r = sumb.r * q__3.r - sumb.i * q__3.i, q__2.i = sumb.r * q__3.i 
		+ sumb.i * q__3.r;
	q__1.r = bsum->r + q__2.r, q__1.i = bsum->i + q__2.i;
	bsum->r = q__1.r, bsum->i = q__1.i;
	if (pp < btol) {
	    ibs = 1;
	}
L90:
	if (ias == 1 && ibs == 1) {
	    goto L110;
	}
	l1 += 30;
	l2 += 30;
/* L100: */
    }
L110:
    q__1.r = asum->r + cone.r, q__1.i = asum->i + cone.i;
    asum->r = q__1.r, asum->i = q__1.i;
    pp = rfnu * rfn13.r;
    q__2.r = pp, q__2.i = (float)0.;
    q__1.r = bsum->r * q__2.r - bsum->i * q__2.i, q__1.i = bsum->r * q__2.i + 
	    bsum->i * q__2.r;
    bsum->r = q__1.r, bsum->i = q__1.i;
L120:
    return 0;
/* ----------------------------------------------------------------------- */
/*     CABS(W2).GT.0.25E0 */
/* ----------------------------------------------------------------------- */
L130:
    c_sqrt(&q__1, &w2);
    w.r = q__1.r, w.i = q__1.i;
    wr = w.r;
    wi = r_imag(&w);
    if (wr < (float)0.) {
	wr = (float)0.;
    }
    if (wi < (float)0.) {
	wi = (float)0.;
    }
    q__1.r = wr, q__1.i = wi;
    w.r = q__1.r, w.i = q__1.i;
    q__2.r = cone.r + w.r, q__2.i = cone.i + w.i;
    c_div(&q__1, &q__2, &zb);
    za.r = q__1.r, za.i = q__1.i;
    c_log(&q__1, &za);
    zc.r = q__1.r, zc.i = q__1.i;
    zcr = zc.r;
    zci = r_imag(&zc);
    if (zci < (float)0.) {
	zci = (float)0.;
    }
    if (zci > hpi) {
	zci = hpi;
    }
    if (zcr < (float)0.) {
	zcr = (float)0.;
    }
    q__1.r = zcr, q__1.i = zci;
    zc.r = q__1.r, zc.i = q__1.i;
    q__2.r = zc.r - w.r, q__2.i = zc.i - w.i;
    q__1.r = q__2.r * (float)1.5 - q__2.i * (float)0., q__1.i = q__2.r * (
	    float)0. + q__2.i * (float)1.5;
    zth.r = q__1.r, zth.i = q__1.i;
    q__1.r = *fnu, q__1.i = (float)0.;
    cfnu.r = q__1.r, cfnu.i = q__1.i;
    q__1.r = zc.r * cfnu.r - zc.i * cfnu.i, q__1.i = zc.r * cfnu.i + zc.i * 
	    cfnu.r;
    zeta1->r = q__1.r, zeta1->i = q__1.i;
    q__1.r = w.r * cfnu.r - w.i * cfnu.i, q__1.i = w.r * cfnu.i + w.i * 
	    cfnu.r;
    zeta2->r = q__1.r, zeta2->i = q__1.i;
    azth = c_abs(&zth);
    zthr = zth.r;
    zthi = r_imag(&zth);
    ang = thpi;
    if (zthr >= (float)0. && zthi < (float)0.) {
	goto L140;
    }
    ang = hpi;
    if (zthr == (float)0.) {
	goto L140;
    }
    ang = atan(zthi / zthr);
    if (zthr < (float)0.) {
	ang += pi;
    }
L140:
    d__1 = (doublereal) azth;
    d__2 = (doublereal) ex2;
    pp = pow_dd(&d__1, &d__2);
    ang *= ex2;
    zetar = pp * cos(ang);
    zetai = pp * sin(ang);
    if (zetai < (float)0.) {
	zetai = (float)0.;
    }
    q__1.r = zetar, q__1.i = zetai;
    zeta.r = q__1.r, zeta.i = q__1.i;
    q__2.r = fn23, q__2.i = (float)0.;
    q__1.r = zeta.r * q__2.r - zeta.i * q__2.i, q__1.i = zeta.r * q__2.i + 
	    zeta.i * q__2.r;
    arg->r = q__1.r, arg->i = q__1.i;
    c_div(&q__1, &zth, &zeta);
    rtzta.r = q__1.r, rtzta.i = q__1.i;
    c_div(&q__1, &rtzta, &w);
    za.r = q__1.r, za.i = q__1.i;
    q__3.r = za.r + za.r, q__3.i = za.i + za.i;
    c_sqrt(&q__2, &q__3);
    q__1.r = q__2.r * rfn13.r - q__2.i * rfn13.i, q__1.i = q__2.r * rfn13.i + 
	    q__2.i * rfn13.r;
    phi->r = q__1.r, phi->i = q__1.i;
    if (*ipmtr == 1) {
	goto L120;
    }
    q__2.r = rfnu, q__2.i = (float)0.;
    c_div(&q__1, &q__2, &w);
    tfn.r = q__1.r, tfn.i = q__1.i;
    q__2.r = rfnu, q__2.i = (float)0.;
    c_div(&q__1, &q__2, &zth);
    rzth.r = q__1.r, rzth.i = q__1.i;
    q__2.r = ar[1], q__2.i = (float)0.;
    q__1.r = rzth.r * q__2.r - rzth.i * q__2.i, q__1.i = rzth.r * q__2.i + 
	    rzth.i * q__2.r;
    zc.r = q__1.r, zc.i = q__1.i;
    c_div(&q__1, &cone, &w2);
    t2.r = q__1.r, t2.i = q__1.i;
    q__4.r = c__[1], q__4.i = (float)0.;
    q__3.r = t2.r * q__4.r - t2.i * q__4.i, q__3.i = t2.r * q__4.i + t2.i * 
	    q__4.r;
    q__5.r = c__[2], q__5.i = (float)0.;
    q__2.r = q__3.r + q__5.r, q__2.i = q__3.i + q__5.i;
    q__1.r = q__2.r * tfn.r - q__2.i * tfn.i, q__1.i = q__2.r * tfn.i + 
	    q__2.i * tfn.r;
    up[1].r = q__1.r, up[1].i = q__1.i;
    q__1.r = up[1].r + zc.r, q__1.i = up[1].i + zc.i;
    bsum->r = q__1.r, bsum->i = q__1.i;
    asum->r = czero.r, asum->i = czero.i;
    if (rfnu < *tol) {
	goto L220;
    }
    przth.r = rzth.r, przth.i = rzth.i;
    ptfn.r = tfn.r, ptfn.i = tfn.i;
    up[0].r = cone.r, up[0].i = cone.i;
    pp = (float)1.;
    bsumr = bsum->r;
    bsumi = r_imag(bsum);
    btol = *tol * (dabs(bsumr) + dabs(bsumi));
    ks = 0;
    kp1 = 2;
    l = 3;
    ias = 0;
    ibs = 0;
    for (lr = 2; lr <= 12; lr += 2) {
	lrp1 = lr + 1;
/* ----------------------------------------------------------------------- */
/*     COMPUTE TWO ADDITIONAL CR, DR, AND UP FOR TWO MORE TERMS IN */
/*     NEXT SUMA AND SUMB */
/* ----------------------------------------------------------------------- */
	i__1 = lrp1;
	for (k = lr; k <= i__1; ++k) {
	    ++ks;
	    ++kp1;
	    ++l;
	    i__2 = l - 1;
	    q__1.r = c__[i__2], q__1.i = (float)0.;
	    za.r = q__1.r, za.i = q__1.i;
	    i__2 = kp1;
	    for (j = 2; j <= i__2; ++j) {
		++l;
		q__2.r = za.r * t2.r - za.i * t2.i, q__2.i = za.r * t2.i + 
			za.i * t2.r;
		i__3 = l - 1;
		q__3.r = c__[i__3], q__3.i = (float)0.;
		q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
		za.r = q__1.r, za.i = q__1.i;
/* L150: */
	    }
	    q__1.r = ptfn.r * tfn.r - ptfn.i * tfn.i, q__1.i = ptfn.r * tfn.i 
		    + ptfn.i * tfn.r;
	    ptfn.r = q__1.r, ptfn.i = q__1.i;
	    i__2 = kp1 - 1;
	    q__1.r = ptfn.r * za.r - ptfn.i * za.i, q__1.i = ptfn.r * za.i + 
		    ptfn.i * za.r;
	    up[i__2].r = q__1.r, up[i__2].i = q__1.i;
	    i__2 = ks - 1;
	    i__3 = ks;
	    q__2.r = br[i__3], q__2.i = (float)0.;
	    q__1.r = przth.r * q__2.r - przth.i * q__2.i, q__1.i = przth.r * 
		    q__2.i + przth.i * q__2.r;
	    cr[i__2].r = q__1.r, cr[i__2].i = q__1.i;
	    q__1.r = przth.r * rzth.r - przth.i * rzth.i, q__1.i = przth.r * 
		    rzth.i + przth.i * rzth.r;
	    przth.r = q__1.r, przth.i = q__1.i;
	    i__2 = ks - 1;
	    i__3 = ks + 1;
	    q__2.r = ar[i__3], q__2.i = (float)0.;
	    q__1.r = przth.r * q__2.r - przth.i * q__2.i, q__1.i = przth.r * 
		    q__2.i + przth.i * q__2.r;
	    dr[i__2].r = q__1.r, dr[i__2].i = q__1.i;
/* L160: */
	}
	pp *= rfnu2;
	if (ias == 1) {
	    goto L180;
	}
	i__1 = lrp1 - 1;
	suma.r = up[i__1].r, suma.i = up[i__1].i;
	ju = lrp1;
	i__1 = lr;
	for (jr = 1; jr <= i__1; ++jr) {
	    --ju;
	    i__2 = jr - 1;
	    i__3 = ju - 1;
	    q__2.r = cr[i__2].r * up[i__3].r - cr[i__2].i * up[i__3].i, 
		    q__2.i = cr[i__2].r * up[i__3].i + cr[i__2].i * up[i__3]
		    .r;
	    q__1.r = suma.r + q__2.r, q__1.i = suma.i + q__2.i;
	    suma.r = q__1.r, suma.i = q__1.i;
/* L170: */
	}
	q__1.r = asum->r + suma.r, q__1.i = asum->i + suma.i;
	asum->r = q__1.r, asum->i = q__1.i;
	asumr = asum->r;
	asumi = r_imag(asum);
	test = dabs(asumr) + dabs(asumi);
	if (pp < *tol && test < *tol) {
	    ias = 1;
	}
L180:
	if (ibs == 1) {
	    goto L200;
	}
	i__1 = lr + 1;
	i__2 = lrp1 - 1;
	q__2.r = up[i__2].r * zc.r - up[i__2].i * zc.i, q__2.i = up[i__2].r * 
		zc.i + up[i__2].i * zc.r;
	q__1.r = up[i__1].r + q__2.r, q__1.i = up[i__1].i + q__2.i;
	sumb.r = q__1.r, sumb.i = q__1.i;
	ju = lrp1;
	i__1 = lr;
	for (jr = 1; jr <= i__1; ++jr) {
	    --ju;
	    i__2 = jr - 1;
	    i__3 = ju - 1;
	    q__2.r = dr[i__2].r * up[i__3].r - dr[i__2].i * up[i__3].i, 
		    q__2.i = dr[i__2].r * up[i__3].i + dr[i__2].i * up[i__3]
		    .r;
	    q__1.r = sumb.r + q__2.r, q__1.i = sumb.i + q__2.i;
	    sumb.r = q__1.r, sumb.i = q__1.i;
/* L190: */
	}
	q__1.r = bsum->r + sumb.r, q__1.i = bsum->i + sumb.i;
	bsum->r = q__1.r, bsum->i = q__1.i;
	bsumr = bsum->r;
	bsumi = r_imag(bsum);
	test = dabs(bsumr) + dabs(bsumi);
	if (pp < btol && test < *tol) {
	    ibs = 1;
	}
L200:
	if (ias == 1 && ibs == 1) {
	    goto L220;
	}
/* L210: */
    }
L220:
    q__1.r = asum->r + cone.r, q__1.i = asum->i + cone.i;
    asum->r = q__1.r, asum->i = q__1.i;
    q__3.r = -bsum->r, q__3.i = -bsum->i;
    q__2.r = q__3.r * rfn13.r - q__3.i * rfn13.i, q__2.i = q__3.r * rfn13.i + 
	    q__3.i * rfn13.r;
    c_div(&q__1, &q__2, &rtzta);
    bsum->r = q__1.r, bsum->i = q__1.i;
    goto L120;
} /* cunhj_ */

#ifdef __cplusplus
	}
#endif
