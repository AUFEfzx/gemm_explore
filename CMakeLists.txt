cmake_minimum_required(VERSION 3.4)
project(gemm_explore C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_FILES 
    src/gemm.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(gemm_shared SHARED ${SRC_FILES})

set_target_properties(gemm_shared PROPERTIES OUTPUT_NAME "gemm")

add_library(gemm_static STATIC ${SRC_FILES})

set_target_properties(gemm_static PROPERTIES OUTPUT_NAME "gemm_static")

install(TARGETS gemm_shared gemm_static
    DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include
)

#build test
include_directories("${PROJECT_SOURCE_DIR}/test/3rd/OpenBLAS/mac_m1/include")
add_executable(test_unittest "${PROJECT_SOURCE_DIR}/test/gemm_unittest.cpp")

target_link_directories(test_unittest PRIVATE "${PROJECT_SOURCE_DIR}/test/3rd/OpenBLAS/mac_m1/lib_static")
target_link_libraries(test_unittest gemm_static openblas)

