#include "kernel/Kernel.hpp"

Kernel::Kernel(double smoothingLenght) : smoothingLength(smoothingLenght) {
    console->debug("<KERN> Construct a new kernel");
    console->debug("<HASH>   * --> smoothing lenght : {} ", smoothingLenght);
}

double Kernel::W(double distance) {
    throw NotImplementedException();
}

vec3 Kernel::gradW(double distance, const vec3& distanceVector) {
    throw NotImplementedException();
}

double Kernel::laplacianW(double distance, const vec3 &distanceVector) {
    throw NotImplementedException();
}

double Kernel::getDilationFactor() {
    return 2.0;
}

double Kernel::maxDistance() {
    return 1.0 * smoothingLength;
}
