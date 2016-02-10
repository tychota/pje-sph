
FIND_PACKAGE ( GLFW REQUIRED )
SET ( GLFW_DEPENDENT_LIBRARIES "Xi;Xrandr;Xinerama;Xcursor" )
SET ( GLFW_LINK_LIBRARY ${GLFW_glfw_LIBRARY} )
SET ( GLFW_INCLUDE_DIRECTORY  ${GLFW3_INCLUDE_DIR} )

FIND_PACKAGE ( Boost ${MINIMUM_BOOST_VERSION} REQUIRED COMPONENTS iostreams system thread )
FIND_PACKAGE ( ILMBase REQUIRED )
FIND_PACKAGE ( OpenEXR REQUIRED )
FIND_PACKAGE ( TBB REQUIRED )
FIND_PACKAGE ( ZLIB REQUIRED )
FIND_PACKAGE ( OpenGL REQUIRED )
FIND_PACKAGE ( Blosc REQUIRED )

INCLUDE_DIRECTORIES ( .. ) # So they can simulate referencing installed headers
INCLUDE_DIRECTORIES ( . ) # So they can simulate referencing installed headers
INCLUDE_DIRECTORIES ( ${Boost_INCLUDE_DIR} )
INCLUDE_DIRECTORIES ( ${ILMBASE_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES ( ${TBB_INCLUDE_DIR} )
INCLUDE_DIRECTORIES ( ${OPENGL_INCLUDE_DIR} )
INCLUDE_DIRECTORIES ( ${ZLIB_INCLUDE_DIR} )
INCLUDE_DIRECTORIES ( ${GLFW_INCLUDE_DIRECTORY} )
INCLUDE_DIRECTORIES ( ${BLOSC_INCLUDE_DIR} )

ADD_DEFINITIONS ( -pthread -fPIC )

FILE ( GLOB VIEWER_SOURCE_FILES RELATIVE ${CMAKE_SOURCE_DIR} viewer/* )
FILE ( MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/dwa/openvdb_viewer )
FILE ( COPY ${VIEWER_SOURCE_FILES} DESTINATION ${CMAKE_BINARY_DIR}/dwa/openvdb_viewer )
INCLUDE_DIRECTORIES ( ${CMAKE_BINARY_DIR}/dwa )

SET ( OPENVDB_LIBRARY_SOURCE_FILES
        ./openvdb/Grid.cc
        ./openvdb/Platform.cc
        ./openvdb/io/Archive.cc
        ./openvdb/io/Compression.cc
        ./openvdb/io/File.cc
        ./openvdb/io/GridDescriptor.cc
        ./openvdb/io/Queue.cc
        ./openvdb/io/Stream.cc
        ./openvdb/io/TempFile.cc
        ./openvdb/math/Maps.cc
        ./openvdb/math/Proximity.cc
        ./openvdb/math/QuantizedUnitVec.cc
        ./openvdb/math/Transform.cc
        ./openvdb/metadata/MetaMap.cc
        ./openvdb/metadata/Metadata.cc
        ./openvdb/openvdb.cc
        ./openvdb/util/Formats.cc
        ./openvdb/util/Util.cc
        )

SET_SOURCE_FILES_PROPERTIES ( ${OPENVDB_LIBRARY_SOURCE_FILES}
        PROPERTIES
        COMPILE_FLAGS "-DOPENVDB_PRIVATE -DOPENVDB_USE_BLOSC ${OPENVDB_USE_GLFW_FLAG}"
        )

ADD_LIBRARY ( openvdb_static STATIC
        ${OPENVDB_LIBRARY_SOURCE_FILES}
        )
ADD_LIBRARY ( openvdb_shared SHARED
        ${OPENVDB_LIBRARY_SOURCE_FILES}
        )

TARGET_LINK_LIBRARIES ( openvdb_static
        ${Boost_LIBRARIES}
        ${Tbb_TBB_LIBRARY}
        ${Ilmbase_HALF_LIBRARY}
        ${ZLIB_LIBRARY}
        )
SET_TARGET_PROPERTIES ( openvdb_static openvdb_shared
        PROPERTIES OUTPUT_NAME openvdb
        )

SET ( VDB_PRINT_SOURCE_FILES  openvdb/cmd/openvdb_print/main.cc )
SET_SOURCE_FILES_PROPERTIES ( ${VDB_PRINT_SOURCE_FILES}
        PROPERTIES
        COMPILE_FLAGS "-DOPENVDB_USE_BLOSC ${OPENVDB_USE_GLFW_FLAG}"
        )

ADD_EXECUTABLE ( vdb_print
        ${VDB_PRINT_SOURCE_FILES}
        )

TARGET_LINK_LIBRARIES ( vdb_print
        openvdb_static
        ${BLOSC_blosc_LIBRARY}
        )

SET ( VDB_RENDER_SOURCE_FILES openvdb/cmd/openvdb_render/main.cc )
SET_SOURCE_FILES_PROPERTIES ( ${VDB_RENDER_SOURCE_FILES}
        PROPERTIES
        COMPILE_FLAGS "-DOPENVDB_USE_BLOSC ${OPENVDB_USE_GLFW_FLAG}"
        )
ADD_EXECUTABLE ( vdb_render
        ${VDB_RENDER_SOURCE_FILES}
        )

TARGET_LINK_LIBRARIES ( vdb_render
        openvdb_static
        ${BLOSC_blosc_LIBRARY}
        ${Openexr_ILMIMF_LIBRARY}
        ${Ilmbase_ILMTHREAD_LIBRARY}
        ${Ilmbase_IEX_LIBRARY}
        )

SET ( VDB_VIEW_SOURCE_FILES
        openvdb/cmd/openvdb_view/main.cc
        openvdb/viewer/Camera.cc
        openvdb/viewer/ClipBox.cc
        openvdb/viewer/Font.cc
        openvdb/viewer/RenderModules.cc
        openvdb/viewer/Viewer.cc
        )
SET_SOURCE_FILES_PROPERTIES ( ${VDB_VIEW_SOURCE_FILES}
        PROPERTIES
        COMPILE_FLAGS "-DOPENVDB_USE_BLOSC ${OPENVDB_USE_GLFW_FLAG} -DGL_GLEXT_PROTOTYPES=1"
        )
ADD_EXECUTABLE ( vdb_view
        ${VDB_VIEW_SOURCE_FILES}
        )

TARGET_LINK_LIBRARIES ( vdb_view
        openvdb_static
        ${BLOSC_blosc_LIBRARY}
        ${OPENGL_gl_LIBRARY}
        ${OPENGL_glu_LIBRARY}
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${COREVIDEO_LIBRARY}
        ${GLFW_LINK_LIBRARY}
        ${GLFW_DEPENDENT_LIBRARIES}
        ${GLEW_GLEW_LIBRARY}
        )

INSTALL ( TARGETS
        vdb_view
        vdb_print
        vdb_render
        DESTINATION
        bin
        )

INSTALL ( TARGETS
        openvdb_static
        openvdb_shared
        DESTINATION
        lib
        )

INSTALL ( DIRECTORY ${CMAKE_SOURCE_DIR} DESTINATION include
        FILES_MATCHING PATTERN "*.h")