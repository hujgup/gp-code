#pragma once

#include "GameLoop.h"
#include "Spike1State.h"

class Spike1Loop : public GameLoop {
protected:
	virtual GameState* create_state_actual(Grid* g,unsigned int startX,unsigned int startY) override;
public:
	Spike1Loop(Command outputFunc,unsigned int width,unsigned int height);
	virtual ~Spike1Loop();
};

