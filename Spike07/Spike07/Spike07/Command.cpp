#include "Command.h"

using namespace std;


Command::Command() {
}
Command::~Command() {
}
bool Command::add_overload(unsigned int argCount,CommandDelegate cmd) {
	bool res = _overloads.count(argCount) == 0;
	if (res) {
		_overloads.insert(make_pair(argCount,cmd));
	}
	return res;
}
/*
CommandResult Command::parse(string command) {
	vector<string> args = split(command);
	unsigned int length = args.size();
	bool valid = length != 0;
	SuccessState success;
	GameState* state;
	if (valid) {
		valid = args[0] == _id;
		if (valid) {
			valid = _overloads.count(--length) != 0;
			if (valid) {
				args.erase(args.begin());
				state = _overloads[length](args);
				success = SuccessState::Success;
			} else {
				success = SuccessState::NoValidOverload;
			}
		} else {
			success = SuccessState::IncorrectId;
		}
	} else {
		success = SuccessState::EmptyCommand;
	}
	return CommandResult(success,state);
}
*/
CommandResult Command::operator ()(const vector<string>& args) {
	unsigned int length = args.size();
	GameState* state = NULL;
	SuccessState success;
	if (_overloads.count(length) != 0) {
		success = SuccessState::Success;
		state = _overloads[length](args);
	} else {
		success = SuccessState::NoValidOverload;
	}
	return CommandResult(success,state);
}