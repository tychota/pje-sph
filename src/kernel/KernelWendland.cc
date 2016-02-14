#include "kernel/KernelWendland.hh"

KernelWendland::KernelWendland(double smoothingLength) : Kernel(smoothingLength) {
    reverseSmoothingLenght = 1 / smoothingLength;
    norme = 21.0 / ( 16 * PI);
    factorW = norme * pow(reverseSmoothingLenght, 3);
    factorGradW = - 6.0 * norme * pow(reverseSmoothingLenght, 4);
}

double KernelWendland::W(double distance) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 2.0) {
        return factorW * pow(1.0 - 0.5 * normalizedDistance, 4) * (2.0 * normalizedDistance + 1.0);
    }  else {
        console->warn("Normalized distance should be less than 2.0 since we already select neighbour");
        return 0.0;
    }
}

Vec3d KernelWendland::gradW(double distance, const Vec3d& distanceVector) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 2.0) {
        return factorGradW * - 5.0 * pow(1.0 - 0.5 * normalizedDistance, 3) * distanceVector;
    } else {
        console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        throw 0;
    }
}

double KernelWendland::laplacian(double distance, const Vec3d &distanceVector) {
    throw NotImplementedException();
}

double KernelWendland::maxDistance() {
    return 2.0 * smoothingLength;
}