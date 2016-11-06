#include "GameSplash.h"

using namespace std;

GameSplash::GameSplash(ostream& output,istream& input,StateStorage* storage) : GameState(output,input,storage) {
}
GameSplash::GameSplash(StateStorage* storage) : GameState(storage) {
}
GameSplash::~GameSplash() {
}
void GameSplash::on_enter() {
	output_content();
	_output << endl;
	_output << "Press [ENTER] to continue.";
}
GameState* GameSplash::parse_command(string command) {
	return next_state();
}
string GameSplash::input_indicator() const {
	return "";
}