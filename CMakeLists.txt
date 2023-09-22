cmake_minimum_required(VERSION 2.8)
project(cuda_example LANGUAGES C CXX CUDA)

find_package(OpenCV REQUIRED)


add_library(saxpy_culib cuda/saxpy/saxpy.cu)
target_compile_options(saxpy_culib PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:
                       -arch=sm_50
                       -Wno-deprecated-gpu-targets
                       >)

add_library(add_vector_culib cuda/add_vector/add_vector.cu)
target_compile_options(add_vector_culib PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:
                       -arch=sm_50
                       -Wno-deprecated-gpu-targets
                       >)

# add_executable(cuda_main func.cu)

add_executable(cuda_test main.cpp)
target_link_libraries(cuda_test saxpy_culib add_vector_culib ${OpenCV_LIBRARIES})

# add_executable(stereo_gpu stereo_gpu.cpp)
# target_link_libraries(stereo_gpu ${OpenCV_LIBRARIES} pthread)
