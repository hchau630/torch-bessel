#pragma once

#include <iostream>
#include <c10/macros/Macros.h>
#include <c10/util/complex.h>
#include "cbesk/cbesk_blah.h"

inline C10_HOST_DEVICE c10::complex<float> cbesk_hihi(float nu, c10::complex<float> z) {
  complex cz = {z.real(), z.imag()};
  integer kode = 1;
  integer n = 1;
  complex cy[1];
  integer nz;
  integer ierr;
  if (nu < 0) {
    nu = -nu;
  }  // cbesk_blah expects nu >= 0 and K_{-nu}(z) = K_{nu}(z)
  cbesk_blah(&cz, &nu, &kode, &n, cy, &nz, &ierr);
//   printf("nz: %ld, ierr: %ld\n", nz, ierr);
//   printf("real: %.10f, imag: %.10f\n", cy[0].r, cy[0].i);
  return c10::complex<float>(cy[0].r, cy[0].i);
}
