#include "kernel/KernelCusp.hh"

KernelCusp::KernelCusp(double smoothingLength) : Kernel(smoothingLength) {
    reverseSmoothingLenght = 1 / smoothingLength;
    norme = 7.5 / PI;
    factorW = norme * pow(reverseSmoothingLenght, 3);
    factorGradW = - 2.0 * norme / pow(reverseSmoothingLenght, 4);
}

double KernelCusp::W(double distance) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 1) {
        auto diffDistance = 1.0 - normalizedDistance;
        return factorW * diffDistance * diffDistance;
    } else {
        console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        return 0.0;
    }
}

Vec3d KernelCusp::gradW(double distance, const Vec3d& distanceVector) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 1 && normalizedDistance != 0) {
        auto diffDistance = 1.0 - normalizedDistance;
        return (factorGradW * diffDistance / distance) * distanceVector;
    } else {
        if (normalizedDistance > 1) {
            console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        } else if (normalizedDistance == 0) {
            console->warn("Normalized distance shouldn't be null");
        }
        return Vec3d(0, 0, 0);
    }
}


double KernelCusp::laplacian(double distance, const Vec3d& distanceVector) { throw NotImplementedException();}