#include "CommandResult.h"

CommandResult::CommandResult(SuccessState success,GameState* result) : _success(success), _result(result) {
}
const SuccessState& CommandResult::success() const {
	return _success;
}
GameState* CommandResult::result() const {
	return _result;
}