#pragma once

#include "Command.h"

class BasicCommand : public Command {
private:
	GameState::PureCommand _cmd;
	GameState* wrapper(const std::vector<std::string>& args);
public:
	BasicCommand(GameState::PureCommand cmd);
	BasicCommand();
	virtual ~BasicCommand();
	void set_command(GameState::PureCommand cmd);
};