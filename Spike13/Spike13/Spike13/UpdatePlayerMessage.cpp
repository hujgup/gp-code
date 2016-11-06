#include "UpdatePlayerMessage.h"

using namespace std;

UpdatePlayerMessage::UpdatePlayerMessage(UpdatePlayerMessage& copyMe) : Message() {
	void* player;
	copyMe.read() >> player;
	write() << player;
}
UpdatePlayerMessage::UpdatePlayerMessage(Player* player) : Message() {
	write() << (void*)player;
}
UpdatePlayerMessage::UpdatePlayerMessage() : Message() {
}
string UpdatePlayerMessage::type_name() const {
	return "UpdatePlayerMessage";
}
time_t UpdatePlayerMessage::timeout() const {
	return 0;
}
Message*UpdatePlayerMessage::clone() {
	return new UpdatePlayerMessage(*this);
}

