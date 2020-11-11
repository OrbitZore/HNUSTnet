// HNUSTnet.cpp: 定义应用程序的入口点。
//

#include "HNUSTnet.h"
using namespace boost::asio;
using boost::asio::chrono::seconds;
using namespace std;

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
		cout << ip << endl;
		if (!checkIP(ip)) {
			cerr << "服务器返回ip不符合要求\n";
			exit(-100);
		}
	}
}

void HNUSTnet::freshStatus() {
	string resp = HTTPclient("login.hnust.cn").get();
	if (resp.find("上网登录页") != resp.npos) isOnline = false;
	else
	if (resp.find("注销页") != resp.npos) isOnline = true;
	else {
		cerr << "服务器返回在线状态错误\n";
		exit(-101);
	}

}

void HNUSTnet::loop() {
	io_context io;
	while (true) {
		freshStatus();
		if (!isOnline) {
			HTTPclient client("login.hnust.cn:801");
			vector<pair<string, string>> args;
			args.push_back({ "c","Portal" });
			args.push_back({ "a","login"  });
			args.push_back({ "login_method","1" });
			args.push_back({ "wlan_user_ip",ip});
			for (auto &i: _user.gen()) args.push_back(i);
			args.push_back({"v",to_string(rand()%9000+1000)});
			client.get("eportal/", args);
		}
		steady_timer t(io, seconds(5));
		t.wait();
	}
}