# CMakeList.txt: HNUSTnet 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

set(Boost_USE_STATIC_LIBS		ON)
set(Boost_USE_DEBUG_LIBS		OFF)
set(Boost_USE_RELEASE_LIBS		ON) 
set(Boost_USE_MULTITHREADED		ON)
set(Boost_USE_STATIC_RUNTIME	OFF)

find_package(Threads)
find_package(Iconv)
find_package(Boost COMPONENTS REQUIRED system)
find_path(BOOST_ASIO_INCLUDE_DIRS "boost/asio.hpp")

include_directories(${Boost_INCLUDE_DIRS} ${BOOST_ASIO_INCLUDE_DIRS} ${Iconv_INCLUDE_DIRS})

link_libraries(${Boost_LIBRARIES})
link_libraries(${CMAKE_THREAD_LIBS_INIT})
link_libraries(${Iconv_LIBRARIES})

add_executable (HNUSTnet "main.cpp" "HNUSTnet.cpp" "HNUSTnet.h" "HTTPclient.cpp" "HTTPclient.h" "misc.h" "misc.cpp" "User.h" "User.cpp" "TCPclient.h" "TCPclient.cpp")
