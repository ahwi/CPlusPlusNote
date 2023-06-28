# c++视频学习笔记（cherno）

学习资料：

* B站`https://www.bilibili.com/video/BV1Xf4y1v7he`

## 1. 欢迎来到 c++

略

## 2. windows 上安装 c++

略

## 3. Mac 上安装 c++

略

## 4. Linux上安装 c++

略



## 13. Visual Studio的最佳设置

创建一个空的项目，NewProject

<img src="C++_Cherno视频学习笔记.assets/image-20230628204930400.png" alt="image-20230628204930400" style="zoom:50%;" />

添加Main.cpp

![image-20230628205148250](C++_Cherno视频学习笔记.assets/image-20230628205148250.png)

上图中的类似目录的东西，只是一个过滤器，并非真实的目录，只是用来更好的组织文件。

点击下图红色按钮，可以看到真实的目录结构

![image-20230628205314053](C++_Cherno视频学习笔记.assets/image-20230628205314053.png)

添加一个src目录，把Main.cpp挪进去

![image-20230628205432374](C++_Cherno视频学习笔记.assets/image-20230628205432374.png)

设置编译后文件的输出目录

<img src="C++_Cherno视频学习笔记.assets/image-20230628210352541.png" alt="image-20230628210352541" style="zoom:50%;" />

```txt
输出目录： $(SolutionDir)bin\$(Platform)\$(Configuration)\
中间目录： $(SolutionDir)bin\intermedia\$(Platform)\$(Configuration)\
```

## 16. c++ 指针

**指针是一种数字，一种存储内存地址的数字**

* 指针的类型不重要，它只是用来只是编译器所指向数据的类型，以便让它知道要数据占多大的内存
* 指针的值也是存在一个内从块中
* 二级指针就是一个存储另一个指针地址的指针