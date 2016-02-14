cmake_minimum_required(VERSION 3.4)
project(PJE)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# INCLUDE ( ${CMAKE_MODULE_PATH}/OpenVdb.cmake )

# FIND_PACKAGE ( Boost ${MINIMUM_BOOST_VERSION} REQUIRED )

# FIND_PACKAGE(VTK)
# INCLUDE(${VTK_USE_FILE})

FIND_PACKAGE(HDF5 REQUIRED)

INCLUDE_DIRECTORIES(
        ${Boost_INCLUDE_DIR}
        headers
        vendors)

ADD_LIBRARY(PJEAcceleration
        src/utils/Prime.cc
        headers/utils/Prime.hh
        src/structure/AccelerationMap.cc
        headers/structure/AccelerationMap.hh)

ADD_LIBRARY(PJECommon
        headers/utils/macros.hh
        headers/utils/Vec3.hh
        src/common/Fluid.cc
        headers/common/Fluid.hh
        src/common/Particle.cc
        headers/common/Particle.hh)

ADD_LIBRARY(PJEForce
        src/force/Force.cc
        headers/force/Force.hh
        src/force/ForceExtern.cc
        headers/force/ForceExtern.hh
        src/force/ForceIntern.cc
        headers/force/ForceIntern.hh
        src/force/ForceInternPressure.cc
        headers/force/ForceInternPressure.hh
        src/force/ForceInternSurfaceTension.cc
        headers/force/ForceInternSurfaceTension.hh
        src/force/ForceInternViscosity.cc
        headers/force/ForceInternViscosity.hh)

ADD_LIBRARY(PJESolid
        src/solid/Solid.cc
        headers/solid/Solid.hh)

ADD_LIBRARY(PJEKernel
        src/kernel/Kernel.cc
        headers/kernel/Kernel.hh
        src/kernel/KernelPoly6.cc
        headers/kernel/KernelPoly6.hh
        src/kernel/KernelSine.cc
        headers/kernel/KernelSine.hh
        src/kernel/KernelSpiky.cc
        headers/kernel/KernelSpiky.hh
        src/kernel/KernelViscosity.cc
        headers/kernel/KernelViscosity.hh)


ADD_LIBRARY(PJEException
        src/exception/NotImplementedException.cc
        headers/exception/NotImplementedException.hh)

ADD_EXECUTABLE(sph main.cpp)
TARGET_LINK_LIBRARIES(sph PJEException PJECommon PJEForce PJEAcceleration PJESolid PJEKernel)

ADD_EXECUTABLE(tests
        test/main.cc
        test/unit/accelerationmapUnitTest.cc
        test/unit/fluidUnitTest.cc
        test/unit/vec3dUnitTest.cc
        test/unit/notimplementedexceptionUnitTest.cc
        test/unit/kernelUnitTest.cc)
TARGET_LINK_LIBRARIES(tests PJEException PJECommon PJEForce PJEAcceleration PJESolid PJEKernel)
