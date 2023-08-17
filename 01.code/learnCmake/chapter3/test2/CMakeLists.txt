cmake_minimum_required(VERSION 3.0)
project(SORTTEST)
# 搜索当前目录下的所有源文件
aux_source_directory(./ SRC)
# 设置头文件路径
include_directories(${HEAD_PATH})
# 指定可执行要链接的动态库
link_libraries(${CALC_LIB})
# 指定可执行程序的生成路径
set(EXECUTABLE_OUTPUT_PATH ${EXEC_PATH})
# 生成可执行程序
add_executable(${APP_NAME_2} ${SRC})
# 指定可执行程序要连接的动态库
target_link_libraries(${APP_NAME_2} ${SORT_LIB})