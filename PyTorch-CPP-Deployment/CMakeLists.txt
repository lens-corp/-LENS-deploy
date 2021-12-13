cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(infer-app)

find_package(OpenCV REQUIRED)

find_package(Torch REQUIRED)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS})

add_executable(infer-app main.cpp)
target_link_libraries(infer-app ${TORCH_LIBRARIES} ${OpenCV_LIBS})

set_property(TARGET infer-app PROPERTY CXX_STANDARD 17)