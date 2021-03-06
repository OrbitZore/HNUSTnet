﻿// HNUSTnet.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include "HTTPclient.h"
#include "User.h"

class HNUSTnet {
	User _user;
	std::string ip;
public:
	HNUSTnet(const User &user);
	bool getOnline();
	std::string login();
	std::string logout();
	void loop();
};
// TODO: 在此处引用程序需要的其他标头。
