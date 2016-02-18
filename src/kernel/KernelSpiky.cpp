#include "kernel/KernelSpiky.hpp"

KernelSpiky::KernelSpiky(double smoothingLength) : Kernel(smoothingLength) {
    norme = 15 / PI;
    factorW = norme / pow(smoothingLength, 6);
    factorGradW =  -3 * norme / pow(smoothingLength, 6);
    factorLapW =  6 * norme / pow(smoothingLength, 6);
}

double KernelSpiky::W(double distance) {
    double normalizedDistance = distance / smoothingLength;
    if (normalizedDistance < 1) {
        return factorW * pow((smoothingLength  - distance ), 3);
    } else {
        // console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        return 0.0;
    }
}

VEC KernelSpiky::gradW(double distance, const VEC& distanceVector) {
    double normalizedDistance = distance / smoothingLength;
    if (normalizedDistance < 1 && normalizedDistance != 0) {
        return factorGradW * pow((smoothingLength  - distance ), 2) * distanceVector / distance;
    } else {
        // console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        return zeros<vec>(3);
    }
}


double KernelSpiky::laplacianW(double distance, const VEC &distanceVector) {
    double normalizedDistance = distance / smoothingLength;
    if (normalizedDistance < 1 && normalizedDistance != 0) {
        return -2 * factorLapW * (smoothingLength - distance) * (smoothingLength - 2 * distance) / distance;
    } else {
        // console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        return 0.0;
    }
}

double KernelSpiky::maxDistance() {
    return 1.0 * smoothingLength;
}
