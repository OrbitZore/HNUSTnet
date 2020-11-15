#include "TCPclient.h"

using namespace boost::asio::ip;
using namespace std;

unique_ptr<tcp::iostream> makeClient(string url) {
    auto urls = split(url, ":");
    string port;
    if (urls.size() == 1) port = "80";
    else port = urls[1];
    auto ptr = unique_ptr<tcp::iostream>(new tcp::iostream(urls[0], port));
    ptr->expires_from_now(std::chrono::seconds(60));
    return ptr;
}
