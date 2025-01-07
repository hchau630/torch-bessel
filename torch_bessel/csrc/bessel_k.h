#pragma once

#include <iostream>
#include <c10/macros/Macros.h>
#include <c10/util/complex.h>
#include "amos.h"


inline C10_HOST_DEVICE c10::complex<double> bessel_k0_forward(c10::complex<double> z) {
    c10::complex<double> cy(NAN, NAN);
    if (std::isnan(std::real(z)) || isnan(std::imag(z))) {
       return cy;
    }

    int ierr;
    int nz = amos::besk0(z, 1, &cy, &ierr);
    if (ierr == 2) {
        if (std::real(z) >= 0 && std::imag(z) == 0) {
            /* overflow */
            cy = INFINITY;
        }
    }

    return cy;
}

inline C10_HOST_DEVICE void bessel_k0_forward_backward(c10::complex<double> z, c10::complex<double>* cy) {
    if (std::isnan(std::real(z)) || isnan(std::imag(z))) {
        cy[0] = c10::complex<double>(NAN, NAN);
        cy[1] = c10::complex<double>(NAN, NAN);
        return;
    }

    int ierr;
    int nz = amos::besk0(z, 2, cy, &ierr);

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

inline C10_HOST_DEVICE c10::complex<float> bessel_k0_forward(c10::complex<float> z) {
    return static_cast<c10::complex<float>>(bessel_k0_forward(static_cast<c10::complex<double>>(z)));
}

inline C10_HOST_DEVICE void bessel_k0_forward_backward(c10::complex<float> z, c10::complex<float>* cy) {
    c10::complex<double> cy_[2];
    bessel_k0_forward_backward(static_cast<c10::complex<double>>(z), cy_);
    cy[0] = static_cast<c10::complex<float>>(cy_[0]);
    cy[1] = static_cast<c10::complex<float>>(cy_[1]);
    return;
}

template <typename T>
inline C10_HOST_DEVICE T bessel_k0_forward(T z) {
    if (z < 0) {
        return std::numeric_limits<T>::quiet_NaN();
    }

    if (z == 0) {
        return std::numeric_limits<T>::infinity();
    }

    if (z > 710) {
        /* Underflow. See uniform expansion https://dlmf.nist.gov/10.41
         * This condition is not a strict bound (it can underflow earlier),
         * rather, we are here working around a restriction in AMOS.
         */
        return 0;
    }

    return std::real(bessel_k0_forward(c10::complex(z)));
}

template <typename T>
inline C10_HOST_DEVICE void bessel_k0_forward_backward(T z, T* cy) {
    if (z < 0) {
        cy[0] = std::numeric_limits<T>::quiet_NaN();
        cy[1] = std::numeric_limits<T>::quiet_NaN();
        return;
    }

    if (z == 0) {
        cy[0] = std::numeric_limits<T>::infinity();
        cy[1] = std::numeric_limits<T>::infinity();
        return;
    }

    if (z > 710) {
        /* Underflow. See uniform expansion https://dlmf.nist.gov/10.41
         * This condition is not a strict bound (it can underflow earlier),
         * rather, we are here working around a restriction in AMOS.
         */
        cy[0] = 0;
        cy[1] = 0;
        return;
    }

    c10::complex<T> cy_[2];
    bessel_k0_forward_backward(c10::complex<T>(z), cy_);
    cy[0] = std::real(cy_[0]);
    cy[1] = std::real(cy_[1]);
    return;
}
