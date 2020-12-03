#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "iconv.hpp"
#include "misc.h"
#include "TCPclient.h"

class HTTPclient {
	iconvpp::converter converter;
	std::string _url;
	std::string makeHeaders(const std::string& method, const std::string& suffix, 
		const std::vector<std::pair<std::string, std::string>>& args = {}) const;
public:
	HTTPclient(const std::string& url,const std::string& encode="utf-8");
	std::string get(const std::string& suffix = "",
		const std::vector<std::pair<std::string, std::string>>& args = {}) ;
};