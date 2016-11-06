#include "InventoryView.h"
#include "NumericUtils.h"
#include "StringUtils.h"

using namespace std;
using namespace placeholders;

string InventoryView::format_number(unsigned int n) const {
	string res = StringUtils::to_upper(NumericUtils::to_word(n));
	res += " (";
	res += to_string(n);
	res += ")";
	return res;
}
GameState* InventoryView::cmd_add(const vector<string>& args) {
	Item item(args[0]);
	_inv.add_item(item);
	_output << "Added item \"" << args[0] << "\" to inventory." << endl;
	_output << "You now have " << format_number(_inv.item_count(item)) << " lot(s) of said item in your inventory." << endl;
	return this;
}
GameState* InventoryView::cmd_remove(const vector<string>& args) {
	Item item(args[0]);
	bool success = _inv.remove_item(item);
	if (success) {
		_output << "Removed item \"" << args[0] << "\" from inventory." << endl;
		_output << "You now have " << format_number(_inv.item_count(item)) << " lot(s) of said item in your inventory." << endl;
	} else {
		_output << "You cannot remove item \"" << args[0] << "\" from inventory: you already have none of that item." << endl;
	}
	return this;
}
GameState* InventoryView::cmd_remove_all(const vector<string>& args) {
	Item item(args[0]);
	_inv.remove_item(item,_inv.item_count(item));
	_output << "Remove all of item \"" << args[0] << "\" from inventory." << endl;
	_output << "You now have " << format_number(_inv.item_count(item)) << " lot(s) of said item in your inventory." << endl;
	return this;
}
GameState* InventoryView::cmd_count(const vector<string>& args) {
	Item item(args[0]);
	_output << "You have " << format_number(_inv.item_count(item)) << " lot(s) of \"" << args[0] << "\" in your inventory." << endl;
	return this;
}
GameState* InventoryView::cmd_count_all(const vector<string>& args) {
	_output << "You have " << format_number(_inv.total_item_count()) << " item(s) in your inventory." << endl;
	return this;
}
GameState* InventoryView::cmd_list() {
	const vector<Item> items = _inv.all_items();
	if (items.size() == 0) {
		_output << "Your inventory is empty." << endl;
	} else {
		_output << "Your inventory contains the following items:" << endl;
		for (vector<Item>::const_iterator i = items.cbegin(); i != items.cend(); ++i) {
			_output << "\t" << format_number(_inv.item_count(*i)) << " " << i->name() << "." << endl;
		}
	}
	return this;
}
GameState* InventoryView::cmd_clear() {
	_inv.clear();
	_output << "Cleared inventory of all items." << endl;
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
	_list.set_command(bind(&InventoryView::cmd_list,this));
	_clear.set_command(bind(&InventoryView::cmd_clear,this));
	_back.set_command(bind(&InventoryView::cmd_back,this));

	add_command("add",_add);
	add_command("remove",_remove);
	add_command("removeall",_removeAll);
	add_command("count",_count);
	add_command("list",_list);
	add_command("clear",_clear);
	add_command("back",_back);
}
InventoryView::InventoryView(ostream& output,istream& input,StateStorage* storage,IInventory& inv) : GameEnvironment(output,input,storage), _inv(inv) {
	add_commands();
}
InventoryView::InventoryView(StateStorage* storage,IInventory& inv) : GameEnvironment(storage), _inv(inv) {
	add_commands();
}
InventoryView::~InventoryView() {
}
void InventoryView::on_enter() {
	_output << "Your inventory." << endl;
	_output << endl;
	_output << "Use add(1) to add an item, remove(1) to remove an item, removeall(1) to remove all of an item, count(0) to count the number of items, count(1) to count the number of a specific item, list(0) to list all items and quantities, and back(0) to return to gameplay." << endl;
}

