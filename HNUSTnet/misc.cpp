#include "misc.h"
using namespace std;
vector<string> split(const string& str, const string& delimiters) {
	vector<string> ans;
	auto lastPos = str.find_first_not_of(delimiters, 0);
	auto pos = str.find_first_of(delimiters, lastPos);
	while (pos != string::npos || lastPos != string::npos) {
		ans.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
	return ans;
}

bool prefix_with(const string& str, const string& sub) {
	if (str.size() < sub.size()) return false;
	for (auto i=str.begin(),j=sub.begin(); j != sub.end(); i++,j++)
		if (*i != *j) return false;
	return true;
}

bool subfix_with(const string& str, const string& sub) {
	if (str.size() < sub.size()) return false;
	for (auto i = str.end()-sub.size(), j = sub.begin(); j != sub.end(); i++,j++)
		if (*i != *j) return false;
	return true;
}

void readUntil(istream& input, string& str, const string &c) {
	str.clear();
	while (!subfix_with(str,c)&&input)
		str+=input.get();
}