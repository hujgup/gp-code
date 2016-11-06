#include "StringUtils.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

string get_word(int index) {
	switch (index) {
		case 0:
			return "Thousand";
			break;
		case 1:
			return "Million";
			break;
		case 2:
			return "Billion";
			break;
		case 3:
			return "Trillion";
			break;
		default:
			throw logic_error("Word at given index does not exist.");
			break;
	}
}
string last_word() {
	return get_word(3);
}

class Components {
private:
	string _remainder;
	string _magnitude;
	bool _hasRemainder;
	bool _hasMagnitude;
	bool exists(const string& str) const;
	Components();
public:
	Components(const string& str,string::size_type index);
	const string& remainder() const;
	const string& magnitude() const;
	const bool& has_remainder() const;
	const bool& has_magnitude() const;
};

bool Components::exists(const string& str) const {
	bool res = false;
	for (string::const_iterator i = str.cbegin(); !res && i != str.cend(); ++i) {
		const char c = *i;
		res = c != '0';
	}
	return res;
}
Components::Components(const string& str,string::size_type index) {
	index = str.length() - index;
	_remainder = str.substr(index);
	_magnitude = str.substr(0,index);
	_hasRemainder = exists(_remainder);
	_hasMagnitude = exists(_magnitude);
}
const string& Components::remainder() const {
	return _remainder;
}
const string& Components::magnitude() const {
	return _magnitude;
}
const bool& Components::has_remainder() const {
	return _hasRemainder;
}
const bool& Components::has_magnitude() const {
	return _hasMagnitude;
}

void internal_to_word(const char& c,string& builder);

void resolve_mod(const char& c,string& builder) {
	switch (c) {
		case '2':
			builder += "Twen";
			break;
		case '3':
			builder += "Thir";
			break;
		case '5':
			builder += "Fif";
			break;
		case '8':
			builder += "Eigh";
			break;
		default:
			internal_to_word(c,builder);
			break;
	}
}

void internal_to_word(const char& c,string& builder) {
	switch (c) {
		case '0':
			builder += "Zero";
			break;
		case '1':
			builder += "One";
			break;
		case '2':
			builder += "Two";
			break;
		case '3':
			builder += "Three";
			break;
		case '4':
			builder += "Four";
			break;
		case '5':
			builder += "Five";
			break;
		case '6':
			builder += "Six";
			break;
		case '7':
			builder += "Seven";
			break;
		case '8':
			builder += "Eight";
			break;
		case '9':
			builder += "Nine";
			break;
	}
}

void internal_to_word(const string& str,string& builder);

void internal_to_word_int_component(const string& str,string& builder) {
	string::size_type length = str.length();
	switch (length) {
		case 1: // < 10
			internal_to_word(str[0],builder);
			break;
		case 2: // < 100
			{
				const char initChar = str[0];
				if (initChar == '1') { // < 20
					resolve_mod(str[1],builder);
					builder += "teen";
				} else { // >= 20
					resolve_mod(initChar,builder);
					builder += "ty";
					const char lastChar = str[1];
					if (lastChar != '0') {
						builder += "-";
						internal_to_word(lastChar,builder);
					}
				}
			}
			break;
		case 3: // < 1000
			{
				Components c(str,2);
				if (c.has_magnitude()) {
					internal_to_word(c.magnitude(),builder);
					builder += " Hundred";
				}
				if (c.has_remainder()) {
					builder += " and ";
					internal_to_word(c.remainder(),builder);
				}
			}
			break;
		default:
			if (length < 15) { // 999,999,999,999,999 or less (999 trillion...)
				string::size_type index = length - 3;
				int magnitude = 0;
				while (index > 3) {
					index -= 3;
					++magnitude;
				}
				string sub = str.substr(0,index);
				internal_to_word(sub,builder);
				builder += " ";
				builder += get_word(magnitude);
				builder += ", ";
				sub = str.substr(index);
				internal_to_word(sub,builder);
			} else { // Really big numbers
				// (427 Billion, 101 Million, 400 Thousand, 124) Trillion, 78 Billion...
				string::size_type index = length - 15;
				builder += "(";
				string sub = str.substr(0,index);
				internal_to_word(sub,builder);
				builder += ") ";
				builder += last_word();
				builder += ", ";
				sub = str.substr(index);
				internal_to_word(sub,builder);
			}
			break;
	}
}

void internal_to_word(const string& str,string& builder) {
	if (str[0] == '-') {
		builder += "Negative ";
		string sub = str.substr(1);
		internal_to_word(sub,builder);
	} else if (str.length() == 1) {
		internal_to_word(str[0],builder);
	} else if (str == "10") {
		builder += "Ten";
	} else if (str == "11") {
		builder += "Eleven";
	} else if (str == "12") {
		builder += "Twelve";
	} else if (str == "20") {
		builder += "Twenty";
	} else if (str == "40") {
		builder += "Forty";
	} else {
		string::size_type decIndex = str.find('.',0);
		if (decIndex != string::npos) {
			string intComponent = str.substr(0,decIndex);
			internal_to_word_int_component(intComponent,builder);
			string decComponent = str.substr(decIndex + 1);
			builder += " point";
			for (string::const_iterator i = decComponent.cbegin(); i != decComponent.cend(); ++i) {
				builder += " ";
				internal_to_word(*i,builder);
			}
		} else {
			internal_to_word_int_component(str,builder);
		}
	}
}

string StringUtils::to_word(const char& c) {
	string builder;
	internal_to_word(c,builder);
	return builder;
}
string StringUtils::to_word(const string& str) {
	bool hasDecPoint = false;
	bool oneAfterPoint = false;
	for (string::const_iterator i = str.cbegin(); i != str.cend(); ++i) {
		if (!isdigit(*i)) {
			if (*i == '.') {
				if (hasDecPoint) {
					throw logic_error("String can only contain one decimal point.");
				} else {
					hasDecPoint = true;
				}
			} else {
				throw logic_error("String contains a character that is not a digit or a decimal point.");
			}
		} else if (hasDecPoint && !oneAfterPoint) {
			oneAfterPoint = true;
		}
	}
	if (hasDecPoint && !oneAfterPoint) {
		throw logic_error("String must contain at least one digit after the decimal point if it is present.");
	}
	string builder;
	internal_to_word(str,builder);
	return builder;
}
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
}
string StringUtils::to_upper(string str) {
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}