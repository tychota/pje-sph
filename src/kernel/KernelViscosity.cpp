#include "kernel/KernelViscosity.hpp"

KernelViscosity::KernelViscosity(double smoothingLength) : Kernel(smoothingLength) {
    norme = 15 / ( 2 * PI);
    factorW = norme / pow(smoothingLength, 3);
    factorGradW =  - norme / pow(smoothingLength, 3);
    factorLapW = 3 * norme / pow(smoothingLength, 6);
}

double KernelViscosity::W(double distance) {
    double normalizedDistance = distance / smoothingLength;
    if (normalizedDistance < 1.0) {
        return factorW * (- pow(distance, 3) / (2 * pow(smoothingLength, 3))
                          + pow(distance, 2) / (pow(smoothingLength, 2))
                          + smoothingLength / (2 * distance)
                          - 1);
    }  else {
        // console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        return 0.0;
    }
}

VEC KernelViscosity::gradW(double distance, const VEC& distanceVector) {
    double normalizedDistance = distance / smoothingLength;
    if (normalizedDistance < 1.0) {
        return distanceVector * factorGradW * (- 3 * distance / (2 * pow(smoothingLength, 3))
                                               + 2 / (pow(smoothingLength, 2))
                                               - smoothingLength / (2 * pow(distance, 3)));
    }  else {
        // console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        return zeros<vec>(3);
    }
}

double KernelViscosity::laplacianW(double distance, const VEC &distanceVector) {
    double normalizedDistance = distance / smoothingLength;
    if (normalizedDistance < 1.0) {
        return factorLapW * (smoothingLength - distance);
    }  else {
        // console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        return 0.;
    }
}

double KernelViscosity::maxDistance() {
    return 1.0 * smoothingLength;
}
