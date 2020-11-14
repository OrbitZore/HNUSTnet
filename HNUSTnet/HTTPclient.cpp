#include "HTTPclient.h"

using namespace std;

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

    
    auto s = makeClient(_url);

    *s << makeHeaders("GET",suffix, args);

    string ans,status;
    getline(*s, status);

    while (!subfix_with(ans,"\r\n\r\n"))
        ans += s->get();
    for_each(ans.begin(), ans.end(), [](string::value_type& i) {i = tolower(i); });

    long long length=-1;

    for (auto& i : split(ans, "\n"))
        if (prefix_with(i, CONTENT_LENGTH)) {
            stringstream in(i.substr(i.find_last_of(":") + 1));
            in >> length;
            break;
        }
    ans.clear();

    if (length == -1) 
        while (!subfix_with(ans, "\r\n\r\n")&&(!(*s)))
            ans += s->get();
    else
        for (int i = 1; i <= length; i++)
            ans += s->get();

    if (!*s) {
        cerr << "TCPÁ¬½Ó´íÎó" << endl;
        return "";
    }
    return ans;
}