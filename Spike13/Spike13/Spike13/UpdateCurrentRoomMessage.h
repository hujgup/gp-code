#pragma once

#include "Message.h"

class UpdateCurrentRoomMessage : public Message {
public:
	UpdateCurrentRoomMessage(const UpdateCurrentRoomMessage& copyMe);
	UpdateCurrentRoomMessage();
	virtual std::string type_name() const override;
	virtual std::time_t timeout() const override;
	virtual Message* clone() override;
};