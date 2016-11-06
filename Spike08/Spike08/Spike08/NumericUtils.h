#pragma once

#include <string>

namespace NumericUtils {
	std::string to_word(char n);
	std::string to_word(unsigned char n);
	std::string to_word(short n);
	std::string to_word(unsigned short n);
	std::string to_word(int n);
	std::string to_word(unsigned int n);
	std::string to_word(long n);
	std::string to_word(unsigned long n);
	std::string to_word(long long n);
	std::string to_word(unsigned long long n);
	std::string to_word(float n);
	std::string to_word(double n);
	std::string to_word(long double n);
}