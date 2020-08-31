#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

int exit() {
	system("pause");
	return 1;
}

string different(string str1, string str2) {
	if (str1 == "") {
		return str2;
	}
	string ans = "";
	for (int i = 0; i < str1.length(); i++) {
		if (str1.at(i) != str2.at(i)) {
			ans += "?";
			continue;
		}
		ans += str1.at(i);
	}

	return ans;
}

void replaceAll(string& str, const string& from, const string& to) {
	if (from.empty())
		return;

	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

string processPattern(string raw) {
	string result = "";
	for (int i = 0; i < raw.size(); i++) {
		if (i % 2 == 0 && i != 0) {
			result += " ";
		}
		result += raw.at(i);
	}
	return result;
}

void end(ofstream* aob, vector<string> raw, int diff, string pattern) {
	*aob << "原始字節數組: " << endl;
	if (raw.size() == 0) {
		*aob << "    " << "沒有字節數組" << endl;
	}
	else {
		for (string s : raw) {
			*aob << "    " << s << endl;
		}
	}
	*aob << "總共" << raw.size() << "組" << endl;
	*aob << "變動: " << diff << endl;
	*aob << "模板: " << endl;
	*aob << "    " << pattern;
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		cout << "把字節數組檔案拖曳到程式上" << endl;
		return exit();
	}

	ifstream file(argv[1], ios::in);
	ofstream aob("pattern.txt", (ios::out | ios::trunc));
	if (!file && !aob) {
		cout << "檔案開啟失敗" << endl;
		file.close();
		aob.close();
		return exit();
	}

	vector<string> raw;
	vector<string> read;
	{
		string s;
		int preLen = -1; // 前一個數組的長度
		while (getline(file, s)) {
			raw.push_back(s);
			replaceAll(s, " ", "");
			if (s.size() != preLen && preLen != -1) {
				cout << "字節數組長度都需相同" << endl;
				return exit();
			}
			preLen = s.size();
			read.push_back(s);
		}
	}

	if (read.size() == 1) {
		end(&aob, raw, 0, raw.at(0));
		return exit();
	}
	else if (read.size() == 0) {
		end(&aob, raw, 0, "沒有字節數組");
		return exit();
	}

	string rawpattern = accumulate(read.begin(), read.end(), string(""), different);
	string pattern = processPattern(rawpattern);
	int diff = count(pattern.begin(), pattern.end(), '?');

	end(&aob, raw, diff, pattern);

	file.close();
	aob.flush();
	aob.close();
	return 0;
}