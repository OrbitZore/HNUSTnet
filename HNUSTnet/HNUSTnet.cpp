// HNUSTnet.cpp: 定义应用程序的入口点。
//

#include "HNUSTnet.h"
using namespace std;
using boost::asio::chrono::seconds;

string getIP(string head, string nil){
	string resp = HTTPclient("login.hnust.cn").get();
	auto beg = resp.find(head) + head.size();
	if (beg >= resp.size()) return "";
	auto len = resp.find(nil, beg);
	if (len >= resp.size()) return "";
	return resp.substr(beg, len - beg);
}

bool checkIP(string ip) {
	vector<string> ips = split(ip, ".");
	if (ips.size() != 4) return false;
	for (auto& i : ips) {
		int part = stoi(i);
		if (!(part >= 0 && part <= 255)) return false;
	}
	return true;
}

HNUSTnet::HNUSTnet(const User& user):_user(user) {
	ip = getIP("v4ip='", "'");
	if (!checkIP(ip)) {
		ip = getIP("v46ip='", "'");
		if (!checkIP(ip)) {
			cerr << "服务器返回ip不符合要求\n";
			ip = "0.0.0.0";
		}
	}
	cout << "当前ip为" << ip << endl;
}
static bool TCPGood = true;
bool HNUSTnet::getOnline() {
	string resp = HTTPclient("login.hnust.cn").get();
	if (resp.find("上网登录页") != resp.npos) return false;
	else
	if (resp.find("注销页") != resp.npos) return true;
	else {
		if (resp.size() == 0) return TCPGood = false;
		else TCPGood = true;
		cerr << "服务器返回在线状态错误\n";
		return false;
	}
}

string HNUSTnet::login() {
	cout << "尝试登录" << endl;
	HTTPclient client("login.hnust.cn:801");
	vector<pair<string, string>> args;
	args.push_back({ "c","Portal" });
	args.push_back({ "a","login" });
	args.push_back({ "login_method","1" });
	args.push_back({ "wlan_user_ip",ip });
	for (auto& i : _user.gen()) args.push_back(i);
	args.push_back({ "v",to_string(rand() % 9000 + 1000) });
	return client.get("eportal/", args);
}

string HNUSTnet::logout() {
	cout << "尝试登出" << endl;
	HTTPclient client("login.hnust.cn:801");
	vector<pair<string, string>> args;
	args.push_back({ "c","Portal" });
	args.push_back({ "a","logout" });
	args.push_back({ "login_method","1" });
	args.push_back({ "wlan_user_ip",ip });
	args.push_back({ "v",to_string(rand() % 9000 + 1000) });
	return client.get("eportal/", args);
}

void HNUSTnet::loop() {
	boost::asio::io_context io;
	while (true) {
		bool f = false;
		while (!getOnline()) {
			if (TCPGood) {
				cout << "检测到未登录" << endl;
				login();
				f = true;
			}
			else {
				cout << "检测到未连接iHNUST，等待5s" << endl;
				boost::asio::steady_timer t(io, seconds(5));
				t.wait();
			}
		}
		if (f) cout << "登入成功" << endl;
		boost::asio::steady_timer t(io, seconds(5));
		t.wait();
	}
}