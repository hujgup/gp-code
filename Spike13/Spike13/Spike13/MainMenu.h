#pragma once

#include "GameMenu.h"

// The main menu of the game, displays immediately on startup
class MainMenu : public GameMenu {
private:
	static const std::string _DISPLAY_TEXT; // The text describing this menu
	// The executable command that lets users select the gameplay world they want to go to
	GameState* cmd_select();
	// The executable command that displays the hall of fame
	GameState* cmd_scores();
	// The executable command that prints all the commands available during gameplay
	GameState* cmd_help();
	// The executable command that provides details about the creator of the game
	GameState* cmd_about();
	// The executable command the quits the game
	GameState* cmd_quit();
	// Constructor helper method: Adds all the options to the menu
	void create_options();
public:
	// Creates a new MainMenu
	// output = The output stream to write to
	// input = The input stream to read from
	// storage = The StateStorage this instance belongs to
	MainMenu(std::ostream& output, std::istream& input,StateStorage* storage);
	// Creates a new MainMenu
	// storage = The StateStorage this instance belongs to
	MainMenu(StateStorage* storage);
	// Required for inheritance, does nothing in this class
	virtual ~MainMenu();
	virtual std::string type_name() const override;
};