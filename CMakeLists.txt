cmake_minimum_required(VERSION 3.4)
project(PJE)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
FIND_PACKAGE(Armadillo REQUIRED)
FIND_PACKAGE(VTK REQUIRED)
FIND_PACKAGE(HDF5 REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall -DNDEBUG")

INCLUDE_DIRECTORIES(
        ${ARMADILLO_INCLUDE_DIRS}
        headers
        vendors)

ADD_LIBRARY(PJEIo
        src/io/Writer.cpp
        headers/io/Writer.hpp
        #src/io/VtkWriter.cpp
        #headers/io/VtkWriter.hpp
        src/io/TextWriter.cpp
        headers/io/TextWriter.hpp)

ADD_LIBRARY(PJESph
        src/sph/Particle.cpp
        headers/sph/Particle.hpp
        src/sph/Solver.cpp
        headers/sph/Solver.hpp)

ADD_LIBRARY(PJECommon
        src/common/Fluid.cpp
        headers/common/Fluid.hpp
        src/common/Force.cpp
        headers/common/Force.hpp)

ADD_LIBRARY(PJESolid
        src/solid/Solid.cpp
        headers/solid/Solid.hpp
        src/solid/Box.cpp
        headers/solid/Box.hpp)

ADD_LIBRARY(PJEKernel
        src/kernel/Kernel.cpp
        headers/kernel/Kernel.hpp
        src/kernel/KernelPoly6.cpp
        headers/kernel/KernelPoly6.hpp
        src/kernel/KernelSine.cpp
        headers/kernel/KernelSine.hpp
        src/kernel/KernelSpiky.cpp
        headers/kernel/KernelSpiky.hpp
        src/kernel/KernelViscosity.cpp
        headers/kernel/KernelViscosity.hpp)

ADD_LIBRARY(PJEException
        src/exception/NotImplementedException.cpp
        headers/exception/NotImplementedException.hpp)

ADD_EXECUTABLE(sph main.cpp)
TARGET_LINK_LIBRARIES(sph ${ARMADILLO_LIBRARIES} PJESolid PJESph PJECommon PJEKernel PJEException PJEIo )

ADD_EXECUTABLE(tests
        test/main.cpp
        test/unit/exceptionTest.cpp
        test/unit/forceTest.cpp
        test/unit/fluidTest.cpp
        test/unit/kernelTest.cpp
        test/unit/particleTest.cpp
        test/unit/solidTest.cpp)
TARGET_LINK_LIBRARIES(tests ${ARMADILLO_LIBRARIES} PJESolid PJESph PJECommon PJEKernel PJEException PJEIo )
