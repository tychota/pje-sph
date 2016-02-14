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
        vendors
)

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
        headers/force/Force.hh)

ADD_LIBRARY(PJEState
        src/state/State.cc
        headers/state/State.hh)

ADD_LIBRARY(PJESolid
        src/solid/Solid.cc
        headers/solid/Solid.hh)

ADD_LIBRARY(PJEKernel
        src/kernel/Kernel.cc
        headers/kernel/Kernel.hh
        src/kernel/KernelBox.cc
        headers/kernel/KernelBox.hh
        src/kernel/KernelCusp.cc
        headers/kernel/KernelCusp.hh
        src/kernel/KernelGaussian.cc
        headers/kernel/KernelGaussian.hh
        src/kernel/KernelPoly6.cc
        headers/kernel/KernelPoly6.hh
        src/kernel/KernelQuadratic.cc
        headers/kernel/KernelQuadratic.hh
        src/kernel/KernelSpiky.cc
        headers/kernel/KernelSpiky.hh
        src/kernel/KernelSpline3rdO.cc
        headers/kernel/KernelSpline3rdO.hh
        src/kernel/KernelSpline5rdO.cc
        headers/kernel/KernelSpline5rdO.hh
        src/kernel/KernelSplineBeta.cc
        headers/kernel/KernelSplineBeta.hh
        src/kernel/KernelSplineS35.cc
        headers/kernel/KernelSplineS35.hh
        src/kernel/KernelWendland.cc
        headers/kernel/KernelWendland.hh)


ADD_LIBRARY(PJEException
        src/exception/NotImplementedException.cc
        headers/exception/NotImplementedException.hh
        )

ADD_EXECUTABLE(sph main.cpp)
TARGET_LINK_LIBRARIES(sph PJEException PJECommon PJEForce PJEState PJEAcceleration PJESolid PJEKernel)

ADD_EXECUTABLE(tests
        test/main.cc
        test/unit/accelerationmapUnitTest.cc
        test/unit/fluidUnitTest.cc
        test/unit/vec3dUnitTest.cc
        test/unit/notimplementedexceptionUnitTest.cc
        test/unit/kernelUnitTest.cc)
TARGET_LINK_LIBRARIES(tests PJEException PJECommon PJEForce PJEState PJEAcceleration PJESolid PJEKernel)
