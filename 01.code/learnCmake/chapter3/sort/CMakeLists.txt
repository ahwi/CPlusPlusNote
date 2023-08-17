cmake_minimum_required(VERSION 3.0)
project(SORTLIB)
# 搜索当前目录下的所有源文件
aux_source_directory(./ SRC)
# 设置头文件路径
include_directories(${HEAD_PATH})
# 设置库的生成路径
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})
# 生成动态库
add_library(${SORT_LIB} SHARED ${SRC})