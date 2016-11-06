#include "MessageDispatcher.h"

using namespace std;

MessageDispatcher::MessageDispatcher() {
}
MessageDispatcher::~MessageDispatcher() {
}
string MessageDispatcher::type_name() const {
	return "MessageDispatcher";
}
void MessageDispatcher::register_event(string id) {
	if (_events.find(id) == _events.cend()) {
		_events[id] = EventKit<MessageDispatcher,Message>();
	}
}
void MessageDispatcher::register_event(Message& msg) {
	register_event(msg.type_name());
}
void MessageDispatcher::dispatch(Message& msg) {
	string id = msg.type_name();
	register_event(id);
	_events[id](this,msg);
}
Event<MessageDispatcher,Message>& MessageDispatcher::operator [](string id) {
	register_event(id);
	return _events[id];
}
Event<MessageDispatcher,Message>& MessageDispatcher::operator [](Message& msg) {
	return (*this)[msg.type_name()];
}

