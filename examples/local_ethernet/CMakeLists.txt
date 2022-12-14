set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

cmake_minimum_required(VERSION 3.20)

project(local_ethernet VERSION 0.1)

include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
  set(CTEST_BUILD_FLAGS -j${N})
  set(ctest_test_args ${ctest_test_args} PARALLEL_LEVEL ${N})
endif()

include_directories(user_config)


include_directories(../../include)
file(GLOB LIB_SOURCES CONFIGURE_DEPENDS ../../src/*.cpp)
file(GLOB LIB_HEADERS CONFIGURE_DEPENDS ../../include/*.h)


add_library(syndesicp_host ${LIB_SOURCES} ${LIB_HEADERS})
add_library(syndesicp_device ${LIB_SOURCES} ${LIB_HEADERS})


add_executable(host)
target_sources(host
  PRIVATE
    host/host.cpp
)
target_include_directories(syndesicp_host PUBLIC host)
set_target_properties(host PROPERTIES RUNTIME_OUTPUT_DIRECTORY host)
target_compile_features(host PRIVATE cxx_std_17)
target_link_libraries(host syndesicp_host)



add_executable(device)
target_sources(device
  PRIVATE
    device/device.cpp
)
target_include_directories(syndesicp_device PUBLIC device)
set_target_properties(device PROPERTIES RUNTIME_OUTPUT_DIRECTORY device)
target_compile_features(device PRIVATE cxx_std_17)
target_link_libraries(device syndesicp_device)