#include "Command.h"

using namespace std;

Command::Command() {
}
Command::~Command() {
}
string Command::type_name() const {
	return "Command";
}
bool Command::add_overload(unsigned int argCount,CommandDelegate cmd) {
	bool res = _overloads.count(argCount) == 0;
	if (res) {
		_overloads.insert(make_pair(argCount,cmd));
	}
	return res;
}
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