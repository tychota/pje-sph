#include "kernel/KernelSpline3rdO.hh"

KernelSpline3rdO::KernelSpline3rdO(double smoothingLength) : Kernel(smoothingLength) {
    reverseSmoothingLenght = 1 / smoothingLength;
    norme = 1 / PI;
    factorW = norme * pow(reverseSmoothingLenght, 3);
    factorGradW =  norme / pow(reverseSmoothingLenght, 4);
}

double KernelSpline3rdO::W(double distance) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 1) {
        return factorW * (1.0 - 1.5 * pow(normalizedDistance, 2)  + 0.75 * pow(normalizedDistance, 3));
    } else if (normalizedDistance < 2.0) {
        auto diffDistance = 2.0 - normalizedDistance;
        return factorW * 0.25 * pow(diffDistance, 3);
    } else {
        console->warn("Normalized distance should be less than 2.0 since we already select neighbour");
        return 0.0;
    }
}

Vec3d KernelSpline3rdO::gradW(double distance, const Vec3d& distanceVector) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 1 && normalizedDistance != 0) {
        return factorGradW * (1.0 - 3 * normalizedDistance  + 2.25 * pow(normalizedDistance, 2)) * distanceVector;
    } else if (normalizedDistance < 2.0 && normalizedDistance != 0) {
        auto diffDistance = 2.0 - normalizedDistance;
        return factorGradW * -0.25 * pow(diffDistance, 2) * distanceVector;
    } else {
        console->warn("Normalized distance should be less than 2.0 since we already select neighbour");
        return Vec3d(0, 0, 0);
    }
}


double KernelSpline3rdO::laplacian(double distance, const Vec3d &distanceVector) {
    throw NotImplementedException();
}

double KernelSpline3rdO::maxDistance() { return 2 * smoothingLength; }