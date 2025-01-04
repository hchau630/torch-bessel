#include <iostream>
#include <c10/util/complex.h>
#include "torch_bessel/csrc/cbesk_hi.h"
#include "torch_bessel/csrc/cbesk/cbesk_blah.h"

int main() {
    // float nu = 0.1631;
    // c10::complex<float> z(-2.2, 0.0);
    float nu = -0.5;
    c10::complex<float> z(1.0, 0.0);
    std::cout << cbesk_hihi(nu, z) << std::endl;
    return 0;
}