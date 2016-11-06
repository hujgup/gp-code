#include "InventoryView.h"
#include <set>
#include "NumericUtils.h"
#include "StringUtils.h"
#include "UpdateCurrentRoomMessage.h"
#include "UpdatePlayerMessage.h"
#include "Gameplay.h"

using namespace std;
using namespace placeholders;

string InventoryView::format_number(unsigned int n) const {
	string res = StringUtils::to_upper(NumericUtils::to_word(n));
	res += " (";
	res += to_string(n);
	res += ")";
	return res;
}
bool InventoryView::room_valid() const {
	bool res = _room != NULL;
	if (!res) {
		_output << "MESSAGING ERROR: _room is NULL." << endl;
	}
	return res;
}
void InventoryView::list_actual(const vector<Item*>& items,IInventory& container,string empty,string contains) {
	if (items.size() == 0) {
		_output << empty << endl;
	} else {
		_output << contains << endl;
		set<string> seen;
		for (vector<Item*>::const_iterator i = items.cbegin(); i != items.cend(); ++i) {
			Item* item = *i;
			if (seen.find(item->name()) == seen.end()) {
				_output << "\t" << format_number(container.item_count(item->name())) << " " << item->name();
				stringstream s;
				BinaryWriter w(s);
				item->exec(w);
				BinaryReader r(s);
				while (!r.at_eof()) {
					unsigned long id;
					r >> id;
					if (id == HealthComponent::id) {
						unsigned long hp;
						r >> hp;
						_output << " (" << hp << " HP)";
					} else if (id == DamageComponent::id) {
						unsigned long dmg;
						r >> dmg;
						_output << " (" << dmg << " DMG)";
					}
				}
				_output << "." << endl;
				seen.insert(item->name());
			}
		}
	}
}
GameState* InventoryView::cmd_add(const vector<string>& args) {
	if (room_valid()) {
		try {
			Item& item = Item::get(Item::get_id_by_name(args[0]),*_room);
			stringstream s;
			BinaryWriter w(s);
			item.exec(w);
			BinaryReader r(s);
			bool success = false;
			while (!r.at_eof()) {
				unsigned long id;
				r >> id;
				if (id == ItemComponent::id) {
					success = true;
					break;
				}
			}
			if (success) {
				bool success = _room->inventory().move_item(item,*_invContainer);
				if (success) {
					_output << "Added item \"" << args[0] << "\" to inventory." << endl;
					_output << "You now have " << format_number(_invContainer->inventory().item_count(args[0])) << " lot(s) of said item in your inventory." << endl;
				} else {
					_output << "You cannot pick up item \"" << args[0] << "\" because that item is not in this room or does not exist." << endl;
				}
			} else {
				_output << "Cannot pick up that object." << endl;
			}
		} catch (range_error) {
			_output << "You cannot pick up item \"" << args[0] << "\" because that item does not exist." << endl;
		} catch (runtime_error) {
			_output << "You cannot pick up item \"" << args[0] << "\" because that item is not in this room." << endl;
		}
	}
	return this;
}
GameState* InventoryView::cmd_remove(const vector<string>& args) {
	if (room_valid()) {
		try {
			bool success = _invContainer->inventory().move_item(args[0], *_room);
		//	Item& item = Item::get(Item::get_id_by_name(args[0]));
			//bool success = _inv.remove_item(item,*_room);
			if (success) {
				_output << "Removed item \"" << args[0] << "\" from inventory." << endl;
				_output << "You now have " << format_number(_invContainer->inventory().item_count(args[0])) << " lot(s) of said item in your inventory." << endl;
			} else {
				_output << "You cannot remove item \"" << args[0] << "\" from inventory: you already have none of that item." << endl;
			}
		} catch (runtime_error e) {
			_output << e.what() << endl;
		}
	}
	return this;
}
GameState* InventoryView::cmd_remove_all(const vector<string>& args) {
	if (room_valid()) {
		try {
			_invContainer->inventory().move_items(args[0], *_room, _invContainer->inventory().item_count(args[0]));
//			Item& item = Item::get(Item::get_id_by_name(args[0]));
	//		_inv.remove_item(item,*_room,_inv.item_count(item));
			_output << "Remove all of item \"" << args[0] << "\" from inventory." << endl;
			_output << "You now have " << format_number(_invContainer->inventory().item_count(args[0])) << " lot(s) of said item in your inventory." << endl;
		} catch (runtime_error e) {
			_output << e.what() << endl;
		}
	}
	return this;
}
GameState* InventoryView::cmd_count(const vector<string>& args) {
	try {
		_output << "You have " << format_number(_invContainer->inventory().item_count(args[0])) << " lot(s) of \"" << args[0] << "\" in your inventory." << endl;
	} catch (runtime_error e) {
		_output << e.what() << endl;
	}
	return this;
}
GameState* InventoryView::cmd_count_all(const vector<string>& args) {
	_output << "You have " << format_number(_invContainer->inventory().total_item_count()) << " item(s) in your inventory." << endl;
	return this;
}
/*
GameState* cmd_look_in(const std::vector<std::string>& args);
GameState* cmd_take_from(const std::vector<std::string>& args);
GameState* cmd_put_in(const std::vector<std::string>& args);
*/
GameState* InventoryView::cmd_look_in(const vector<string>& args) {
	try {
		Item& item = Item::get(Item::get_id_by_name(args[0]),*_invContainer);
		const vector<Item*> items = item.inventory().all_items();
		list_actual(items,item.inventory(),args[0] + " is empty.",args[0] + " contains the following items:");
	} catch (range_error) {
		_output << "Cannot look inside that item because that item does not exist." << endl;
	} catch (runtime_error) {
		_output << "Cannot look inside that item because you're not currently holding that item." << endl;
	}
	return this;
}
GameState* InventoryView::cmd_take_from(const vector<string>& args) {
	try {
		Item& container = Item::get(Item::get_id_by_name(args[1]),*_invContainer);
		try {
			Item& item = Item::get(Item::get_id_by_name(args[0]),container);
			item.inventory().move_item(item,*_invContainer);
			_output << args[0] << " has been taken from " << args[1] << "." << endl;
		} catch (range_error) {
			_output << "Cannot take that item from a container because that item does not exist." << endl;
		} catch (runtime_error) {
			_output << "Cannot take that item from a container because that container does not contain that item." << endl;
		}
	} catch (range_error) {
		_output << "Cannot take that item from a container because that container does not exist." << endl;
	} catch (runtime_error) {
		_output << "Cannot take that item from a container because you're not currently holding that container." << endl;
	}
	return this;
}
GameState* InventoryView::cmd_put_in(const vector<string>& args) {
	try {
		Item& container = Item::get(Item::get_id_by_name(args[1]),*_invContainer);
		try {
			Item& item = Item::get(Item::get_id_by_name(args[0]),*_invContainer);
			_invContainer->inventory().move_item(item,container);
			_output << args[0] << " is now inside " << args[1] << "." << endl;
		} catch (range_error) {
			_output << "Cannot put that item in that a container because that item does not exist." << endl;
		} catch (runtime_error) {
			_output << "Cannot put that item in that a container because you're not currently holding that item." << endl;
		}
	} catch (range_error) {
		_output << "Cannot put that item in that a container because that container does not exist." << endl;
	} catch (runtime_error) {
		_output << "Cannot put that item in that a container because you're not currently holding that container." << endl;
	}
	return this;
}
GameState* InventoryView::cmd_clear(const vector<string>& args) {
	if (room_valid()) {
		_invContainer->inventory().clear(*_room);
		_output << "Cleared inventory of all items." << endl;
	}
	return this;
}
GameState* InventoryView::cmd_clear_item(const vector<string>& args) {
	try {
		Item& item = Item::get(Item::get_id_by_name(args[0]),*_invContainer);
		item.inventory().clear(*_invContainer);
		_output << "Cleared out contents of " << args[0] << "." << endl;
	} catch (range_error) {
		_output << "Cannot clear out that item because that item does not exist." << endl;
	} catch (runtime_error) {
		_output << "Cannot clear out that item because you're not currently holding that item." << endl;
	}
	return this;
}
GameState* InventoryView::cmd_list() {
	const vector<Item*> items = _invContainer->inventory().all_items();
	list_actual(items,_invContainer->inventory(),"Your inventory is empty.","Your inventory contains the following items:");
	return this;
}
GameState* InventoryView::cmd_back() {
	_output << "Exiting inventory..." << endl;
	return storage()->gameplay();
}
void InventoryView::add_commands() {
	_add.add_overload(1,bind(&InventoryView::cmd_add,this,_1));
	_remove.add_overload(1,bind(&InventoryView::cmd_remove,this,_1));
	_removeAll.add_overload(1,bind(&InventoryView::cmd_remove_all,this,_1));
	_count.add_overload(0,bind(&InventoryView::cmd_count_all,this,_1));
	_count.add_overload(1,bind(&InventoryView::cmd_count,this,_1));
	_lookIn.add_overload(1,bind(&InventoryView::cmd_look_in,this,_1));
	_takeFrom.add_overload(2,bind(&InventoryView::cmd_take_from,this,_1));
	_putIn.add_overload(2,bind(&InventoryView::cmd_put_in,this,_1));
	_clear.add_overload(0,bind(&InventoryView::cmd_clear,this,_1));
	_clear.add_overload(1,bind(&InventoryView::cmd_clear_item,this,_1));
	_list.set_command(bind(&InventoryView::cmd_list,this));
	_back.set_command(bind(&InventoryView::cmd_back,this));

	add_command("add",_add);
	add_command("rm",_remove);
	add_command("rmall",_removeAll);
	add_command("count",_count);
	add_command("lookIn",_lookIn);
	add_command("takeFrom",_takeFrom);
	add_command("putIn",_putIn);
	add_command("list",_list);
	add_command("clear",_clear);
	add_command("back",_back);
	load_aliases("inventoryAliases.txt");

	storage()->dispatcher()[UpdateCurrentRoomMessage()].event() += [this](MessageDispatcher& sender,Message& message) {
		Gameplay* g = (Gameplay*)storage()->gameplay();
		_room = const_cast<Room*>(&(g->world().room(g->player().location_id())));
	};
	storage()->dispatcher()[UpdatePlayerMessage()].event() += [this](MessageDispatcher& sender,Message& message) {
		void* ptr;
		message.read() >> ptr;
		_invContainer = (IHasInventory*)ptr;
	};
}
InventoryView::InventoryView(ostream& output,istream& input,StateStorage* storage) : GameEnvironment(output,input,storage) {
	add_commands();
}
InventoryView::InventoryView(StateStorage* storage) : GameEnvironment(storage) {
	add_commands();
}
InventoryView::~InventoryView() {
}
string InventoryView::type_name() const {
	return "InventoryView";
}
void InventoryView::on_enter() {
	_output << "Your inventory." << endl;
	_output << endl;
	_output << "Use add(1) to add an item, remove(1) to remove an item, removeall(1) to remove all of an item, count(0) to count the number of items, count(1) to count the number of a specific item, list(0) to list all items and quantities, and back(0) to return to gameplay." << endl;
}

