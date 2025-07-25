#pragma once

#include <iostream>
#include <c10/macros/Macros.h>
#include <c10/util/complex.h>
#include "amos.h"


template <typename T>
inline C10_HOST_DEVICE c10::complex<T> modified_bessel_k0_complex_forward(c10::complex<T> z) {
    c10::complex<T> cy(NAN, NAN);
    if (std::isnan(std::real(z)) || isnan(std::imag(z))) {
       return cy;
    }

    int ierr;
    amos::besk0(z, 1, &cy, &ierr);
    if (ierr == 2) {
        if (std::real(z) >= 0 && std::imag(z) == 0) {
            /* overflow */
            cy = INFINITY;
        }
    }

    return cy;
}

template <typename T>
inline C10_HOST_DEVICE void modified_bessel_k0_complex_forward_backward(c10::complex<T> z, c10::complex<T>* cy) {
    cy[0] = c10::complex<T>(NAN, NAN);
    cy[1] = c10::complex<T>(NAN, NAN);
    if (std::isnan(std::real(z)) || isnan(std::imag(z))) {
        return;
    }

    int ierr;
    amos::besk0(z, 2, cy, &ierr);

    /* dK_0(z)/dz = -K_1(z), conjugation needed for PyTorch gradient computation */
    cy[1] = -std::conj(cy[1]);

    if (ierr == 2) {
        if (std::real(z) >= 0 && std::imag(z) == 0) {
            /* overflow */
            cy[0] = INFINITY;
            cy[1] = INFINITY;
        }
    }

    return;
}

template <typename T>
inline C10_HOST_DEVICE c10::complex<T> modified_bessel_k1_complex_forward(c10::complex<T> z) {
    c10::complex<T> cy[2];
    cy[1] = c10::complex<T>(NAN, NAN);
    if (std::isnan(std::real(z)) || isnan(std::imag(z))) {
        return cy[1];
    }

    int ierr;
    amos::besk0(z, 2, cy, &ierr);

    if (ierr == 2) {
        if (std::real(z) >= 0 && std::imag(z) == 0) {
            /* overflow */
            cy[1] = INFINITY;
        }
    }

    return cy[1];
}
