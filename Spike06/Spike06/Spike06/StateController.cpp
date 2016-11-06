#include "StateController.h"
#include "StringUtils.h"

using namespace std;
using namespace StringUtils;

StateController::StateController(ostream& output, istream& input) : _output(output), _input(input) {
}
StateController::StateController() : StateController(cout,cin) {
}
void StateController::operator ()() {
	_currentState = _storage.main_menu();
	_currentState->on_enter();
	bool keepAlive = true;
	string indicator;
	string command;
	GameState* newState;
	do {
		_output << endl;
		indicator = _currentState->input_indicator();
		if (indicator != "") {
			_output << indicator << " ";
		}
		getline(_input,command);
		command = trim(command);
		if (command != "") {
			_output << endl;
		}
		newState = _currentState->parse_command(command);
		if (newState != _currentState) {
			_currentState = newState;
			keepAlive = _currentState != _storage.quit();
			if (keepAlive) {
				_currentState->on_enter();
			}
		}
	} while (keepAlive);
}
