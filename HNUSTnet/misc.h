#pragma once
#include <string>
#include <iostream>
#include <vector>
std::vector<std::string> split(const std::string& str, const std::string& delimiters);
bool prefix_with(const std::string& str, const std::string& sub);
bool subfix_with(const std::string& str, const std::string& sub);