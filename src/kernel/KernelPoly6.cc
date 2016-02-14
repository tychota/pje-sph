#include "kernel/KernelPoly6.hh"

KernelPoly6::KernelPoly6(double smoothingLength) : Kernel(smoothingLength) {
    reverseSmoothingLenght = 1 / smoothingLength;
    norme = 315. / (64 * PI);
    factorW = norme / pow(reverseSmoothingLenght, 9);
    factorGradW = 3 * norme / pow(reverseSmoothingLenght, 9);
}

double KernelPoly6::W(double distance) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 1) {
        return factorW * pow((smoothingLength * smoothingLength - distance * distance), 3);
    } else {
        console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        return 0.0;
    }
}

Vec3d KernelPoly6::gradW(double distance, const Vec3d& distanceVector) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 1 && normalizedDistance != 0) {
        return - factorGradW * pow((smoothingLength * smoothingLength - distance * distance), 2) * distanceVector;
    } else {
        if (normalizedDistance > 1) {
            console->warn("Normalized distance should be less than 2.0 since we already select neighbour");
        } else if (normalizedDistance == 0) {
            console->warn("Normalized distance shouldn't be null");
        }
        return Vec3d(0, 0, 0);
    }
}


double KernelPoly6::laplacian(double distance, const Vec3d& distanceVector) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 1 && normalizedDistance != 0) {
        return 8 * factorGradW * (smoothingLength * smoothingLength - distance * distance)
               * (distance * distance - 0.75 * (smoothingLength * smoothingLength - distance * distance));
    } else {
        return 0.;
    }
}

double KernelPoly6::maxDistance() { return 1.0 * smoothingLength; }