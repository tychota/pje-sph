#include "kernel/KernelQuadratic.hh"

KernelQuadratic::KernelQuadratic(double smoothingLength) : Kernel(smoothingLength) {
    reverseSmoothingLenght = 1 / smoothingLength;
    norme = (15.0/16.0) * 1.0 / PI;
    factorW = norme * pow(reverseSmoothingLenght, 3);
    factorGradW = norme / pow(reverseSmoothingLenght, 4);
}

double KernelQuadratic::W(double distance) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 2) {
        return factorW * ((1.0 / 4.0) * normalizedDistance * normalizedDistance - normalizedDistance + 1.0);
    } else {
        console->alert("Normalized distance should be less than 1.0 since we already select neighbour");
        return 0.0;
    }
}

Vec3d KernelQuadratic::gradW(double distance, const Vec3d& distanceVector) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 5 && normalizedDistance != 0) {
        return factorGradW * ((1.0 / 2.0) * normalizedDistance - 1.0) * distanceVector;
    } else {
        if (normalizedDistance > 1) {
            console->alert("Normalized distance should be less than 1.0 since we already select neighbour");
        } else if (normalizedDistance == 0) {
            console->alert("Normalized distance shouldn't be null");
        }
        return Vec3d(0, 0, 0);
    }
}

double KernelQuadratic::maxDistance() {
    return 2 * smoothingLength;
}


