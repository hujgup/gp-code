#pragma once

#include <vector>
#include <unordered_map>
#include "CommandResult.h"

class Command {
public:
	typedef std::function<GameState*(const std::vector<std::string>&)> CommandDelegate;
private:
	std::unordered_map<unsigned int,CommandDelegate> _overloads;
public:
	Command();
	virtual ~Command();
	bool add_overload(unsigned int argCount,CommandDelegate cmd);
	CommandResult operator ()(const std::vector<std::string>& args);
};
