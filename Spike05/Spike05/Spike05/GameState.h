#pragma once

#include <string>
#include <iostream>
#include <functional>

class StateStorage; // Forward declaration

// Represents a game state
class GameState {
public:
	typedef std::function<GameState*()> Command; // An executable command
private:
	StateStorage* _storage; // The StateStorage this instance belongs to
protected:
	std::ostream& _output; // The output stream to write to
	std::istream& _input; // The input stream to read from
	StateStorage* storage() const; // Gets the StateStorage this instance belongs to
public:
	static const std::string HORIZONTAL_RULE; // Prominent line break
	// Creates a new GameState
	// output = The output stream to write to
	// input = The input stream to read from
	// storage = The StateStorage this instance belongs to
	GameState(std::ostream& output, std::istream& input,StateStorage* storage);
	// Creates a new GameState
	// storage = The StateStorage this instance belongs to
	// Overload of the previous constructor, passing in std::cout and std::cin as arguments
	GameState(StateStorage* storage);
	// Required for inheritance, does nothing in this class
	virtual ~GameState();
	// This method is called when this GameState is entered from another GameState
	virtual void on_enter() = 0;
	// This method is called when the user inputs a command and this GameState is the active state
	// Should return this if the GameState should not change from the current one, or NULL if the game should exit; otherwise it should return a new GameState pointer
	virtual GameState* parse_command(std::string command) = 0;
	// This method returns an indicator giving the user details about what they are allowed to enter
	virtual std::string input_indicator() const;
};

// Stores and managers the various GameState instances
class StateStorage {
private:
	GameState* _mainMenu; // The main menu state
	GameState* _worldSelector; // The world selector state
	GameState* _hallOfFame; // The hall of fame state
	GameState* _credits; // The credits state
	GameState* _commandLister; // The command lister state
	GameState* _gameplay; // The gameplay state
public:
	// Creates a new StateStorage
	// output = The output stream to write to
	// input = The input stream to read from
	StateStorage(std::ostream& output,std::istream& input);
	// Creates a new GameState
	// Overload of the previous constructor, passing in std::cout and std::cin as arguments
	StateStorage();
	// Cleans up all the stored pointers
	~StateStorage();
	// Returns the quit game pointer
	GameState* quit() const;
	// Returns the main menu pointer
	GameState* main_menu() const;
	// Returns the world selector pointer
	GameState* world_selector() const;
	// Returns the hall of fame pointer
	GameState* hall_of_fame() const;
	// Returns the credits pointer
	GameState* credits() const;
	// Returns the command lister pointer
	GameState* command_lister() const;
	// Returns the gameplay pointer
	GameState* gameplay() const;
};