#include "WorldSwitchMessage.h"

using namespace std;

WorldSwitchMessage::WorldSwitchMessage(string worldName) : Message(worldName) {
}
WorldSwitchMessage::WorldSwitchMessage() {
}
string WorldSwitchMessage::type_name() const {
	return "WorldSwitchMessage";
}