#pragma once

#include <unordered_map>
#include "Event.h"
#include "Message.h"

class MessageAccessor;

class MessageDispatcher : public Object {
private:
	std::unordered_map<std::string,EventKit<MessageDispatcher,Message>> _events;
	std::unordered_map<std::string,Message*> _heldMessages;
	void update_timeouts();
public:
	MessageDispatcher();
	virtual ~MessageDispatcher();
	virtual std::string type_name() const override;
	void register_event(std::string id);
	void register_event(const Message& msg);
	void dispatch(Message& msg);
	MessageAccessor operator [](std::string id);
	MessageAccessor operator [](const Message& msg);
	friend class MessageAccessor;
};

class MessageAccessor : public Object {
private:
	MessageDispatcher& _dispatcher;
	std::string _id;
	Message* _heldMsg;
public:
	MessageAccessor(MessageDispatcher& dispatcher,std::string id);
	virtual ~MessageAccessor();
	virtual std::string type_name() const override;
	bool has_held_message() const;
	Event<MessageDispatcher,Message>& event();
	Message* held_message();
};
