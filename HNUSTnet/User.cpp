#include "user.h"
using namespace std;

std::map<std::string, std::string> ISPtoArgs = { {"school",""},{"telecom","%40telecom"},{"unicom","%40unicom"},{"cmcc","%40cmcc"} };

User::User() {}

User::User(string name,string pwd, string isp):_name(name),_pwd(pwd),_isp(isp) {}

vector<pair<string, string>> User::gen() {
	return {
		{"user_account","%2C0%2C"+_name+ ISPtoArgs[_isp]},
		{"user_password",_pwd}
	};
}