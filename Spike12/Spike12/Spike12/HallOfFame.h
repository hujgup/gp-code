#pragma once

#include "GameSplash.h"
#include "MainMenu.h"

// Represents the highscore screen
class HallOfFame : public GameSplash {
protected:
	// Outputs the current high scores
	virtual void output_content() const override;
	// Progresses to the main menu
	virtual GameState* next_state() const override;
public:
	// Creates a new HallOfFame
	// output = The output stream to write to
	// input = The input stream to read from
	// storage = The StateStorage this instance belongs to
	HallOfFame(std::ostream& output,std::istream& input,StateStorage* storage);
	// Creates a new HallOfFame
	// storage = The StateStorage this instance belongs to
	HallOfFame(StateStorage* storage);
	// Required for inheritance, does nothing in this class
	virtual ~HallOfFame();
	virtual std::string type_name() const override;
};