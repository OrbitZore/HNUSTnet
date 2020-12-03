#include "HTTPclient.h"

using namespace std;

const std::string CONTENT_LENGTH("content-length");

HTTPclient::HTTPclient(const string& url,const string& encode):_url(url), converter("utf-8",encode) {

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

    
    auto s(makeClient(_url));

    *s << makeHeaders("GET",suffix, args);

    string rec;
    readUntil(*s, rec, "\n"); rec.clear();
    //不处理http状态码
    readUntil(*s, rec, "\r\n\r\n");

    for_each(rec.begin(), rec.end(), [](string::value_type& i) {i = tolower(i); });

    long long length=-1;

    for (auto& i : split(rec, "\n"))
        if (prefix_with(i, CONTENT_LENGTH)) {
            stringstream(i.substr(i.find_last_of(":") + 1)) 
                >> length;
            break;
        }
    rec.clear();

    if (length == -1)
        readUntil(*s,rec,"\r\n\r\n");
    else
        for (int i = 1; i <= length&&*s; i++)
            rec += s->get();

    if (!*s) {
        cerr << "TCP连接错误" << endl;
        return "";
    }
    return converter.convert(rec);
}