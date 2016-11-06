#pragma once

#include <vector>
#include <tuple>
#include "GameState.h"

// Represents a menu screen
class GameMenu : public GameState {
protected:
	typedef std::vector<std::tuple<std::string, Command>> OptionList; // A list of menu options and the executables that should run when they are selected
private:
	const std::string _text; // The text describing the menu
	OptionList _options; // The list of menu options
protected:
	// Adds an option to the menu
	// text = A string describing the option
	// cmd = The executable that should run when the option is chosen
	void add_option(std::string text, Command cmd);
public:
	// Creates a new GameMenu
	// output = The output stream to write to
	// input = The input stream to read from
	// text = The text describing the menu
	// storage = The StateStorage this instance belongs to
	GameMenu(std::ostream& output, std::istream& input,const std::string text,StateStorage* storage);
	// Creates a new GameMenu
	// output = The output stream to write to
	// input = The input stream to read from
	// storage = The StateStorage this instance belongs to
	GameMenu(std::ostream& output, std::istream& input,StateStorage* storage);
	// Creates a new GameMenu
	// text = The text describing the menu
	// storage = The StateStorage this instance belongs to
	GameMenu(const std::string text,StateStorage* storage);
	// Creates a new GameMenu
	// storage = The StateStorage this instance belongs to
	GameMenu(StateStorage* storage);
	// Required for inheritance, does nothing in this class
	virtual ~GameMenu();
	// Indicates the range of available options to the player
	virtual std::string input_indicator() const override final;
	// Displays the menu options
	virtual void on_enter() override final;
	// Allows users to select menu options
	virtual GameState* parse_command(std::string command) override final;
};
