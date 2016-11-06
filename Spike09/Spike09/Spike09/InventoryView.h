#pragma once

#include "GameEnvironment.h"
#include "Inventory.h"
#include "BasicCommand.h"
#include "Room.h"

class InventoryView : public GameEnvironment {
private:
	IHasInventory* _invContainer;
	Room* _room;
	Command _add;
	Command _remove;
	Command _removeAll;
	Command _count;
	Command _lookIn;
	Command _takeFrom;
	Command _putIn;
	Command _clear;
	BasicCommand _list;
	BasicCommand _back;
	std::string format_number(unsigned int n) const;
	bool room_valid() const;
	void list_actual(const std::vector<Item*>& items,IInventory& container,std::string empty,std::string contains);
	GameState* cmd_add(const std::vector<std::string>& args);
	GameState* cmd_remove(const std::vector<std::string>& args);
	GameState* cmd_remove_all(const std::vector<std::string>& args);
	GameState* cmd_count(const std::vector<std::string>& args);
	GameState* cmd_count_all(const std::vector<std::string>& args);
	GameState* cmd_look_in(const std::vector<std::string>& args);
	GameState* cmd_take_from(const std::vector<std::string>& args);
	GameState* cmd_put_in(const std::vector<std::string>& args);
	GameState* cmd_clear(const std::vector<std::string>& args);
	GameState* cmd_clear_item(const std::vector<std::string>& args);
	GameState* cmd_list();
	GameState* cmd_back();
	void add_commands();
public:
	InventoryView(std::ostream& output,std::istream& input,StateStorage* storage);
	InventoryView(StateStorage* storage);
	virtual ~InventoryView();
	virtual std::string type_name() const override;
	virtual void on_enter() override;
};

