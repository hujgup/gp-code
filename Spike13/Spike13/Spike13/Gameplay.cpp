#include "Gameplay.h"
#include "MainMenu.h"
#include "HallOfFame.h"
#include "StringUtils.h"
#include "NumericUtils.h"
#include "WorldSwitchMessage.h"
#include "WorldReader.h"
#include "UpdateCurrentRoomMessage.h"
#include "UpdatePlayerMessage.h"

using namespace std;
using namespace placeholders;
using namespace StringUtils;
using namespace NumericUtils;

GameState* Gameplay::cmd_exit() {
	_firstEnter = true;
	IInventory::clear_references();
	Item::clear_references();
	return storage()->main_menu();
}
GameState* Gameplay::cmd_scores() {
	_firstEnter = true;
	return storage()->hall_of_fame();
}
GameState* Gameplay::cmd_view_inventory() {
	return storage()->inventory_view();
}
GameState* Gameplay::cmd_examine() {
	const Room& location = _world->room(_player.location_id());
	_output << "Your are in " << location.name() << "." << endl;
	_output << location.desc() << endl;
	_output << endl;
	_output << "From here, you can move to the following rooms:" << endl;
	for (World::Iterator i = _world->cbegin(); i != _world->cend(); ++i) {
		if (location != *i && _world->has_connection(location,*i)) {
			_output << "\t" << i->name() << " (" << i->id() << ")." << endl;
		}
	}
	vector<Item*> items = const_cast<Room&>(location).inventory().all_items(); // IDK why const_cast is necessary here (.inventory() is a const method) but w/e
	if (items.size() > 0) {
		_output << "This room contains the following items:" << endl;
		for (vector<Item*>::const_iterator i = items.cbegin(); i != items.cend(); ++i) {
			_output << "\t" << (*i)->name() << endl;
		}
	} else {
		_output << "This room contains no items." << endl;
	}
	return this;
}
GameState* Gameplay::cmd_go(const vector<string>& args) {
	try {
		unsigned long id = stoul(args[0]);
		unsigned long current = _player.location_id();
		if (id != current) {
			try {
				const Room& moveTo = _world->room(id);
				const Room& currentRoom = _world->room(current);
				if (_world->has_connection(currentRoom,moveTo)) {
					_player.location_id(id);
					storage()->dispatcher().dispatch(UpdateCurrentRoomMessage());
					_output << "You are now in " << moveTo.name() << "." << endl;
				} else {
					_output << "You cannot move to that room from your current location." << endl;
				}
			} catch (runtime_error) {
				_output << "You cannot move to that room from your current location." << endl;
			}
		} else {
			_output << "You are already in that room. Were you looking for the \"examine\" command?" << endl;
		}
	} catch (invalid_argument) {
		_output << "When using go, reference rooms by their I.D. numbers." << endl;
	}
	return this;
}
void Gameplay::add_commands() {
	storage()->dispatcher().dispatch(UpdatePlayerMessage(&_player));
	_firstEnter = true;
	_exit.set_command(bind(&Gameplay::cmd_exit,this));
	_scores.set_command(bind(&Gameplay::cmd_scores,this));
	_inventory.set_command(bind(&Gameplay::cmd_view_inventory,this));
	_examine.set_command(bind(&Gameplay::cmd_examine,this));
	_go.add_overload(1,bind(&Gameplay::cmd_go,this,_1));
	add_command("quit",_exit);
	add_command("hiscore",_scores);
	add_command("inv",_inventory);
	add_command("look",_examine);
	add_command("go",_go);
	load_aliases("gameplayAliases.txt");
	storage()->dispatcher()[WorldSwitchMessage()].event() += [this](MessageDispatcher& sender,Message& message) {
		message.read() >> _worldName;
		WorldReader reader;
		delete _world;
		_world = reader.read();
		storage()->dispatcher().dispatch(UpdateCurrentRoomMessage());
	};
}
Gameplay::Gameplay(ostream& output,istream& input,StateStorage* storage) : GameEnvironment(output,input,storage) {
	add_commands();
}
Gameplay::Gameplay(StateStorage* storage) : GameEnvironment(storage) {
	add_commands();
}
Gameplay::~Gameplay() {
	delete _world;
}
string Gameplay::type_name() const {
	return "Gameplay";
}
void Gameplay::on_enter() {
	if (_firstEnter) {
		_player.location_id(0);
		_player.inventory().clear(const_cast<Room&>(_world->room(0)));
		_output << "Welcome to Zorkish: " << _worldName << " World." << endl;
		_firstEnter = false;
	}
}
const World& Gameplay::world() const {
	return *_world;
}
Player& Gameplay::player() {
	return _player;
}
