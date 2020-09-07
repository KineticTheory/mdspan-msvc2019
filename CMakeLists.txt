#-----------------------------*-cmake-*----------------------------------------#
# file   experimental/CMakeLists.txt
# author Kelly Thompson <kgt@lanl.gov>
# date   Saturday, Dec 28, 2019, 15:35 pm
# brief  Provide future C++ features that can be made to work when limiting C++
#        standard to 14.
# note   Copyright (C) 2019, Triad National Security, LLC.
#        All rights reserved.
#------------------------------------------------------------------------------#
cmake_minimum_required(VERSION 3.9.0)
project( experimental CXX )

set( experimental_headers ${PROJECT_SOURCE_DIR}/mdspan )
file( GLOB supporting_headers_p0009_bits ${PROJECT_SOURCE_DIR}/__p0009_bits/*.hpp)

add_executable( mdspan_test_exe WIN32 tst_mdspan.cc )
set_target_properties( mdspan_test_exe PROPERTIES
  CXX_STANDARD 14              # Force strict C++ 14 standard
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED ON
  POSITION_INDEPENDENT_CODE ON )
target_include_directories( mdspan_test_exe
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}> )    
  
include(CTest)
enable_testing()
add_test( NAME mdspan_test COMMAND  $<TARGET_FILE:mdspan_test_exe>)

# ---------------------------------------------------------------------------- #
# End experimental/CMakeLists.txt
# ---------------------------------------------------------------------------- #
