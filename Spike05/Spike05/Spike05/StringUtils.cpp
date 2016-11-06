#include "StringUtils.h"
#include <iostream>

using namespace std;

bool StringUtils::is_whitespace(const char& c) {
	return c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ';
}
string StringUtils::trim_left(string str) {
	string res = "";
	if (str != "") {
		int startIndex = 0;
		int endIndex = str.length();
		while (startIndex < endIndex && is_whitespace(str[startIndex])) {
			++startIndex;
		}
		res = str.substr(startIndex,endIndex - startIndex);
	}
	return res;
}
string StringUtils::trim_right(string str) {
	string res = "";
	if (str != "") {
		int endIndex = str.length() - 1;
		int startIndex = 0;
		while (startIndex <= endIndex && is_whitespace(str[endIndex])) {
			--endIndex;
		}
		res = str.substr(startIndex,endIndex + 1);
	}
	return res;
}
string StringUtils::trim(string str) {
	return trim_right(trim_left(str));
	/*
	string res = "";
	if (str != "") {
		int startIndex = 0;
		int endIndex = str.length();
		while (startIndex < endIndex && is_whitespace(str[startIndex])) {
			++startIndex;
		}
		if (startIndex != endIndex) {
			while (is_whitespace(str[endIndex])) {
				--endIndex;
			}
			res = str.substr(startIndex,endIndex - startIndex);
		}
	}
	return res;
	*/
}