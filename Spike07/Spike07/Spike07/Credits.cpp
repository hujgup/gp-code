#include "Credits.h"
#include "MainMenu.h"

using namespace std;

void Credits::output_content() const {
	_output << "Zorkish :: About" + GameState::HORIZONTAL_RULE << endl;
	_output << "Written by: Jake Tunaley" << endl;
}
GameState* Credits::next_state() const {
	return storage()->main_menu();
}
Credits::Credits(ostream& output,istream& input,StateStorage* storage) : GameSplash(output,input,storage) {
}
Credits::Credits(StateStorage* storage) : GameSplash(storage) {
}
Credits::~Credits() {
}