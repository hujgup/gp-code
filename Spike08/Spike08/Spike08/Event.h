#pragma once

#include <vector>
#include <functional>
#include "Object.h"
#include "EmptyEventArgs.h"

template<typename TSender,typename TArgs>
class Event;

template<typename TSender,typename TArgs>
class EventKit : public Object {
private:
	Event<TSender,TArgs> _evt;
public:
	EventKit();
	virtual std::string type_name() const override;
	operator Event<TSender,TArgs>&() {
		return _evt;
	};
	void operator ()(TSender* sender,TArgs& args,std::function<void()> betweenFires);
	void operator ()(TSender* sender,TArgs& args);
};

template<typename TSender,typename TArgs>
EventKit<TSender,TArgs>::EventKit() : _evt(Event<TSender,TArgs>()) {
}
template<typename TSender,typename TArgs>
std::string EventKit<TSender,TArgs>::type_name() const {
	return "EventKit<TSender,TArgs>";
}
template<typename TSender, typename TArgs>
void EventKit<TSender, TArgs>::operator ()(TSender* sender,TArgs& args,std::function<void()> betweenFires) {
	betweenFires();
	for (std::vector<Event<TSender, TArgs>::Handler>::iterator i = _evt._handlers.begin(); i != _evt._handlers.end(); ++i) {
		(*i)(*sender, args);
		betweenFires();
	}
}
template<typename TSender,typename TArgs>
void EventKit<TSender,TArgs>::operator ()(TSender* sender,TArgs& args) {
	(*this)(sender,args,[]{
	})
}

template<typename TSender,typename TArgs>
class Event : public Object {
public:
	friend class EventKit<TSender,TArgs>;
	typedef std::function<void(TSender&,TArgs&)> Handler;
private:
	std::vector<Handler> _handlers;
	Event();
public:
	virtual std::string type_name() const override;
	Event<TSender,TArgs>& operator +=(Handler handler);
	Event<TSender,TArgs>& operator -=(Handler handler);
};

template<typename TSender,typename TArgs>
Event<TSender,TArgs>::Event() {
}
template<typename TSender,typename TArgs>
std::string Event<TSender,TArgs>::type_name() const {
	return "Event<TSender,TArgs>";
}
template<typename TSender,typename TArgs>
Event<TSender,TArgs>& Event<TSender,TArgs>::operator +=(Handler handler) {
	_handlers.push_back(handler);
	return *this;
}
template<typename TSender,typename TArgs>
Event<TSender,TArgs>& Event<TSender,TArgs>::operator -=(Handler handler) {
	std::vector<Handler>::iterator position = std::find(_handlers.begin(),handlers.end(),handler);
	if (position != _handlers.end()) {
		_handlers.erase(position);
	}
	return *this;
}

