#include <iostream>
#include <fstream>
#include <iterator>
#include "HNUSTnet.h"

using namespace std;

const string helpMessage = "\
�ṩУ԰����¼��API����\n\
\n\
:��¼\n\
HNUSTnet login username userpwd ISPname\n\
\n\
username\t�û���\n\
userpwd \t�û�����\n\
ISPname \t��Ӫ��Ӣ����(����)\n\
\n\
:�ǳ�\n\
HNUSTnet logout\n\
\n\
\n\
ISPname��ѡֵ\n\
\n\
school\tУ԰��\n\
telecom\t����\n\
unicom\t��ͨ\n\
cmcc\t�й��ƶ�\n\
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
			cerr << "����̫��\n";
			break;
		case -9:
			cerr << "����̫��\n";
			break;
		case -8:
			cerr << "������ʽ����";
			break;
		case -7:
			cerr << "��Ӫ�̸�ʽ����\n";
			break;
	}
	if (argStatus < 0) { cout << helpMessage; return argStatus; }
	HNUSTnet main(user);
	main.loop();
	return 0;
}