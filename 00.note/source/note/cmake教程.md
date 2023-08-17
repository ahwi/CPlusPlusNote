# CMake 保姆级教程

学习资料：

* 视频：`CMake 保姆级教程【c/c++】` 爱编程的大丙  `https://www.bilibili.com/video/BV14s4y1g7Zj`
* 文章：`https://subingwen.cn/cmake/CMake-primer/`

## 1. CMake 概述

## 2. CMake 的使用

### 2.1 注释

注释的两种方式：

* `#` 注释

* `#[[]]` 块注释，如：

  ```cmake
  #[[ 这是一个 CMakeLists.txt 文件。
  这是一个 CMakeLists.txt 文件
  这是一个 CMakeLists.txt 文件]]
  cmake_minimum_required(VERSION 3.0.0)
  ```

### 2.2 第一个示例

添加文件 (详细查看`chapter1`的代码)：

```txt
$ tree
.
├── add.c
├── div.c
├── head.h
├── main.c
├── mult.c
└── sub.c
```

添加`CMakeLists.txt`文件

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
add_executable(app add.c div.c main.c mult.c sub.c)
```

* `cmake_minimum_required` 指定使用的cmake的最低版本

* `project`: 定义工程名称，并可指定工程的版本、工程描述、web主页地址、支持的语言（默认情况支持所有语言），如果不需要这些都是可以忽略的，只需要指定出工程名字即可。

  ```cmake
  # PROJECT 指令的语法是：
  project(<PROJECT-NAME> [<language-name>...])
  project(<PROJECT-NAME>
         [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
         [DESCRIPTION <project-description-string>]
         [HOMEPAGE_URL <url-string>]
         [LANGUAGES <language-name>...])
  ```

* `add_executable`：定义工程会生成一个可执行程序

  ```cmake
  add_executable(可执行程序名 源文件名称)
  ```

  * 这里的可执行程序名和project中的项目名没有任何关系
  * 源文件名可以是一个也可以是多个，如有多个可用`空格`或`;`间隔

**执行cmake指令**

* 指令格式：

  ```cmd
  cmake CMakeLists.txt文件所在路径
  ```

* 创建一个build(用来存放编译生成的相关文件)：

  ```cmd
  mkdir build
  cd build;cmake ..
  ```

* 生成的文件大概如下：

  ```txt
  $ tree build -L 1
  build
  ├── CMakeCache.txt
  ├── CMakeFiles
  ├── cmake_install.cmake
  └── Makefile
  
  1 directory, 3 files
  ```

### 2.3 定义变量

`set` 可以用来定义变量。

语法：

```cmake
# SET 指令的语法是：
# [] 中的参数为可选项, 如不需要可以不写
SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])

# VAR 变量名
# VALUE 变量值
```

**例子：定义变量用来存储文件名列表**

```cmake
set(SRC_LIST add.c div.c ain.c mult.c sub.c)
```

### 2.4 指定使用的C++标准

在编写C++程序的时候，可能会用到C++11、C++14、C++17、C++20等新特性，那么就需要在编译的时候在编译命令中指定使用哪个标准：

```cmd
$ g++ *.cpp -std=c++11 -o app
```

上面的例子中通过参数`-std=c++11`指定出要使用c++11标准编译程序，C++标准对应有一宏叫做`DCMAKE_CXX_STANDARD`。

在CMake中指定C++标准的两种方式：

* 在 CMakeLists.txt 中通过 set 命令指定

    ```cmake
    #增加-std=c++11
    set(CMAKE_CXX_STANDARD 11)
    #增加-std=c++14
    set(CMAKE_CXX_STANDARD 14)
    #增加-std=c++17
    set(CMAKE_CXX_STANDARD 17)
    ```
	
* 在执行 cmake 命令的时候指定出这个宏的值

    ```cmake
    #增加-std=c++11
    cmake CMakeLists.txt文件路径 -DCMAKE_CXX_STANDARD=11
    #增加-std=c++14
    cmake CMakeLists.txt文件路径 -DCMAKE_CXX_STANDARD=14
    #增加-std=c++17
    cmake CMakeLists.txt文件路径 -DCMAKE_CXX_STANDARD=17
    ```
    

### 2.5 指定输出的路径

在CMake中指定可执行程序输出的路径，对应的宏是`EXECUTABLE_OUTPUT_PATH`：

```cmake
set(HOME /home/robin/sort)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)
```

* 第一行：定义一个变量用于存储一个绝对路径
* 第二行：将拼接好的路径值设置给`EXECUTABLE_OUTPUT_PATH`宏

> 如果此处指定可执行程序生成路径的时候使用的是相对路径 ./xxx/xxx，那么这个路径中的 ./ 对应的就是 makefile 文件所在的那个目录

### 2.6 搜索文件

搜索文件的命令：
* `aux_source_directory`
* `file`

**`aux_source_directory`命令**
该命令可以查找某个路径下的所有源文件（*.c和*.cpp）
命令格式：

```cmake
aux_source_directory(< dir > < variable >)

# dir: 要搜索的目录
# variable: 将从dir目录下搜索到的源文件列表存储到该变量中
```

示例：

```cmake
# 搜索 src 目录下的源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
```

> `CMAKE_CURRENT_SOURCE_DIR` 宏表示当前访问的 `CMakeLists.txt` 文件所在的路径。

**`file`命令**
格式：

```cmake
file(GLOB/GLOB_RECURSE 变量名 要搜索的文件路径和文件类型)

# GLOB: 将指定目录下搜索到的满足条件的所有文件名生成一个列表，并将其存储到变量中
# GLOB_RECURSE：递归搜索指定目录，将搜索到的满足条件的文件名生成一个列表，并将其存储到变量中
```

示例：

```cmake
file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB MAIN_HEAD ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
```

> 要搜索的文件路径和类型可加双引号 :
>
> `file(GLOB MAIN_HEAD "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")`

### 2.7 包含头文件
`include_directories` 设置要包含头文件
格式：

```cmake
include_directories(headpath)
```

示例：有如下目录结构

```txt
$ tree
.
├── build
├── CMakeLists.txt
├── include
│   └── head.h
└── src
    ├── add.cpp
    ├── div.cpp
    ├── main.cpp
    ├── mult.cpp
    └── sub.cpp

3 directories, 7 files
```

CMakeLists.txt的内容如下：

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
set(CMAKE_CXX_STANDARD 11)
set(HOME /home/robin/Linux/calc)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin/)
# 指定头文件的路径
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(app  ${SRC_LIST})
```

> `PROJECT_SOURCE_DIR` 宏对应的值就是我们在使用cmake命令时，后面紧跟的目录，一般是工程的根目录。

代码参考：`chapter2.7`

### 2.8 制作动态库或静态库

#### 2.8.1 制作静态库

制作静态库的命令：

```cmake
add_library(库名称 STATIC 源文件1 [源文件2])
```

在Linux中，静态库名称分为三部分：`lib` + `库名字` + `.a`，此处只需要指定出库的名字就可以了，另外两部分在生成该文件的时候会自动填充。

windows中虽然库名和linux格式不同，但也只需指定出名字即可。

示例：

将`src`目录中的源文件编译成静态库：

```txt
.
├── build
├── CMakeLists.txt
├── include           # 头文件目录
│   └── head.h
├── main.cpp          # 用于测试的源文件
└── src               # 源文件目录
    ├── add.cpp
    ├── div.cpp
    ├── mult.cpp
    └── sub.cpp
```

 `CMakeLists.txt`文件：

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_library(app STATIC ${SRC_LIST})
```

示例：参考`chapter2.8.1`

#### 2.8.2 制作动态库

制作动态库的命令：

```cmake
add_library(库名称 SHARED 源文件1 [源文件2] ...)
```

动态库的规则类静态库类似，在linux中为：`lib` + `库名字` + `.so`

`CMakeLists.txt`文件：

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_library(app SHARED ${SRC_LIST})
```

示例：参考`chapter2.8.2`

#### 2.8.3 指定输出路径

##### 1. 适用于动态库

在linux下生成的动态库默认是有执行权限的，所以可以按照生成可执行程序的方式去指定它生成的目录：

```cmake
# 设置动态库生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
```

> <font color=red>注：经过测试，通过`EXECUTABLE_OUTPUT_PATH`宏并不能指定动态库的路径，建议使用`LIBRARY_OUTPUT_PATH`来指定库路径</font>

##### 2. 适用于动态库和静态库

在linux下生成的静态库默认不具有可执行权限，所以不能用`EXECUTABLE_OUTPUT_PATH`宏来指定输出路径。

可以使用`LIBRARY_OUTPUT_PATH`来指定库输出路径，这个宏对静态库和动态库都适用。

```cmake
# 设置动态库/静态库生成路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
```

完整的`CMakeLists.txt`：

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# 设置动态库/静态库生成路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 生成动态库
add_library(calc SHARED ${SRC_LIST})
# 生成静态库
# add_library(calc STATIC ${SRC_LIST})
```

完整代码 `chapter2.8.3`

### 2.9 包含库文件

通过调用上一节生成的动态库或静态库的函数来编写代码，此时需要进行链接处理。

#### 2.9.1 链接静态库

测试目录结构如下：

```txt
$ tree 
.
├── build
├── CMakeLists.txt
├── include
│   └── head.h
├── lib
│   └── libcalc.a     # 制作出的静态库的名字
└── src
    └── main.cpp

4 directories, 4 files
```

链接静态库的命令：

```cmake
link_libraries(<static lib> [<static lib>...])

# 参数1：指出要链接的静态库的名字
	* 可以是全名 `libxxx.a`
	* 也可以是 去掉lib .a的名字 xxx
# 参数2-N：要链接的其它静态库的名字
```

指定静态库的路径：

```cmake
link_directories(<lib path>)
```

> 如果该静态库不是系统提供的（自己制作或者使用第三方提供的静态库）可能出现静态库找不到的情况，此时可以将静态库的路径也指定出来。

完整的`CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# 包含静态库路径
link_directories(${PROJECT_SOURCE_DIR}/lib)
# 链接静态库
link_libraries(calc)
add_executable(app ${SRC_LIST})
```

完整代码：`chapter2.9.1`

#### 2.9.2 链接动态库

**1. 动态库的链接和静态库的链接的不同**

动态库的链接和静态库是完全不同的：

* 静态库会在生成可执行程序的链接阶段被打包到可执行程序中，所以可执行程序启动，静态库就被加载到内存中了。
* 动态库在生成可执行程序的链接阶段不会被打包到可执行程序中，当可执行程序被启动并且调用了动态库中的函数的时候，动态库才会被加载到内存。

**2. 命令格式**

链接动态库的命令如下：

```cmake
target_link_libraries(
    <target> 
    <PRIVATE|PUBLIC|INTERFACE> <item>... 
    [<PRIVATE|PUBLIC|INTERFACE> <item>...]...)
    
# target：指定要加载动态库的文件的名字
	* 该文件可能是一个源文件
	* 该文件可能是一个动态库文件
	* 该文件可能是一个可执行文件
# PRIVATE|PUBLIC|INTERFACE: 动态库的访问权限，默认为 PUBLIC
	* 如果各个动态库之间没有依赖关系，无需做任何设置，三者没有没有区别，一般无需指定，使用默认的 PUBLIC 即可。
	* PUBLIC：在public后面的库会被Link到前面的target中，并且里面的符号也会被导出，提供给第三方使用。
	* PRIVATE：在private后面的库仅被link到前面的target中，并且终结掉，第三方不能感知你调了啥库
	* INTERFACE：在interface后面引入的库不会被链接到前面的target中，只会导出符号。
```

> 动态库的链接具有传递性：如果动态库 A 链接了动态库B、C，动态库D链接了动态库A，此时动态库D相当于也链接了动态库B、C，并可以使用动态库B、C中定义的方法。
>
> ```cmake
> target_link_libraries(A B C)
> target_link_libraries(D A)
> ```



**示例：链接动态库**

在cmake中指定要链接的动态库的时候，应该将命令写到生成了可执行文件之后。

示例：链接系统动态库`libpthread.so`和第三方动态库`libcalc.so`

> 通过 `link_directories(path)`指定要链接的第三方动态库路径。

目录结构：

```txt
$ tree 
.
├── build
├── CMakeLists.txt
├── include
│   └── head.h            # 动态库对应的头文件
├── lib
│   └── libcalc.so        # 自己制作的动态库文件
└── main.cpp              # 测试用的源文件

3 directories, 4 files
```

完整的`CMakeLists.txt`：

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# 指定要链接的动态库路径
link_directories(${PROJECT_SOURCE_DIR}/lib)
add_executable(app ${SRC_LIST})
target_link_libraries(app pthread calc)
```

示例代码：`chapter2.9.2`

### 2.10 日志

使用`message`显示消息：

```cmake
message([STATUS|WARNING|AUTHOR_WARNING|FATAL_ERROR|SEND_ERROR] "message to display" ...)

* (无) ：重要消息
* STATUS ：非重要消息
* WARNING：CMake 警告, 会继续执行
* AUTHOR_WARNING：CMake 警告 (dev), 会继续执行
* SEND_ERROR：CMake 错误, 继续执行，但是会跳过生成的步骤
* FATAL_ERROR：CMake 错误, 终止所有处理过程
```

 CMake的命令行工具会在stdout上显示STATUS消息，在stderr上显示其他所有消息。CMake的GUI会在它的log区域显示所有消息。

示例：

```cmake
# 输出一般日志信息
message(STATUS "source path: ${PROJECT_SOURCE_DIR}")
# 输出警告信息
message(WARNING "source path: ${PROJECT_SOURCE_DIR}")
# 输出错误信息
message(FATAL_ERROR "source path: ${PROJECT_SOURCE_DIR}")
```

### 2.11 变量操作

`set` `list`命令的操作，略

### 2.12 宏定义

通过宏来控制代码是否生效：

```cmake
#include <stdio.h>
#define NUMBER  3

int main()
{
    int a = 10;
#ifdef DEBUG
    printf("我是一个程序猿, 我不会爬树...\n");
#endif
    for(int i=0; i<NUMBER; ++i)
    {
        printf("hello, GCC!!!\n");
    }
    return 0;
}
```

第七行对DEBUG宏进行了判断，如果该宏被定义了，那么第八行就会进行日志输出，如果没有定义这个宏，第八行就相当于被注释掉了。

`gcc/g++`编译时指定宏定义：

```cmd
$ gcc test.c -DDEBUG -o app 
```

在cmake中可以使用`add_definitions`命令

```cmake
add_definitions(-D宏名称)
```

针对上面的源文件编写的`CMakeLists.txt`：

```cmake
cmake_minimum_required(VERSION 3.0)
project(TEST)
# 自定义 DEBUG 宏
add_definitions(-DDEBUG)
add_executable(app ./test.c)
```

#### 预定义宏

cmake中常用的宏：

| 宏                       | 功能                                                         |
| ------------------------ | ------------------------------------------------------------ |
| PROJECT_SOURCE_DIR       | 使用cmake命令后紧跟的目录，一般是工程的根目录                |
| PROJECT_BINARY_DIR       | 执行cmake命令的目录                                          |
| CMAKE_CURRENT_SOURCE_DIR | 当前处理的CMakeLists.txt所在的路径                           |
| CMAKE_CURRENT_BINARY_DIR | target 编译目录                                              |
| EXECUTABLE_OUTPUT_PATH   | 重新定义目标二进制可执行文件的存放位置                       |
| LIBRARY_OUTPUT_PATH      | 重新定义目标链接库文件的存放位置                             |
| PROJECT_NAME             | 返回通过PROJECT指令定义的项目名称                            |
| CMAKE_BINARY_DIR         | 项目实际构建路径，假设在build目录进行的构建，那么得到的就是这个目录的路径 |



## 3. 嵌套的CMake

对于多目录结构的项目，为了方便管理和维护，需要给每个目录都添加一个`CMakeLists.txt`文件。

目录结构：

```txt
tree
.
├── CMakeLists.txt
├── calc
│   ├── CMakeLists.txt
│   ├── add.cpp
│   ├── div.cpp
│   ├── mult.cpp
│   └── sub.cpp
├── include
│   ├── calc.h
│   └── sort.h
├── sort
│   ├── CMakeLists.txt
│   └── sort.cpp
├── test1
│   ├── CMakeLists.txt
│   └── testCalc.cpp
└── test2
    ├── CMakeLists.txt
    └── testSort.cpp

5 directories, 14 files
```

* `include 目录`：头文件目录
* `calc 目录`：加减乘除的源码
* `sort 目录`：排序的源码
* `test1 目录`：测试目录，对加减乘除进行测试
* `test2 目录`：测试目录，对排序算法进行测试

可以看到各个目录底下都需要一个`CMakeLists.txt`文件

**节点关系：**

嵌套的 CMake 也是一个树状结构，最顶层的 `CMakeLists.txt` 是根节点，其次都是子节点。

`CMakeLists.txt` 文件变量作用域的一些信息：

* 根节点`CMakeLists.txt`中的变量全局有效
* 父节点`CMakeLists.txt`中的变量可以在子节点中使用
* 子节点`CMakeLists.txt`中的变量只能在当前节点中使用

**添加子目录**

把子目录添加到构建系统中：

```cmake
add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])

* source_dir：指定了CMakeLists.txt源文件和代码文件的位置，其实就是指定子目录
* binary_dir：指定了输出文件的路径，一般不需要指定，忽略即可。
* EXCLUDE_FROM_ALL：在子路径下的目标默认不会被包含到父路径的ALL目标里，并且也会被排除在IDE工程文件之外。用户必须显式构建在子路径下的目标。
```

通过这种方式`CMakeLists.txt`文件之间的父子关系就被构建出来了。

**解决问题：**

最终的目标：

* 把`calc`编译成静态库
* 把`sort`编译成动态库
* 分别编译`test1`和`test2`，并链接对应的库，以便进行函数调用

**根目录的`CMakeLists.txt`**

```cmake
cmake_minimum_required(VERSION 3.0)
project(test)
# 定义变量
# 静态库生成的路径
set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
# 测试程序生成的路径
set(EXEC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# 头文件目录
set(HEAD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
# 静态库的名字
set(CALC_LIB calc)
set(SORT_LIB sort)
# 可执行程序的名字
set(APP_NAME_1 test1)
set(APP_NAME_2 test2)
# 添加子目录
add_subdirectory(calc)
add_subdirectory(sort)
add_subdirectory(test1)
add_subdirectory(test2)
```

**calc目录的`CMakeLists.txt`**

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALCLIB)
# 搜索当前目录下的所有源文件
aux_source_directory(./ SRC)
# 设置头文件路径
include_directories(${HEAD_PATH})
# 设置库的生成路径
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})
# 生成静态库
add_library(${CALC_LIB} STATIC ${SRC})
```

**sort目录的`CMakeLists.txt`**

```cmake
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
```

**test1目录的`CMakeLists.txt`**

```cmake
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
```

**test2目录的`CMakeLists.txt`**

```cmake
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
```

编译后生成的文件：

```txt
$ tree bin/ lib/
bin/
├── test1
└── test2
lib/
├── libcalc.a
└── libsort.so
```

> 在项目中，如果将程序中的某个模块制作成了动态库或者静态库并且在CMakeLists.txt 中指定了库的输出目录，而后其它模块又需要加载这个生成的库文件，此时直接使用就可以了，如果没有指定库的输出路径或者需要直接加载外部提供的库文件，此时就需要使用 link_directories 将库文件路径指定出来。



## 4. 流程控制

略



## 补充资料

### 1. win10 的linux 子系统环境安装

> 参考：https://deepinout.com/wsl-tutorials/36_installing_wsl_on_windows_10.html

WSL（Windows Subsystem for Linux）是 Windows 10 系统上的 Linux 子系统。

**1. 启用wsl功能**

1. 打开 PowerShell，以管理员身份运行，输入以下代码并按下回车键：

    ```cmd
    dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
    ```

2. 输入以下代码并按下回车键，将 WSL2 设置为默认版本

   ```cmd
   dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
   ```

3. 重启 Windows 10 系统，以便使修改生效。

**2. 从 Microsoft Store 下载 Ubuntu 发行版**

1. 搜索 Microsoft Store，打开它。
2. 在搜索框中输入 Ubuntu，点击搜索按钮。
3. 安装 Ubuntu。如果是第一次下载应用程序，需要输入 Microsoft 账号和密码以进行认证。
4. 安装完成后，Ubuntu 应用程序图标将出现在 Windows 启动菜单中。

**3. 配置和使用**

1. 双击 Ubuntu 应用程序图标打开，在初始化过程中设置用户名和密码。

2. 在 Ubuntu 中可以访问 Windows 系统上的文件和文件夹，即使当前的用户没有管理员权限，也可以使用以下命令跨越多个系统：

   ```cmd
   cd /mnt/d/ # 在 Ubuntu 终端中访问 Windows D 盘
   cd /mnt/e/ # 在 Ubuntu 终端中访问 Windows E 盘
   ```

> 上面安装的貌似是wsl1版本的，wsl2版本的安装还没试过，可以参考 https://deepinout.com/wsl-tutorials/37_installing_wsl2_on_windows_10.html



### 2. vs code 连接wsl

1. 下载插件：`Remote Development`

2. 点击右下角，选择`Connect to WSL`

   <img src="assets/image-20230813112431954.png" alt="image-20230813112431954" style="zoom:50%;" />