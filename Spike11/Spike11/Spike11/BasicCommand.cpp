#include "BasicCommand.h"

using namespace std;
using namespace placeholders;

GameState* BasicCommand::wrapper(const vector<string>& args) {
	return _cmd();
}
BasicCommand::BasicCommand(GameState::PureCommand cmd) : Command() {
	set_command(cmd);
}
BasicCommand::BasicCommand() : Command() {
}
BasicCommand::~BasicCommand() {
}
string BasicCommand::type_name() const {
	return "BasicCommand";
}
void BasicCommand::set_command(GameState::PureCommand cmd) {
	_cmd = cmd;
	add_overload(0,bind(&BasicCommand::wrapper,this,_1));
}
