#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <boost/asio.hpp>
#include "misc.h"

class HTTPclient {
	std::string _url;
	std::string makeHeaders(const std::string& method, const std::string& suffix, const std::vector<std::pair<std::string, std::string>>& args = {}) const;
public:
	HTTPclient(std::string url);
	std::string get(const std::string& suffix="", const std::vector<std::pair<std::string, std::string>>& args = {}) ;
};