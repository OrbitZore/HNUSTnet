#include "TCPclient.h"

using namespace boost::asio::ip;
using namespace std;

unique_ptr<basic_iostream<char>> makeClient(string url) {
    auto urls = split(url, ":");
    string port;
    if (urls.size() == 1) port = "80";
    else port = urls[1];
    auto* ptr = new tcp::iostream(urls[0], port);
    ptr->expires_from_now(std::chrono::seconds(60));
    unique_ptr<basic_iostream<char>> ptre(ptr);
    return ptre;
}
