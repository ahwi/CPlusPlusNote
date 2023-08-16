cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# 指定要链接的动态库路径
link_directories(${PROJECT_SOURCE_DIR}/lib)
add_executable(app ${SRC_LIST})
target_link_libraries(app pthread calc)