cmake_minimum_required(VERSION 3.0)
project(CALCTEST)
# 搜索当前目录下的所有源文件
aux_source_directory(./ SRC)
# 设置头文件路径
include_directories(${HEAD_PATH})
# 指定可执行要链接的静态库
link_libraries(${CALC_LIB})
# 指定可执行程序的生成路径
set(EXECUTABLE_OUTPUT_PATH ${EXEC_PATH})
# 生成可执行程序
add_executable(${APP_NAME_1} ${SRC})