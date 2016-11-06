#include "CommandLister.h"
#include "MainMenu.h"

using namespace std;

void CommandLister::output_content() const {
	_output << "Zorkish :: Help" + GameState::HORIZONTAL_RULE << endl;
	_output << "The following commands are available during gameplay:" << endl;
	_output << "quit" << endl;
	_output << "inventory" << endl;
	_output << "-> add" << endl;
	_output << "-> remove" << endl;
	_output << "-> removeall" << endl;
	_output << "-> count" << endl;
	_output << "-> list" << endl;
	_output << "-> clear" << endl;
	_output << "-> back" << endl;
	_output << "examine" << endl;
	_output << "go" << endl;
	_output << "hiscore (for testing)" << endl;
}
GameState* CommandLister::next_state() const {
	return storage()->main_menu();
}
CommandLister::CommandLister(ostream& output,istream& input,StateStorage* storage) : GameSplash(output,input,storage) {
}
CommandLister::CommandLister(StateStorage* storage) : GameSplash(storage) {
}
CommandLister::~CommandLister() {
}