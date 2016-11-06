#pragma once

#include "Object.h"
#include "GameState.h"
#include "SuccessState.h"

class CommandResult : public Object {
private:
	SuccessState _success;
	GameState* _result;
public:
	CommandResult(SuccessState success,GameState* result);
	virtual ~CommandResult();
	virtual std::string type_name() const override;
	const SuccessState& success() const;
	GameState* result() const;
};