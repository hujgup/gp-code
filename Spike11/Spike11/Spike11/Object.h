#pragma once

#include <string>

struct Object {
	virtual ~Object();
	virtual std::string type_name() const = 0;
	virtual std::string to_string() const;
	// Guards against having to specify std::to_string when that's what needs to be called
	std::string to_string(int value) const;
	std::string to_string(unsigned int value) const;
	std::string to_string(long value) const;
	std::string to_string(unsigned long value) const;
	std::string to_string(long long value) const;
	std::string to_string(unsigned long long value) const;
	std::string to_string(float value) const;
	std::string to_string(double value) const;
	std::string to_string(long double value) const;
};