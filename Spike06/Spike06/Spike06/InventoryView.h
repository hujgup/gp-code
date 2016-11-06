#pragma once

#include "GameEnvironment.h"
#include "IInventory.h"
#include "BasicCommand.h"

class InventoryView : public GameEnvironment {
	/*
	add
	remove
	count
	back
	*/
private:
	IInventory& _inv;
	Command _add;
	Command _remove;
	Command _removeAll;
	Command _count;
	BasicCommand _list;
	BasicCommand _clear;
	BasicCommand _back;
	std::string format_number(unsigned int n) const;
	GameState* cmd_add(const std::vector<std::string>& args);
	GameState* cmd_remove(const std::vector<std::string>& args);
	GameState* cmd_remove_all(const std::vector<std::string>& args);
	GameState* cmd_count(const std::vector<std::string>& args);
	GameState* cmd_count_all(const std::vector<std::string>& args);
	GameState* cmd_list();
	GameState* cmd_clear();
	GameState* cmd_back();
	void add_commands();
public:
	InventoryView(std::ostream& output,std::istream& input,StateStorage* storage,IInventory& inv);
	InventoryView(StateStorage* storage,IInventory& inv);
	virtual ~InventoryView();
	virtual void on_enter() override;
};

