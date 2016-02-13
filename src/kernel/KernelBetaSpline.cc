#include "kernel/KernelBetaSpline.hh"

KernelBetaSpline::KernelBetaSpline(double smoothingLength) : Kernel(smoothingLength) {
    rH = 1 / smoothingLength;
    n = 8.0 / PI;
    fW = n * pow(rH, 3);
    fGW = - 6.0 * n * pow(rH, 4);
}

double KernelBetaSpline::W(double distance) {
    double nDist = distance * rH;
    if (nDist< 0.5) {
        return fW * (6.0 * pow(nDist, 3) + 6.0 *pow(nDist,2) + 1);
    } else if (nDist < 1.0) {
        auto a = 1 - nDist;
        return fW * (2.0 * pow(a, 3));
    } else {
        console->alert("Normed distance should be less than 1.0 since we already select neighbour");
    }
}