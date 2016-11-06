#pragma once

#include <iostream>
#include <string>
#include "GameState.h"

class MovementCommand {
private:
	int _xMotion;
	int _yMotion;
public:
	MovementCommand(int xMotion,int yMotion);
	bool operator ()(std::ostream& output,GameState& state);
};
