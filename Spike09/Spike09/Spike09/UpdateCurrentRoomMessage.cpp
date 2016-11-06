#include "UpdateCurrentRoomMessage.h"

using namespace std;

UpdateCurrentRoomMessage::UpdateCurrentRoomMessage(const UpdateCurrentRoomMessage& copyMe) : Message() {
}
UpdateCurrentRoomMessage::UpdateCurrentRoomMessage() : Message() {
}
string UpdateCurrentRoomMessage::type_name() const {
	return "UpdateCurrentRoomMessage";
}
time_t UpdateCurrentRoomMessage::timeout() const {
	return 0;
}
Message* UpdateCurrentRoomMessage::clone() {
	return new UpdateCurrentRoomMessage(*this);
}