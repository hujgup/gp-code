#include "WorldSwitchMessage.h"

using namespace std;

WorldSwitchMessage::WorldSwitchMessage(WorldSwitchMessage& copyMe) {
	string worldName;
	copyMe.read() >> worldName;
	this->write() << worldName;
}
WorldSwitchMessage::WorldSwitchMessage(string worldName) : Message(worldName) {
}
WorldSwitchMessage::WorldSwitchMessage() {
}
string WorldSwitchMessage::type_name() const {
	return "WorldSwitchMessage";
}
time_t WorldSwitchMessage::timeout() const {
	return 0;
}
Message* WorldSwitchMessage::clone() {
	return new WorldSwitchMessage(*this);
}