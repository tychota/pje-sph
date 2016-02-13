#include "kernel/KernelBox.hh"

KernelBox::KernelBox(double smoothingLength) : Kernel(smoothingLength) {
    reverseSmoothingLenght = 1 / smoothingLength;
    scaleFactorW = (3.0 / 4.0) / PI;
    scaleFactorGradW = - 3.0 / PI;
    factorW = scaleFactorGradW * pow(reverseSmoothingLenght, 3);
    factorGradW = scaleFactorGradW * pow(reverseSmoothingLenght, 4);
}

double KernelBox::W(double distance) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 1) {
        return factorW;
    } else {
        console->alert("Normalized distance should be less than 1.0 since we already select neighbour");
        return 0.0;
    }
}

Vec3d KernelBox::gradW(double distance, const Vec3d& distanceVector) {
    double normalizedDistance = distance * reverseSmoothingLenght;
    if (normalizedDistance < 1 && normalizedDistance != 0) {
        return (factorGradW / distance) * distanceVector;
    } else {
        if (normalizedDistance > 1) {
            console->alert("Normalized distance should be less than 1.0 since we already select neighbour");
        } else if (normalizedDistance == 0) {
            console->alert("Normalized distance shouldn't be null");
        }
        return Vec3d(0, 0, 0);
    }
}


