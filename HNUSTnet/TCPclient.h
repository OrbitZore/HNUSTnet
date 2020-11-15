#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include "misc.h"

std::unique_ptr<boost::asio::ip::tcp::iostream> makeClient(std::string url);