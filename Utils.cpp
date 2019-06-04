//
// Created by rd on 16/05/2019.
//

#include <iostream>
#include "Utils.hpp"

vector<string> splitString(const string &s, char d) {
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
	if (chars >= s.length()) {
		return s;
	}
	return s.substr(0, chars);
}

vector<string> splitStringToRows(string s, int l) {
	vector<string> output;

	while (s.length() > l) {

		int lastSpacePos = 0;
		//Search last space before end of the line
		for (int i = 0; i < l; ++i) {
			if (s[i] == ' ') {
				lastSpacePos = i;
			}
		}

		if (lastSpacePos == 0) {
			//Space not found, break string
			output.push_back(cropString(s, l));
			s = s.substr(l);
		} else {
			//Space found, split at space and remove it
			output.push_back(cropString(s, lastSpacePos));
			s = s.substr(lastSpacePos + 1);
		}
	}

	output.push_back(s);
	return output;
}
