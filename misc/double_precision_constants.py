import math

d1mach = [
    2.2250738585072014e-308,  # np.finfo(np.float64).tiny
    1.7976931348623157e308,  # np.finfo(np.float64).max
    1.1102230246251565e-16,  # 0.5 * np.finfo(np.float64).eps
    2.220446049250313e-16,  # np.finfo(np.float64).eps
    0.3010299956639812,  # np.log10(2)
]
i1mach = [
    5,  # standard input
    6,  # standard output
    7,  # standard punch
    0,  # standard error
    32,  # bits per integer
    4,  # sizeof(int)
    2,  # base for integers
    31,  # digits of integer base
    2147483647,  # LONG MAX 2**31 - 1
    2,  # FLT_RADIX
    24,  # FLT_MANT_DIG
    -126,  # FLT_MIN_EXP
    128,  # FLT_MAX_EXP
    53,  # DBL_MANT_DIG
    -1021,  # DBL_MIN_EXP
    1024,  # DBL_MAX_EXP
]
fnu = 0
nn = 2
kode = 1

# besk
tol = max(d1mach[3], 1e-18)
k1 = i1mach[14]
k2 = i1mach[15]
r1m5 = d1mach[4]
k = abs(k2) if abs(k1) > abs(k2) else abs(k1)
elim = 2.303 * (k * r1m5 - 3.0)
k1 = i1mach[13] - 1
aa = r1m5 * k1
dig = min(aa, 18.0)
aa *= 2.303
alim = elim + max(-aa, -41.45)
fnul = 10.0 + 6.0 * (dig - 3.0)
rl = 1.2 * dig + 3.0
# az = abs(z)
fn = fnu + (nn - 1)
aa = 0.5 / tol
bb = i1mach[8] * 0.5
aa = min(aa, bb)

print(f"{fnu=}, {nn=}")
print(f"{fnul=}, {fn=}, {rl=}")
print(f"{tol=}, {alim=}, {elim=}")
print(f"{aa=}, {bb=}")
aa = math.sqrt(aa)
print(f"{aa=}")
ufl = d1mach[0] * 1.0e3
print(f"{ufl=}")

# bknu
kmax = 30
r1 = 2.0
pi = 3.14159265358979324
rthpi = 1.25331413731550025
spi = 1.90985931710274403
hpi = 1.57079632679489662
fpi = 1.89769999331517738
tth = 2.0 / 3.0
cc = [
    5.77215664901532861e-01,
    -4.20026350340952355e-02,
    -4.21977345555443367e-02,
    7.21894324666309954e-03,
    -2.15241674114950973e-04,
    -2.01348547807882387e-05,
    1.13302723198169588e-06,
    6.11609510448141582e-09,
]

cscl = 1.0 / tol
crsc = tol
css = [cscl, 1.0, crsc]
csr = [crsc, 1.0, cscl]
bry = [1e3 * d1mach[0] / tol, tol / (1e3 * d1mach[0]), d1mach[1]]
nz = 0
iflag = 0
koded = kode
# rz = 2.0 / z
inu = (int)(fnu + 0.5)
dnu = fnu - inu

print(f"{1/tol=}")
print(f"{css=}")
print(f"{csr=}")
print(f"{bry=}")
print(f"{inu=}, {dnu=}")
print(f"{koded=}")
print(f"{(abs(dnu) > tol)=}")

s1 = 0.0
s2 = 0.0
ck = 0.0
dnu2 = 0.0

ak = abs(math.cos(math.pi * dnu))
fhs = abs(0.25 - dnu2)

print(f"{ak=}, {fhs=}")

t1 = (i1mach[13] - 1) * d1mach[4] * (math.log(10) / math.log(2))
t1 = min(max(t1, 12.0), 60.0)
t2 = tth * t1 - 6.0

print(f"{t1=}, {t2=}")
