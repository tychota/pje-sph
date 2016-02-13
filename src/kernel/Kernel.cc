#include "kernel/Kernel.hh"

Kernel::Kernel(double smoothingLenght) : smoothingLength(smoothingLenght) {
    console->debug("<KERN> Construct a new kernel");
    console->debug("<HASH>   * --> smoothing lenght : {} ", smoothingLenght);
}

double Kernel::W(double distance) {
    throw NotImplementedException();
}

double Kernel::W(double h, double distance) {
    throw NotImplementedException();
}

Vec3d Kernel::gradW(double distance, const Vec3d& distanceVector) {
    throw NotImplementedException();
}

Vec3d Kernel::gradW(double h, double distance, const Vec3d& distanceVector) {
    throw NotImplementedException();
}

double Kernel::laplacian(double distance, const Vec3d& distanceVector) {
    throw NotImplementedException();
}

double Kernel::laplacian(double h, double distance, const Vec3d& distanceVector) {
    throw NotImplementedException();
}

double Kernel::getDilationFactor() {
    return 2.0;
}

double Kernel::maxDistance() {
    return 1.0 * smoothingLength;
}