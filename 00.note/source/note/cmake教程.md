# CMake 保姆级教程

学习资料：

* 视频：`CMake 保姆级教程【c/c++】` 爱编程的大丙  `https://www.bilibili.com/video/BV14s4y1g7Zj`
* 文章：`https://subingwen.cn/cmake/CMake-primer/`

## 1. CMake 概述





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

1. 下载插件：`remote explorer`

2. 点击右下角，选择`Connect to WSL`

   <img src="assets/image-20230813112431954.png" alt="image-20230813112431954" style="zoom:50%;" />