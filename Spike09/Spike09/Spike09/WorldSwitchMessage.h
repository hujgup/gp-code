#pragma once

#include "Message.h"

class WorldSwitchMessage : public Message {
public:
	WorldSwitchMessage(WorldSwitchMessage& copyMe);
	WorldSwitchMessage(std::string worldName);
	WorldSwitchMessage();
	virtual std::string type_name() const override;
	virtual std::time_t timeout() const override;
	virtual Message* clone() override;
};