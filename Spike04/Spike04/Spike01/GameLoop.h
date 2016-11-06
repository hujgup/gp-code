#pragma once

#include <map>
#include <string>
#include <functional>
#include "GameState.h"

class GameLoop {
public:
	typedef std::function<bool(std::ostream&,GameState&)> Command;
private:
	std::map<std::string,Command> _cmds;
	Command _outputFunc;
	GameState* _state;
	Grid* _grid;
	bool* _keepAlive;
	bool* _updateMap;
	int _threads;
	std::ostream* _output;
	std::istream* _input;
	void destroy_keep_alive();
protected:
	virtual GameState* create_state_actual(Grid* g,unsigned int startX,unsigned int startY);
public:
	GameLoop(Command outputFunc,unsigned int width,unsigned int height);
	virtual ~GameLoop();
	GameState& state() const;
	void create_game_state(unsigned int startX,unsigned int startY);
	bool add_command(std::string id,Command cmd);
	void operator ()(std::ostream& output,std::istream& input);
	friend void input_loop(GameLoop& loop);
};
