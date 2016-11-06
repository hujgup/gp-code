#include "GameState.h"
#include "MainMenu.h"
#include "WorldSelector.h"
#include "HallOfFame.h"
#include "Credits.h"
#include "CommandLister.h"
#include "Gameplay.h"
#include "InventoryView.h"
#include "WorldReader.h"

using namespace std;

const string GameState::HORIZONTAL_RULE = "\n--------------------------------------------------------\n";

StateStorage* GameState::storage() const {
	return _storage;
}
GameState::GameState(ostream& output,istream& input,StateStorage* storage) : _output(output), _input(input), _storage(storage) {
}
GameState::GameState(StateStorage* storage) : GameState(cout,cin,storage) {
}
GameState::~GameState() {
}
string GameState::input_indicator() const {
	return ":>";
}

StateStorage::StateStorage(ostream& output,istream& input) {
	_mainMenu = new MainMenu(output,input,this);
	_worldSelector = new WorldSelector(output,input,this);
	_hallOfFame = new HallOfFame(output,input,this);
	_credits = new Credits(output,input,this);
	_commandLister = new CommandLister(output,input,this);
	_gameplay = new Gameplay(output,input,this);
	_inventoryView = new InventoryView(output,input,this,((Gameplay*)_gameplay)->player().inventory());
}
StateStorage::StateStorage() : StateStorage(cout,cin) {
}
StateStorage::~StateStorage() {
	delete _mainMenu;
	delete _worldSelector;
	delete _hallOfFame;
	delete _credits;
	delete _commandLister;
	delete _gameplay;
	delete _inventoryView;
}
GameState* StateStorage::quit() const {
	return NULL;
}
GameState* StateStorage::main_menu() const {
	return _mainMenu;
}
GameState* StateStorage::world_selector() const {
	return _worldSelector;
}
GameState* StateStorage::hall_of_fame() const {
	return _hallOfFame;
}
GameState* StateStorage::credits() const {
	return _credits;
}
GameState* StateStorage::command_lister() const {
	return _commandLister;
}
GameState* StateStorage::gameplay() const {
	return _gameplay;
}
GameState* StateStorage::inventory_view() const {
	return _inventoryView;
}
/*
GameState* StateStorage::x() const {
return _x;
}
*/