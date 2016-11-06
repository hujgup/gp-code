#include "GameMenu.h"
#include <cstdlib>

using namespace std;

void GameMenu::add_option(string text,PureCommand cmd) {
	_options.push_back(std::tuple<string,PureCommand>(text,cmd));
}
GameMenu::GameMenu(ostream& output, istream& input, const string text,StateStorage* storage) : GameState(output,input,storage), _text(text) {
}
GameMenu::GameMenu(ostream& output, istream& input,StateStorage* storage) : GameState(output,input,storage) {
}
GameMenu::GameMenu(const string text,StateStorage* storage) : GameState(storage), _text(text) {
}
GameMenu::GameMenu(StateStorage* storage) : GameState(storage) {
}
GameMenu::~GameMenu() {
}
string GameMenu::input_indicator() const {
	return "Select 1-" + to_string(_options.size()) + GameState::input_indicator();
}
void GameMenu::on_enter() {
	_output << _text << endl << endl;
	int n = 1;
	for (OptionList::iterator i = _options.begin(); i != _options.end(); ++i,++n) {
		cout << n << ". " << get<0>(*i) << endl;
	}
}
GameState* GameMenu::parse_command(string command) {
	GameState* res;
	int n = atoi(command.c_str());
	if (n >= 1 && (unsigned int)n <= _options.size()) {
		res = get<1>(_options[n - 1])();
	}
	else {
		_output << "Not a valid option." << endl;
		res = this;
	}
	return res;
}