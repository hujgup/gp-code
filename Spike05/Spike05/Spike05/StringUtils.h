#pragma once

#include <string>

// Provides extra methods for dealing with and manipulating strings
namespace StringUtils {
	// Determines if the given char is a whitespace character (ASCII range only)
	bool is_whitespace(const char& c);
	// Removes whitespace to the left of a string
	std::string trim_left(std::string str);
	// Removes whitespace to the right of a string
	std::string trim_right(std::string str);
	// Removes whitespace on both sides of a string
	std::string trim(std::string str);
}

