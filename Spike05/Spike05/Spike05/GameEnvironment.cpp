#include "GameEnvironment.h"

using namespace std;

bool GameEnvironment::contains(string command) const {
	return _commands.count(command) != 0;
}
bool GameEnvironment::add_command(string id, Command cmd) {
	bool res = !contains(id);
	if (res) {
		_commands.insert(std::make_pair(id, cmd));
	}
	return res;
}
GameEnvironment::GameEnvironment(ostream& output,istream& input,StateStorage* storage) : GameState(output,input,storage) {
}
GameEnvironment::GameEnvironment(StateStorage* storage) : GameState(storage) {
}
GameEnvironment::~GameEnvironment() {
}
GameState* GameEnvironment::parse_command(std::string command) {
	bool valid = contains(command);
	GameState* res;
	if (valid) {
		res = _commands[command]();
	}
	else {
		_output << "Invalid command." << endl;
		res = this;
	}
	return res;
}
