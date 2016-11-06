#include "Spike1Loop.h"

// Creates this loop's game state
// g = The grid this GameLoop is using
// startX = The player's initial x position
// startY = The player's initial y position
GameState* Spike1Loop::create_state_actual(Grid* g,unsigned int startX,unsigned int startY) {
	return new Spike1State(g,startX,startY);
};
// Creates a new Spike1Loop
// outputFunc = The functor controlling the loop's output
// width = The width of the playspace
// height = The height of the playspace
Spike1Loop::Spike1Loop(Command outputFunc,unsigned int width,unsigned int height) : GameLoop(outputFunc,width,height) {
}
// Destroys this Spike1Loop
Spike1Loop::~Spike1Loop() {
}

