#pragma once
#include <string>
#include <vector>
#include <map>

struct User {
	std::string _name, _pwd, _isp;
	User();
	User(std::string name, std::string pwd, std::string isp);
	std::vector<std::pair<std::string, std::string>> gen();
};