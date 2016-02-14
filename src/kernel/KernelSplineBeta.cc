#include "kernel/KernelSplineBeta.hh"

KernelSplineBeta::KernelSplineBeta(double smoothingLength) : Kernel(smoothingLength) {
    reverseSmoothingLenght = 1 / smoothingLength;
    norme = 8.0 / PI;
    factorW = norme * pow(reverseSmoothingLenght, 3);
    factorGradW = - 6.0 * norme * pow(reverseSmoothingLenght, 4);
}

double KernelSplineBeta::W(double distance) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 0.5) {
        return factorW * (6.0 * pow(normalizedDistance, 3) - 6.0 * pow(normalizedDistance, 2) + 1);
    } else if (normalizedDistance < 1.0) {
        auto a = 1 - normalizedDistance;
        return factorW * (2.0 * pow(a, 3));
    } else {
        console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        return 0.0;
    }
}

Vec3d KernelSplineBeta::gradW(double distance, const Vec3d& distanceVector) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 0.5) {
        return (factorGradW * (3.0 * pow(normalizedDistance, 3) - 2.0 * pow(normalizedDistance, 2) + 1)) * distanceVector;
    } else if (normalizedDistance < 1.0) {
        return (-factorGradW * (1.0 / distance - 2.0 * reverseSmoothingLenght + norme * reverseSmoothingLenght))
               * distanceVector;
    } else {
        console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        throw 0;
    }
}

double KernelSplineBeta::laplacian(double distance, const Vec3d &distanceVector) {
    return Kernel::laplacian(distance, distanceVector);
}

double KernelSplineBeta::maxDistance() {
    return 1.0 * smoothingLength;
}


