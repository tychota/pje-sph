#include "kernel/KernelGaussian.hh"

KernelGaussian::KernelGaussian(double smoothingLength) : Kernel(smoothingLength) {
    reverseSmoothingLenght = 1 / smoothingLength;
    norme = 1 / pow(PI, 3.0 / 2.0);
    factorW = norme * pow(reverseSmoothingLenght, 3);
    factorGradW = - 2.0 * norme / pow(reverseSmoothingLenght, 4);
}

double KernelGaussian::W(double distance) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 5) {
        return factorW * exp( - normalizedDistance * normalizedDistance );
    } else {
        console->alert("Normalized distance should be less than 1.0 since we already select neighbour");
        return 0.0;
    }
}

Vec3d KernelGaussian::gradW(double distance, const Vec3d& distanceVector) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 5 && normalizedDistance != 0) {
        return factorGradW * exp( - normalizedDistance * normalizedDistance ) * distanceVector;
    } else {
        if (normalizedDistance > 1) {
            console->alert("Normalized distance should be less than 1.0 since we already select neighbour");
        } else if (normalizedDistance == 0) {
            console->alert("Normalized distance shouldn't be null");
        }
        return Vec3d(0, 0, 0);
    }
}

double KernelGaussian::maxDistance() {
    return 5 * smoothingLength;
}


