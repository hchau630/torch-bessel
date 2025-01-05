#pragma once

#include <iostream>
#include <c10/macros/Macros.h>
#include <c10/util/complex.h>
#include "amos.h"


inline C10_HOST_DEVICE c10::complex<double> bessel_k_forward(double v, c10::complex<double> z) {
    c10::complex<double> cy(NAN, NAN);
    if (std::isnan(v) || std::isnan(std::real(z)) || isnan(std::imag(z))) {
        return cy;
    }

    if (v < 0) {
        /* K_v == K_{-v} even for non-integer v */
        v = -v;
    }

    int n = 1;
    int kode = 1;
    int ierr;
    int nz = amos::besk(z, v, kode, n, &cy, &ierr);
    if (ierr == 2) {
        if (std::real(z) >= 0 && std::imag(z) == 0) {
            /* overflow */
            cy = INFINITY;
        }
    }

    return cy;
}

inline C10_HOST_DEVICE std::tuple<c10::complex<double>, c10::complex<double>> bessel_k_forward_backward(double v, c10::complex<double> z) {
    c10::complex<double> cy[2] = {c10::complex<double>(NAN, NAN), c10::complex<double>(NAN, NAN)};
    if (std::isnan(v) || std::isnan(std::real(z)) || isnan(std::imag(z))) {
        return std::make_tuple(cy[0], cy[1]);
    }

    if (v < 0) {
        /* K_v == K_{-v} even for non-integer v */
        v = -v;
    }

    int n = 2;
    int kode = 1;
    int ierr;
    int nz = amos::besk(z, v, kode, n, cy, &ierr);

    /* dK_v(z)/dz = v/z * K_v(z) - K_{v+1}(z), conjugation
       needed for PyTorch gradient computation */
    cy[1] = std::conj(v / z * cy[0] - cy[1]);

    if (ierr == 2) {
        if (std::real(z) >= 0 && std::imag(z) == 0) {
            /* overflow */
            cy[0] = INFINITY;
            cy[1] = INFINITY;
        }
    }

    return std::make_tuple(cy[0], cy[1]);
}

inline C10_HOST_DEVICE c10::complex<float> bessel_k_forward(float v, c10::complex<float> z) {
    return static_cast<c10::complex<float>>(bessel_k_forward(static_cast<double>(v), static_cast<c10::complex<double>>(z)));
}

inline C10_HOST_DEVICE std::tuple<c10::complex<float>, c10::complex<float>> bessel_k_forward_backward(float v, c10::complex<float> z) {
    auto out = bessel_k_forward(static_cast<double>(v), static_cast<c10::complex<double>>(z));
    return std::make_tuple(static_cast<c10::complex<float>>(std::get<0>(out)), static_cast<c10::complex<float>>(std::get<1>(out)));
}

template <typename T>
inline C10_HOST_DEVICE T bessel_k_forward(T v, T z) {
    if (z < 0) {
        return std::numeric_limits<T>::quiet_NaN();
    }

    if (z == 0) {
        return std::numeric_limits<T>::infinity();
    }

    if (z > 710 * (1 + std::abs(v))) {
        /* Underflow. See uniform expansion https://dlmf.nist.gov/10.41
         * This condition is not a strict bound (it can underflow earlier),
         * rather, we are here working around a restriction in AMOS.
         */
        return 0;
    }

    return std::real(bessel_k_forward(v, c10::complex(z)));
}

template <typename T>
inline C10_HOST_DEVICE std::tuple<T, T> bessel_k_forward_backward(T v, T z) {
    if (z < 0) {
        return std::make_tuple(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN());
    }

    if (z == 0) {
        return std::make_tuple(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());
    }

    if (z > 710 * (1 + std::abs(v))) {
        /* Underflow. See uniform expansion https://dlmf.nist.gov/10.41
         * This condition is not a strict bound (it can underflow earlier),
         * rather, we are here working around a restriction in AMOS.
         */
        return std::make_tuple(0, 0);
    }

    auto out = bessel_k_forward_backward(v, c10::complex(z));
    return std::make_tuple(std::real(std::get<0>(out)), std::real(std::get<1>(out)));
}
