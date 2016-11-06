#include "GameEnvironment.h"
#include <algorithm>
#include "StringUtils.h"

using namespace std;
using namespace StringUtils;

bool GameEnvironment::contains(const string& id) const {
	return _commands.count(id) != 0;
}
string GameEnvironment::split(const string& command) {
	_args.clear();
	string res;
	string current;
	char lastChar;
	char currentChar;
	bool inString = false;
	for (string::const_iterator i = command.cbegin(); i != command.cend(); ++i) {
		currentChar = *i;
		if (inString) {
			if (currentChar == '"' && lastChar != '\\') {
				inString = false;
			} else {
				current += currentChar;
			}
		} else if (is_whitespace(currentChar)) {
			if (current != "") {
				if (res != "") {
					_args.push_back(current);
				} else {
					res = current;
				}
				current.clear();
			}
		} else if (currentChar == '"' && lastChar == ' ') {
			inString = true;
		} else {
			current += currentChar;
		}
		lastChar = currentChar;
	}
	if (current != "") {
		if (res != "") {
			_args.push_back(current);
		} else {
			res = current;
		}
	}
	return res;
}
bool GameEnvironment::add_command(string id,Command cmd) {
	bool res = !contains(id);
	if (res) {
		_commands[id] = cmd;
	}
	return res;
}
GameEnvironment::GameEnvironment(ostream& output,istream& input,StateStorage* storage) : GameState(output,input,storage) {
}
GameEnvironment::GameEnvironment(StateStorage* storage) : GameState(storage) {
}
GameEnvironment::~GameEnvironment() {
}
GameState* GameEnvironment::parse_command(string command) {
	GameState* res = this;
	bool notFound = true;
	string id = split(command);
	if (contains(id)) {
		CommandResult cr = _commands[id](_args);
		if (cr.success() == SuccessState::Success) {
			res = cr.result();
		} else {
			_output << "Invalid command: No overload for command \"" << id << "\" accepts " << _args.size() << " arguments." << endl;
		}
	} else if (id == "") {
		_output << "Invalid command: String is empty." << endl;
	} else {
		_output << "Invalid command: No command with ID \"" << id << "\" exists in the current context." << endl;
	}
	return res;
	/*
	string id = split(command);
	bool valid = contains(id);
	GameState* res;
	if (valid) {
		res = _commands[id]();
	}
	else {
		_output << "Invalid command." << endl;
		res = this;
	}
	return res;
	*/
}
