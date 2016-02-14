#include "kernel/KernelSpline5rdO.hh"

KernelSpline5rdO::KernelSpline5rdO(double smoothingLength) : Kernel(smoothingLength) {
    reverseSmoothingLenght = 1 / smoothingLength;
    norme = 1 / (120 * PI);
    factorW = norme * pow(reverseSmoothingLenght, 3);
    factorGradW =  norme / pow(reverseSmoothingLenght, 4);
}

double KernelSpline5rdO::W(double distance) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 1) {
        return factorW * (pow(3.0 - normalizedDistance, 5)  - 6 * pow(2.0 - normalizedDistance, 5) + 15 * pow(1.0 - normalizedDistance, 5));
    } else if (normalizedDistance < 2.0) {
        return factorW * (pow(3.0 - normalizedDistance, 5)  - 6 * pow(2.0 - normalizedDistance, 5));
    } else if (normalizedDistance < 3.0) {
        return factorW * (pow(3.0 - normalizedDistance, 5));
    } else {
        console->warn("Normalized distance should be less than 3.0 since we already select neighbour");
        return 0.0;
    }
}

Vec3d KernelSpline5rdO::gradW(double distance, const Vec3d& distanceVector) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 1 && normalizedDistance != 0) {
        return factorGradW * (1.0 - 3 * normalizedDistance  + 2.25 * pow(normalizedDistance, 2)) * distanceVector;
    } else if (normalizedDistance < 2.0 && normalizedDistance != 0) {
        auto diffDistance = 2.0 - normalizedDistance;
        return factorGradW * -0.25 * pow(diffDistance, 2) * distanceVector;
    } else {
        console->warn("Normalized distance should be less than 3.0 since we already select neighbour");
        return Vec3d(0, 0, 0);
    }
}


double KernelSpline5rdO::laplacian(double distance, const Vec3d &distanceVector) {
    throw NotImplementedException();
}

double KernelSpline5rdO::maxDistance() { return 3 * smoothingLength; }