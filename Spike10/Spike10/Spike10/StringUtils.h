#pragma once

#include <string>

// Provides extra methods for dealing with and manipulating strings
namespace StringUtils {
	// Converts a single digit to its English representation
	std::string to_word(const char& c);
	// Converts a string of digits to its English representation
	std::string to_word(const std::string& str);
	// Determines if the given char is a whitespace character (ASCII range only)
	bool is_whitespace(const char& c);
	// Removes whitespace to the left of a string
	std::string trim_left(std::string str);
	// Removes whitespace to the right of a string
	std::string trim_right(std::string str);
	// Removes whitespace on both sides of a string
	std::string trim(std::string str);
	// Transforms a string to upper case
	std::string to_upper(std::string str);
	// Replaces a given substring with another given substring
	std::string substring_replace(const std::string& str,std::string from,std::string to);
	// Checks if a given string starts with a certain character
	bool starts_with(std::string str,char c);
}

