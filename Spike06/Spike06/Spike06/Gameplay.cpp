#include "Gameplay.h"
#include "MainMenu.h"
#include "HallOfFame.h"
#include "StringUtils.h"
#include "NumericUtils.h"

using namespace std;
using namespace StringUtils;
using namespace NumericUtils;

GameState* Gameplay::cmd_exit() {
	_firstEnter = true;
	return storage()->main_menu();
}
GameState* Gameplay::cmd_scores() {
	_firstEnter = true;
	return storage()->hall_of_fame();
}
GameState* Gameplay::cmd_view_inventory() {
	/*
	IInventory& inv = _player.inventory();
	unsigned int totalItems = inv.total_item_count();
	_output << "You have " << to_upper(to_word(totalItems)) << " (" << totalItems << ") item";
	if (totalItems != 1) {
		_output << "s";
	}
	_output << " in your inventory." << endl;
	const vector<Item> items = inv.all_items();
	unsigned int count;
	for (vector<Item>::const_iterator i = items.cbegin(); i != items.cend(); ++i) {
		count = inv.item_count(*i);
		_output << "\t" << to_upper(to_word(count)) << " (" << count << ") " << i->name() << endl;
	}
	return this;
	*/
	return storage()->inventory_view();
}
void Gameplay::add_commands() {
	_firstEnter = true;
	_exit.set_command(bind(&Gameplay::cmd_exit,this));
	_scores.set_command(bind(&Gameplay::cmd_scores,this));
	_inventory.set_command(bind(&Gameplay::cmd_view_inventory,this));
	add_command("quit",_exit);
	add_command("hiscore",_scores);
	add_command("inventory",_inventory);
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
	if (_firstEnter) {
		_player.inventory().clear();
		_output << "Welcome to Zorkish: " << _worldName << " World." << endl;
		_firstEnter = false;
	}
}
string Gameplay::world_name() const {
	return _worldName;
}
void Gameplay::world_name(string value) {
	_worldName = value;
}
Player& Gameplay::player() {
	return _player;
}
