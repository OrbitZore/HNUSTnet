# HNUSTnet

A iHNUST auto connect tool

一个湖南科技大学校园网自动登录/重新登录工具

## Feature

- 登录
- 自动重连

之后会实现的功能

- ~~注销~~
- 流量统计

## Quick Start

下载[HNUSTnet.exe](https://github.com/OrbitZore/HNUSTnet/releases/download/b1.0/HNUSTnet.exe)

在当前目录使用命令行输入

```bash
.\HNUSTnet.exe [学号] [密码] [运营商英文]
```

回车即可实现自动登录

运营商英文可选如下



| 可选值  | 含义   |
| ------- | ------ |
| school  | 校园网 |
| telecom | 电信   |
| unicom  | 联通   |
| cmcc    | 移动   |

## Build

本程序使用cmake进行跨平台编译

请确保环境中安装有boost.asio

