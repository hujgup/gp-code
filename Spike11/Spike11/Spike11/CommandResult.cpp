#include "CommandResult.h"

using namespace std;

CommandResult::CommandResult(SuccessState success,GameState* result) : _success(success), _result(result) {
}
CommandResult::~CommandResult() {
}
string CommandResult::type_name() const {
	return "CommandResult";
}
const SuccessState& CommandResult::success() const {
	return _success;
}
GameState* CommandResult::result() const {
	return _result;
}