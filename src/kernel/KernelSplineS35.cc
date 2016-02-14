#include "kernel/KernelSplineS35.hh"

KernelSplineS35::KernelSplineS35(double smoothingLength) : Kernel(smoothingLength) {
    reverseSmoothingLenght = 1 / smoothingLength;
    norme = 2187.0 / (40.0 * PI);
    factorW = norme * pow(reverseSmoothingLenght, 3);
    factorGradW = 5.0 * norme * pow(reverseSmoothingLenght, 4);
}

double KernelSplineS35::W(double distance) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 1.0 / 3.0) {
        return factorW * (pow(1.0 - normalizedDistance, 5) - 6.0 * pow(2.0 / 3.0 - normalizedDistance, 5)
                          + 15.0 * pow(2.0 / 3.0 - normalizedDistance, 5));
    } else if (normalizedDistance < 2.0 / 3.0) {
        return factorW * (pow(1.0 - normalizedDistance, 5) - 6.0 * pow(2.0 / 3.0 - normalizedDistance, 5));
    } else if (normalizedDistance < 1.0) {
        return factorW * (pow(1.0 - normalizedDistance, 5));
    } else {
        console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        return 0.0;
    }
}

Vec3d KernelSplineS35::gradW(double distance, const Vec3d& distanceVector) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance == 0.0) {
        return Vec3d(0, 0, 0);
    } else if (normalizedDistance < 1.0 / 3.0) {
        return factorGradW * (pow(1.0 - normalizedDistance, 4) - 6.0 * pow(2.0 / 3.0 - normalizedDistance, 4)
                          + 15.0 * pow(2.0 / 3.0 - normalizedDistance, 4)) / distance * distanceVector;
    } else if (normalizedDistance < 2.0 / 3.0) {
        return factorGradW * (pow(1.0 - normalizedDistance, 4) - 6.0 * pow(2.0 / 3.0 - normalizedDistance, 4))
               / distance * distanceVector;
    } else if (normalizedDistance < 1.0) {
        return factorGradW * pow(1.0 - normalizedDistance, 5) / distance * distanceVector;
    } else {
        console->warn("Normalized distance should be less than 1.0 since we already select neighbour");
        return Vec3d(0, 0, 0);
    }
}

double KernelSplineS35::laplacian(double distance, const Vec3d &distanceVector) {
    throw NotImplementedException();
}

double KernelSplineS35::maxDistance() {
    return 1.0 * smoothingLength;
}