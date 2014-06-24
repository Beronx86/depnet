project (depnet)
set(CMAKE_RELEASE_POSTFIX, "so")
set(CMAKE_DEBUG_POSTFIX, "so")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
cmake_minimum_required(VERSION 2.8)

find_package(PythonLibs REQUIRED)
include_directories (${PYTHON_INCLUDE_DIRS})

find_package(Boost 1.55.0 COMPONENTS python)
include_directories (${Boost_INCLUDE_DIRS} src)
message("Python include dirs: " ${PYTHON_INCLUDE_DIRS} )
message("Python libraries: " ${PYTHON_LIBRARIES} )
message("Boost include dirs: " ${Boost_INCLUDE_DIRS} )
message("Boost libraries: " ${Boost_LIBRARIES} )


file(GLOB DEPNET_SOURCES src/*.cpp)
file(GLOB DEPNET_HEADERS src/*.h)

file(GLOB ALGLIB_SOURCES src/alglib/*.cpp)
file(GLOB ALGLIB_HEADERS src/alglib/*.h)

file(GLOB PYDEPNET_SOURCES src/python/*.cpp)
file(GLOB PYDEPNET_HEADERS src/python/*.h)

add_library (
    depnet SHARED 
    ${DEPNET_SOURCES}
    ${DEPNET_HEADERS}
    ${ALGLIB_SOURCES}
    ${ALGLIB_HEADERS}
)

add_library(
    pydepnet SHARED
    ${DEPNET_SOURCES}
    ${DEPNET_HEADERS}
    ${PYDEPNET_SOURCES}
    ${PYDEPNET_HEADERS}
    ${ALGLIB_SOURCES}
    ${ALGLIB_HEADERS}
)

add_executable(deptool 
    ${DEPNET_SOURCES} ${DEPNET_HEADERS} 
    ${ALGLIB_SOURCES} ${ALGLIB_HEADERS}
)

set(CMAKE_SHARED_LIBRARY_SUFFIX .so)
set(CMAKE_SHARED_LIBRARY_PREFIX )

target_link_libraries(deptool
    ${Boost_LIBRARIES}
)

target_link_libraries (depnet
    ${Boost_LIBRARIES}
)

target_link_libraries(pydepnet
    ${PYTHON_LIBRARIES}
    ${Boost_LIBRARIES}
)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(docs
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)
