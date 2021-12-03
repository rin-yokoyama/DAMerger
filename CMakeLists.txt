cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(DAMerger)

# ROOT 6 installation
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

# Default installation dir
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install/ CACHE PATH "install dir" FORCE)

# Build options
#option(BUILD_IDAQ2ROOT "Build and install Isobe DAQ data to ROOT converter" ON)

# path definitions
set(DAMERGER_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib/ CACHE STRING "path to install lib")
set(MERGER_WORK_DIR $ENV{HOME}/merger_work/ CACHE STRING "path to working directory")
set(GRETINA_DECODER_DIR $ENV{HOME}/Grape CACHE STRING "path to gretina daq decoder directory")
set(HOME $ENV{HOME} )
set(ANAROOT_DIR_PATH $ENV{TARTSYS} CACHE STRING "path to anaroot directory" )
#configure_file( anamerger/include/LibraryConfig.h.in ${CMAKE_BINARY_DIR}/generated/LibraryConfig.h)

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net Proof )
#find_package(LibXml2 REQUIRED)
find_package(yaml-cpp)
set(YAML_CPP_LIB_DIR ${YAML_CPP_CMAKE_DIR}/../../../lib CACHE PATH "yaml-cpp lib dir")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

# include directories
include_directories(${YAML_CPP_INCLUDE_DIR})
include_directories(${ANAROOT_DIR_PATH}/include)
include_directories(${GRETINA_DECODER_DIR}/cmake/inc)
#include_directories(${CMAKE_BINARY_DIR}/generated)

# link directories
link_directories(${ANAROOT_DIR_PATH}/lib)
link_directories(${YAML_CPP_LIB_DIR})
link_directories(${PWD}/idaq2root)
link_directories(${ROOTSYS}/lib)
link_directories(${GRETINA_DECODER_DIR}/cmake/build)

add_subdirectory(core)
add_subdirectory(idaq2root)
add_subdirectory(grape_dump)
add_subdirectory(tsscan)
add_subdirectory(share)
add_subdirectory(config)