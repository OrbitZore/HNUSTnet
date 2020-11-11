#include "HTTPclient.h"

using namespace std;
using boost::asio::ip::tcp;

const std::string CONTENT_LENGTH("content-length");

HTTPclient::HTTPclient(string url):_url(url) {

}

string HTTPclient::makeHeaders(const string& method,const string& suffix, const vector<pair<string, string>>& args) const {
    string str;
    str += method + " /"+ suffix + [&]()->string{
        string tmp;
        bool f = true;
        for (auto& i : args) {
            tmp += (f ? '?' : '&');
            f = false;
            tmp += i.first + "=" + i.second;
        }
        return tmp;
    }() + " HTTP/1.1\n";
    str += "Host: " + _url + "\r\n";
    str += "Accept: */*\r\n";
    str += "User-Agent: curl/7.55.1\r\n\r\n";
    return str;
}

string HTTPclient::get(const string& suffix,const vector<pair<string, string>>& args){
    auto urls = split(_url, ":");
    string port;
    if (urls.size() == 1) port = "80";
    else port = urls[1];
    tcp::iostream s(urls[0],port);
    s.expires_from_now(std::chrono::seconds(60));
    s << makeHeaders("GET",suffix, args);
    string ans,status;
    getline(s, status);
    if (status.find("OK")==string::npos) {
        cerr << "Socket error: " << s.error().message() << "\n";
        return "";
    }

    while (!subfix_with(ans,"\r\n\r\n"))
        ans += s.get();
    for_each(ans.begin(), ans.end(), [](string::value_type& i) {i = tolower(i); });

    long long length=0;

    for (auto& i : split(ans, "\n"))
        if (prefix_with(i, CONTENT_LENGTH)) {
            stringstream in(i.substr(i.find_last_of(":")+1));
            in >> length;
            break;
        }

    ans.clear();
    for (int i = 1; i <= length; i++)
        ans += s.get();

    if (!s) {
        cerr << "Socket error: " << s.error().message() << "\n";
        return "";
    }
    return ans;
}