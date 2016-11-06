#pragma once

#include "GameMenu.h"
#include "WorldReader.h"

// The menu that allows users to select the world they wish to go to
class WorldSelector : public GameMenu {
private:
	static const std::string _DISPLAY_TEXT; // The text describing this menu
	WorldReader _reader;
	// The executable command that sends the player to the mountain world
	GameState* cmd_mountain();
	// The executable command that sends the player to the water world
	GameState* cmd_water();
	// The executable command that sends the player to the box world
	GameState* cmd_box();
	// Constructor helper method: Adds all the options to the menu
	void create_options();
public:
	// Creates a new WorldSelector
	// output = The output stream to write to
	// input = The input stream to read from
	// storage = The StateStorage this instance belongs to
	WorldSelector(std::ostream& output,std::istream& input,StateStorage* storage);
	// Creates a new WorldSelector
	// storage = The StateStorage this instance belongs to
	WorldSelector(StateStorage* storage);
	// Required for inheritance, does nothing in this class
	virtual ~WorldSelector();
};



