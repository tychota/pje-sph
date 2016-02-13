cmake_minimum_required(VERSION 3.4)
project(pje)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# INCLUDE ( ${CMAKE_MODULE_PATH}/OpenVdb.cmake )

# FIND_PACKAGE ( Boost ${MINIMUM_BOOST_VERSION} REQUIRED )

# FIND_PACKAGE(VTK)
# INCLUDE(${VTK_USE_FILE})

FIND_PACKAGE(HDF5 REQUIRED)

INCLUDE_DIRECTORIES (
        ${Boost_INCLUDE_DIR}
        headers
        vendors
        )

ADD_LIBRARY( pjeAcceleration
        src/utils/Prime.cc
        headers/utils/Prime.hh
        src/structure/AccelerationMap.cc
        headers/structure/AccelerationMap.hh)

ADD_LIBRARY( pjeCommon
        headers/utils/macros.hh
        headers/utils/Vec3.hh
        src/common/Fluid.cc
        headers/common/Fluid.hh
        src/common/Particle.cc
        headers/common/Particle.hh
        src/common/Force.cc
        headers/common/Force.hh)

ADD_LIBRARY( pjeKernel
        src/kernel/Kernel.cc
        headers/kernel/Kernel.hh
        src/kernel/KernelBetaSpline.cc
        headers/kernel/KernelBetaSpline.hh)

ADD_EXECUTABLE( pje_sph main.cpp)
TARGET_LINK_LIBRARIES( pje_sph pjeCommon pjeAcceleration pjeKernel)

ADD_EXECUTABLE( pje_test
        test/main.cc
        test/unit/accelerationmapUnitTest.cc
        test/unit/fluidUnitTest.cc
        test/unit/vec3dUnitTest.cc)
TARGET_LINK_LIBRARIES( pje_test pjeCommon pjeAcceleration pjeKernel)
