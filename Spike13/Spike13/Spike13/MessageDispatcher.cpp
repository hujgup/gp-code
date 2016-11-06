#include "MessageDispatcher.h"

using namespace std;

void MessageDispatcher::update_timeouts() {
	list<pair<string,Message*>> toDelete;
	for (unordered_map<string,Message*>::iterator i = _heldMessages.begin(); i != _heldMessages.end(); ++i) {
		if (i->second->is_timed_out()) {
			toDelete.push_back(*i);
		}
	}
	for (list<pair<string,Message*>>::const_iterator i = toDelete.cbegin(); i != toDelete.cend(); ++i) {
		_heldMessages.erase(i->first);
		delete i->second;
	}
}
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
void MessageDispatcher::register_event(const Message& msg) {
	register_event(msg.type_name());
}
void MessageDispatcher::dispatch(Message& msg) {
	string id = msg.type_name();
	register_event(id);
	_events[id](this, msg, [&msg]() {
		msg.seek(0);
	});
	update_timeouts();
	if (_heldMessages.find(id) != _heldMessages.cend()) {
		delete _heldMessages[id];
	}
	_heldMessages[id] = msg.clone();
}
MessageAccessor MessageDispatcher::operator [](string id) {
	return MessageAccessor(*this,id);
}
MessageAccessor MessageDispatcher::operator [](const Message& msg) {
	return (*this)[msg.type_name()];
}

MessageAccessor::MessageAccessor(MessageDispatcher& dispatcher,string id) : _dispatcher(dispatcher), _id(id) {
	_dispatcher.update_timeouts();
	if (_dispatcher._heldMessages.find(_id) != _dispatcher._heldMessages.end()) {
		_heldMsg = _dispatcher._heldMessages[_id];
	}
}
MessageAccessor::~MessageAccessor() {
}
string MessageAccessor::type_name() const {
	return "MessageAccessor";
}
bool MessageAccessor::has_held_message() const {
	return _heldMsg != NULL;
}
Event<MessageDispatcher,Message>& MessageAccessor::event() {
	_dispatcher.register_event(_id);
	return _dispatcher._events[_id];
}
Message* MessageAccessor::held_message() {
	return _heldMsg;
}