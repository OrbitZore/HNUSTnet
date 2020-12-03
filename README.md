# HNUSTnet v1.1

A iHNUST auto connect tool

一个湖南科技大学校园网自动登录/重新登录工具

## Feature

- 登录
- 掉线自动重连
- 注销

以后会实现的功能

- 流量统计

## Quick Start

下载[HNUSTnet](https://github.com/OrbitZore/HNUSTnet/releases/latest)

在当前目录使用命令行输入

```bash
.\HNUSTnet autologin [学号] [密码] [运营商英文]
```

回车即可实现自动登录以及断线重连

运营商英文可选如下

| 可选值  | 含义   |
| ------- | ------ |
| school  | 校园网 |
| telecom | 电信   |
| unicom  | 联通   |
| cmcc    | 移动   |

## 全指令一览

```cmd
.\HNUSTnet logout
```
登出


```cmd
.\HNUSTnet login [学号] [密码] [运营商英文]
```
登录

```cmd
.\HNUSTnet autologin [学号] [密码] [运营商英文]
```
自动登录

## Build

### Ubuntu

如官方源下载速度不佳可切换软件源至[TUNA](https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/)

```bash
sudo apt update
sudo apt install libboost-dev libboost-system-dev cmake make g++ git libiconv
git clone https://github.com/OrbitZore/HNUSTnet.git
mv HNUSTnet HNUSTnet-build
cd HNUSTnet-build
mkdir build
cd build
cmake ..
make -j4
cp HNUSTnet/HNUSTnet ../../
cd ../../
rm HNUSTnet-build/ -R
```

构建的HNUSTnet可执行文件即在当前目录

### Windows

请安装vcpkg和Visual Studio 2019

```cmd
vcpkg install boost iconv libiconv
```

下载源代码zip文件解压至目录下

在Visual Studio 2019中点击文件->打开->CMake，然后等候Visual Studio生成项目。

生成项目完成后，点击生成，全部生成。即可在/out/build/xxxxx/HNUSTnet/目录中找到HNUSTnet.exe

## Update Log

2020/12/3 v1.2-修复编码问题

2020/11/15 v1.1-修复内存泄漏问题

2020/11/14 v1.0-修复bug，实现跨平台编译

2020/11/13 beta2.0-分离自动登录和登录，实现登出。修复bug，提高程序稳定性

2020/11/11 beta1.0-实现登录

