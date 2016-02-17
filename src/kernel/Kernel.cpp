#include "kernel/Kernel.hpp"

Kernel::Kernel(double smoothingLenght) : smoothingLength(smoothingLenght) {
    console->debug("<KERN> Construct a new kernel");
    console->debug("<HASH>   * --> smoothing lenght : {} ", smoothingLenght);
}

double Kernel::W(double distance) {
    throw NotImplementedException();
}

VEC Kernel::gradW(double distance, const VEC& distanceVector) {
    throw NotImplementedException();
}

double Kernel::laplacianW(double distance, const VEC &distanceVector) {
    throw NotImplementedException();
}

double Kernel::maxDistance() {
    return 1.0 * smoothingLength;
}
