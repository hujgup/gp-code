#pragma once

#include "Message.h"

class WorldSwitchMessage : public Message {
public:
	WorldSwitchMessage(std::string worldName);
	WorldSwitchMessage();
	virtual std::string type_name() const override;
};