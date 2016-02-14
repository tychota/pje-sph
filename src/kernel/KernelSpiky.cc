#include "kernel/KernelSpiky.hh"

KernelSpiky::KernelSpiky(double smoothingLength) : Kernel(smoothingLength) {
    reverseSmoothingLenght = 1 / smoothingLength;
    norme = 15 / PI;
    factorW = norme * pow(reverseSmoothingLenght, 6);
    factorGradW =  -3 * norme / pow(reverseSmoothingLenght, 5);
}

double KernelSpiky::W(double distance) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 1) {
        return factorW * pow((smoothingLength  - distance ), 3);
    } else {
        console->warn("Normalized distance should be less than 2.0 since we already select neighbour");
        return 0.0;
    }
}

Vec3d KernelSpiky::gradW(double distance, const Vec3d& distanceVector) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 1 && normalizedDistance != 0) {
        return factorGradW * pow((smoothingLength  - distance ), 2)* distanceVector / distance;
    }  else {
        console->warn("Normalized distance should be less than 2.0 since we already select neighbour");
        return Vec3d(0, 0, 0);
    }
}


double KernelSpiky::laplacian(double distance, const Vec3d &distanceVector) {
    return -2 * (smoothingLength  - distance ) *(smoothingLength  - 2 * distance ) / distance;
}

double KernelSpiky::maxDistance() { return 2 * smoothingLength; }