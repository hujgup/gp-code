#pragma once

#include <unordered_map>
#include "Event.h"
#include "Message.h"

class MessageDispatcher : public Object {
private:
	std::unordered_map<std::string,EventKit<MessageDispatcher,Message>> _events;
public:
	MessageDispatcher();
	virtual ~MessageDispatcher();
	virtual std::string type_name() const override;
	void register_event(std::string id);
	void register_event(Message& msg);
	void dispatch(Message& msg);
	Event<MessageDispatcher,Message>& operator [](std::string id);
	Event<MessageDispatcher,Message>& operator [](Message& msg);
};