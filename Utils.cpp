//
// Created by rd on 16/05/2019.
//

#include "Utils.hpp"

vector<string> splitString(string s, char d) {
	vector<string> output;

	int start = 0, end = 0, length = s.length();
	do {
		end = s.find(d, start);
		if (end == string::npos) { end = length; }

		output.push_back(s.substr(start, end - start));
		start = end + 1;
	} while (end < length);

	return output;
}

string cropString(const string &s, int chars) {
	return s.substr(0, chars);
}
