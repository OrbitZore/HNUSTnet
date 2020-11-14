# CMakeList.txt: HNUSTnet 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS REQUIRED system)
find_path(BOOST_ASIO_INCLUDE_DIRS "boost/asio.hpp")

include_directories(${Boost_INCLUDE_DIRS} ${BOOST_ASIO_INCLUDE_DIRS})

add_executable (HNUSTnet "main.cpp" "HNUSTnet.cpp" "HNUSTnet.h" "HTTPclient.cpp" "HTTPclient.h" "misc.h" "misc.cpp" "User.h" "User.cpp" "TCPclient.h" "TCPclient.cpp")
target_link_libraries(HNUSTnet ${Boost_LIBRARIES})