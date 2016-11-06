#include "NumericUtils.h"
#include "StringUtils.h"

using namespace std;

void trim_zeroes(string& str) {
	string::size_type length = str.length();
	string::size_type index = length;
	for (string::reverse_iterator i = str.rbegin(); i != str.rend(); ++i, --index) {
		char c = *i;
		if (c != '0' && c != '.') {
			break;
		}
	}
	if (index != length) {
		str = str.substr(0,index);
	}
}

string NumericUtils::to_word(char n) {
	return to_word((int)n);
}
string NumericUtils::to_word(unsigned char n) {
	return to_word((unsigned int)n);
}
string NumericUtils::to_word(short n) {
	return to_word((int)n);
}
string NumericUtils::to_word(unsigned short n) {
	return to_word((unsigned int)n);
}
string NumericUtils::to_word(int n) {
	string str = to_string(n);
	return StringUtils::to_word(str);
}
string NumericUtils::to_word(unsigned int n) {
	string str = to_string(n);
	return StringUtils::to_word(str);
}
string NumericUtils::to_word(long n) {
	string str = to_string(n);
	return StringUtils::to_word(str);
}
string NumericUtils::to_word(unsigned long n) {
	string str = to_string(n);
	return StringUtils::to_word(str);
}
string NumericUtils::to_word(long long n) {
	string str = to_string(n);
	return StringUtils::to_word(str);
}
string NumericUtils::to_word(unsigned long long n) {
	string str = to_string(n);
	return StringUtils::to_word(str);
}
string NumericUtils::to_word(float n) {
	string str = to_string(n);
	trim_zeroes(str);
	return StringUtils::to_word(str);
}
string NumericUtils::to_word(double n) {
	string str = to_string(n);
	trim_zeroes(str);
	return StringUtils::to_word(str);
}
string NumericUtils::to_word(long double n) {
	string str = to_string(n);
	trim_zeroes(str);
	return StringUtils::to_word(str);
}

