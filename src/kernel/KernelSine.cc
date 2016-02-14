#include "kernel/KernelSine.hh"

KernelSine::KernelSine(double smoothingLength) : Kernel(smoothingLength) {
    norme = PI / (PI/3 - 8/PI +16/(PI*PI));
    factorW = (2 * smoothingLength / PI) * norme / pow(smoothingLength, 4);
    factorGradW =  norme / pow(smoothingLength, 4);
}

double KernelSine::W(double distance) {
    double normalizedDistance = distance / smoothingLength;
    if (normalizedDistance < 1) {
        return factorW * (cos((distance + smoothingLength) / (2 * smoothingLength)) + 1);
    } else {
        console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        return 0.0;
    }
}

Vec3d KernelSine::gradW(double distance, const Vec3d& distanceVector) {
    double normalizedDistance = distance / smoothingLength;
    if (normalizedDistance < 1 && normalizedDistance != 0) {
        return - factorGradW *  distanceVector / distance * sin((distance + smoothingLength) / (2 * smoothingLength)) ;
    }  else {
        console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        return Vec3d(0, 0, 0);
    }
}

double KernelSine::maxDistance() {
    return 1 * smoothingLength;
}