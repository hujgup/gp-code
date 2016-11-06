#include "LineResult.h"

using namespace std;

LineResult::LineResult() : error(""), id(""), regex("") {
}
LineResult::~LineResult() {
}
string LineResult::type_name() const {
	return "CommandReader::LineResult";
}
bool LineResult::has_error() const {
	return error.length() != 0;
}
