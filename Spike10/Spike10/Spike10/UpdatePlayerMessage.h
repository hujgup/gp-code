#pragma once

#include "Message.h"
#include "Player.h"

class UpdatePlayerMessage : public Message {
public:
	UpdatePlayerMessage(UpdatePlayerMessage& copyMe);
	UpdatePlayerMessage(Player* player);
	UpdatePlayerMessage();
	virtual std::string type_name() const override;
	virtual std::time_t timeout() const override;
	virtual Message* clone() override;
};