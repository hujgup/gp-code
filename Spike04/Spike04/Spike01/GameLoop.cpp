#include "GameLoop.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

// Destroys the _keepAlive pointer if the number of threads reaches 0
void GameLoop::destroy_keep_alive() {
	if (--_threads <= 0) {
		delete _keepAlive;
		delete _updateMap;
	}
}

// Creates this loop's game state
// g = The grid this GameLoop is using
// startX = The player's initial x position
// startY = The player's initial y position
GameState* GameLoop::create_state_actual(Grid* g,unsigned int startX,unsigned int startY) {
	return new GameState(g,startX,startY);
}
// Creates a new GameLoop
// outputFunc = The functor controlling the loop's output
// width = The width of the playspace
// height = The height of the playspace
GameLoop::GameLoop(Command outputFunc,unsigned int width,unsigned int height) {
	_grid = new Grid(width,height);
	_outputFunc = outputFunc;
}
// Destroys this GameLoop
GameLoop::~GameLoop() {
	delete _state;
}
// Gets the current game state
GameState& GameLoop::state() const {
	return *_state;
}
// Creates this loop's game state
// This method should only be called once, immediately after object construction (workaround for how method overloading works when called from the constructor)
// startX = The player's initial x position
// startY = The player's initial y position
void GameLoop::create_game_state(unsigned int startX,unsigned int startY) {
	if (_state != NULL) {
		throw logic_error("Cannot call this method twice.");
	}
	_state = create_state_actual(_grid,startX,startY);
};
// Adds a command to this loop
// id = The unique string identifying the command
// cmd = The functor that contains the code the command should execute
bool GameLoop::add_command(string id,Command cmd) {
	bool res = _cmds.count(id) == 0;
	if (res) {
		_cmds.insert(make_pair(id,cmd));
	}
	return res;
}
// Runs the loop
// output = The output stream to write to
// input = The input stream to read from
void GameLoop::operator ()(ostream& output, istream& input) {
	_updateMap = new bool(true);
	_threads = 1;
	_output = &output;
	_input = &input;
	_keepAlive = new bool(true);
	typedef chrono::time_point<chrono::steady_clock> TimePoint;
	typedef chrono::high_resolution_clock Clock;
	TimePoint start = Clock::now();
	thread inputThread(&input_loop,*this);
	inputThread.detach();
	string inputStr;
	long long milliseconds;
	do {
		milliseconds = chrono::duration_cast<chrono::milliseconds>(Clock::now() - start).count();
		if (milliseconds >= 16 && *_updateMap) {
			*_keepAlive = !_outputFunc(output, *_state);
			start = Clock::now();
			*_updateMap = false;
		}
	} while (*_keepAlive);
	destroy_keep_alive();
}

void input_loop(GameLoop& loop) {
	++(loop._threads);
	typedef map<string, GameLoop::Command>::iterator Iterator;
	string inputStr;
	while (*loop._keepAlive) {
		*loop._input >> inputStr;
		if (inputStr != "" && *loop._keepAlive) {
			int start = 0;
			int end = inputStr.length();
			while (inputStr.at(end - 1) == ' ' && end > 1) {
				--end;
			}
			while (inputStr.at(start) == ' ' && start < end) {
				++start;
			}
			if (start != end) {
				inputStr = inputStr.substr(start, end);
				transform(inputStr.begin(), inputStr.end(), inputStr.begin(), ::tolower);
				bool notFound = true;
				for (Iterator i = loop._cmds.begin(); i != loop._cmds.end(); ++i) {
					if (i->first == inputStr) {
						(*loop._keepAlive) = !i->second(*loop._output, *loop._state);
						notFound = false;
						break;
					}
				}
				if (notFound) {
					*loop._output << "That command does not exist." << endl;
				}
			}
			if (*loop._keepAlive) {
				*loop._updateMap = true;
			}
		}
	}
	loop.destroy_keep_alive();
}

