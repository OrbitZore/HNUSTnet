#include <iostream>
#include <fstream>
#include <iterator>
#include "HNUSTnet.h"

using namespace std;

const string helpMessage = "\
提供校园网登录的API调用\n\
\n\
:登录\n\
HNUSTnet login username userpwd ISPname\n\
\n\
username\t用户名\n\
userpwd \t用户密码\n\
ISPname \t运营商英文名(见下)\n\
\n\
:登出\n\
HNUSTnet logout\n\
\n\
\n\
ISPname可选值\n\
\n\
school\t校园网\n\
telecom\t电信\n\
unicom\t联通\n\
cmcc\t中国移动\n\
";

string config_file;
string method;
User user;

extern std::map<std::string, std::string> ISPtoArgs;

int main(int argc, char* argv[]) {

	int argStatus = [&]()->int {
		if (argc < 5) return -2;
		if (argc > 5) return -1;
		method = string(argv[1]);
		if (method != "login" && method != "logout") return 1;
		user._name = string(argv[2]);
		user._pwd = string(argv[3]);
		user._isp = string(argv[4]);
		if (ISPtoArgs.count(user._isp) == 0) return -7;
		return 0;
	}();
	switch (argStatus){
		case -10: 
			cerr << "参数太少\n";
			break;
		case -9:
			cerr << "参数太多\n";
			break;
		case -8:
			cerr << "方法格式错误";
			break;
		case -7:
			cerr << "运营商格式错误\n";
			break;
	}
	if (argStatus < 0) { cout << helpMessage; return argStatus; }
	HNUSTnet main(user);
	main.loop();
	return 0;
}