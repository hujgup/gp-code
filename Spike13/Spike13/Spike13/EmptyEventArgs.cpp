#include "EmptyEventArgs.h"

using namespace std;

EmptyEventArgs::~EmptyEventArgs() {
}
string EmptyEventArgs::type_name() const {
	return "EmptyEventArgs";
}
