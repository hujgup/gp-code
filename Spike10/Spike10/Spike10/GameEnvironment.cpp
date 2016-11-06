#include "GameEnvironment.h"
#include <regex>
#include <vector>
#include <algorithm>
#include "StringUtils.h"
#include "CommandReader.h"

using namespace std;
using namespace StringUtils;

bool GameEnvironment::contains(const string& id) const {
	return _commands.find(id) != _commands.cend();
}
bool GameEnvironment::contains_alias(const string& alias) const {
	return _aliases.count(alias) != 0;
}
vector<string> GameEnvironment::create_args(string command,const string& aRegex) {
	vector<string> res;
	{
		smatch match;
		if (regex_search(command,match,regex(aRegex)) && match.size() > 1) {
			for (size_t i = 1; i < match.size(); ++i) {
				string str = match.str(i);
				if (starts_with(str,'\"')) {
					str = str.substr(1,str.length() - 2);
				}
				res.push_back(str);
			}
		}
	}
	command = regex_replace(command,regex(aRegex),"");
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
				res.push_back(current);
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
		res.push_back(current);
	}
	return res;
}
bool GameEnvironment::add_alias(string id,string regex) {
	bool res = !contains_alias(regex) && contains(id);
	if (res) {
		_aliases[regex] = id;
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
void GameEnvironment::load_aliases(string file) {
	CommandReader reader;
	set<string> ids;
	for (InsertionOrderedMap<string,Command>::ConstIterator i = _commands.cbegin(); i != _commands.cend(); ++i) {
		ids.insert(i->first);
	}
	list<LineResult> regexes = reader.read(file,ids);
	for (list<LineResult>::const_iterator i = regexes.cbegin(); i != regexes.cend(); ++i) {
	//	_output  << type_name() << " :: " << i->id << " :: " << i->regex << endl;
		add_alias(i->id,i->regex);
	}
}
GameEnvironment::GameEnvironment(ostream& output,istream& input,StateStorage* storage) : GameState(output,input,storage) {
}
GameEnvironment::GameEnvironment(StateStorage* storage) : GameState(storage) {
}
GameEnvironment::~GameEnvironment() {
}
string GameEnvironment::type_name() const {
	return "GameEnvironment";
}
GameState* GameEnvironment::parse_command(string command) {
	GameState* res = this;
	bool found = false;
	smatch match;
	for (unordered_map<string,string>::const_iterator i = _aliases.cbegin(); i != _aliases.cend(); ++i) {
		//_output << i->first << " :: " << command << endl;
		if (regex_search(command,match,regex(i->first))) {
			found = true;
			vector<string> vArgs = create_args(command,i->first);
			//cout << command << endl;
			//cout << i->first << endl;
			//cout << i->second << "(" << vArgs.size() << ")" << endl;
			CommandResult cr = _commands[i->second](vArgs);
			if (cr.success() == SuccessState::Success) {
				res = cr.result();
			} else {
				_output << "Invalid command: No overload for that command accepts " << vArgs.size() << " arguments." << endl;
			}
			break;
		}
	}
	if (!found) {
		_output << "Invalid command: No command with structure \"" << command << "\" exists in the current context." << endl;
	}
	return res;

	/*
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
	*/
}
