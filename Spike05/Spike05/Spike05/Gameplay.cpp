#include "Gameplay.h"
#include "MainMenu.h"
#include "HallOfFame.h"

using namespace std;

GameState* Gameplay::cmd_exit() {
	return storage()->main_menu();
}
GameState* Gameplay::cmd_scores() {
	return storage()->hall_of_fame();
}
void Gameplay::add_commands() {
	add_command("quit",bind(&Gameplay::cmd_exit,this));
	add_command("hiscore",bind(&Gameplay::cmd_scores,this));
}
Gameplay::Gameplay(ostream& output,istream& input,StateStorage* storage) : GameEnvironment(output,input,storage) {
	add_commands();
}
Gameplay::Gameplay(StateStorage* storage) : GameEnvironment(storage) {
	add_commands();
}
Gameplay::~Gameplay() {
}
void Gameplay::on_enter() {
	_output << "Welcome to Zorkish: " << _worldName << " World." << endl;
}
string Gameplay::world_name() const {
	return _worldName;
}
void Gameplay::world_name(string value) {
	_worldName = value;
}