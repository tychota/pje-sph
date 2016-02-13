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
        vendors
        headers)

SET( SPH_SOURCE_FILES
        main.cpp
        src/utils/prime.cc
        src/structure/proximityHash.cc
        src/common/fluid.cc
        src/common/particle.cc
        src/common/force.cc
        src/kernels/kernel.cc)

SET( SPH_TEST_FILES
        test/unit.cc
        src/utils/prime.cc
        src/structure/proximityHash.cc
        src/common/fluid.cc
        src/common/particle.cc
        src/common/force.cc)

ADD_EXECUTABLE( pje_sph ${SPH_SOURCE_FILES})
ADD_EXECUTABLE( pje_test ${SPH_TEST_FILES})
