#pragma once

#include "GameState.h"
#include "SuccessState.h"

class CommandResult {
private:
	SuccessState _success;
	GameState* _result;
public:
	CommandResult(SuccessState success,GameState* result);
	const SuccessState& success() const;
	GameState* result() const;
};