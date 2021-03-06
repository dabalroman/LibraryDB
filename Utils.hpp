#ifndef LIBRARYDB_UTILS_HPP
#define LIBRARYDB_UTILS_HPP

#include <vector>
#include <string>

using namespace std;

enum KEY : int {
	BACKSPACE = 8,
	ENTER = 13,
	ESC = 27,
	ARROW_UP = 38,
	ARROW_DOWN = 40,
	ARROW_LEFT = 37,
	ARROW_RIGHT = 39,
	DEL = 46,
	A = 65,
	C = 67,
	E = 69,
	I = 73,
	N = 78,
	S = 83,
	T = 84,
	Z = 90,
};

/**
 * Splits string into substrings
 * @param s String
 * @param d Delimiter
 * @return Vector w/ substrings
 */
vector<string> splitString(const string &s, char d);

/**
 * Splits string into rows
 * @param s String
 * @param l Row length
 * @return Vector w/ rows
 */
vector<string> splitStringToRows(string s, int l);

/**
 * Crop string to given length
 * @param s String
 * @param chars Length
 * @return String
 */
string cropString(const string &s, int chars);

#endif //LIBRARYDB_UTILS_HPP
