#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include "misc.h"

std::unique_ptr<std::basic_iostream<char>> makeClient(std::string url);