#pragma once

#include <deque>
#include <stdexcept>
#include "Object.h"

template<typename TKey,typename TValue>
class InsertionOrderedMap : public Object {
private:
	typedef std::deque<std::pair<TKey,TValue>> Container;
public:
	typedef typename Container::iterator Iterator;
	typedef typename Container::const_iterator ConstIterator;
private:
	Container _data;
public:
	InsertionOrderedMap(const InsertionOrderedMap<TKey,TValue>& copyMe);
	InsertionOrderedMap();
	virtual ~InsertionOrderedMap();
	virtual std::string type_name() const override;
	ConstIterator cbegin() const;
	ConstIterator cend() const;
	ConstIterator crbegin() const;
	ConstIterator crend() const;
	Iterator begin();
	Iterator end();
	Iterator rbegin();
	Iterator rend();
	bool empty() const;
	std::size_t size() const;
	std::size_t max_size() const;
	bool contains_key(const TKey& key) const;
	bool contains_value(const TValue& value) const;
	ConstIterator find(const TKey& key) const;
	std::size_t count(const TKey& key) const;
	const TValue& at(const TKey& key) const;
	TValue& at(const TKey& key);
	std::size_t erase(const TKey& key);
	bool insert(const TKey& key,TValue& value);
	void swap(InsertionOrderedMap<TKey,TValue>& other);
	void clear();
	TValue& operator [](const TKey& key);
	InsertionOrderedMap<TKey,TValue>& operator =(const InsertionOrderedMap<TKey,TValue>& other);
};

template<typename TKey,typename TValue>
InsertionOrderedMap<TKey,TValue>::InsertionOrderedMap(const InsertionOrderedMap<TKey,TValue>& copyMe) {
	*this = copyMe;
}
template<typename TKey,typename TValue>
InsertionOrderedMap<TKey,TValue>::InsertionOrderedMap() {
}
template<typename TKey,typename TValue>
InsertionOrderedMap<TKey,TValue>::~InsertionOrderedMap() {
}
template<typename TKey,typename TValue>
std::string InsertionOrderedMap<TKey,TValue>::type_name() const {
	return "InsertionOrderedMap<TKey,TValue>";
}
template<typename TKey,typename TValue>
typename InsertionOrderedMap<TKey,TValue>::ConstIterator InsertionOrderedMap<TKey,TValue>::cbegin() const {
	return _data.cbegin();
}
template<typename TKey,typename TValue>
typename InsertionOrderedMap<TKey,TValue>::ConstIterator InsertionOrderedMap<TKey,TValue>::cend() const {
	return _data.cend();
}
template<typename TKey,typename TValue>
typename InsertionOrderedMap<TKey,TValue>::ConstIterator InsertionOrderedMap<TKey,TValue>::crbegin() const {
	return _data.crbegin();
}
template<typename TKey,typename TValue>
typename InsertionOrderedMap<TKey,TValue>::ConstIterator InsertionOrderedMap<TKey,TValue>::crend() const {
	return _data.crend();
}
template<typename TKey,typename TValue>
typename InsertionOrderedMap<TKey,TValue>::Iterator InsertionOrderedMap<TKey,TValue>::begin() {
	return _data.begin();
}
template<typename TKey,typename TValue>
typename InsertionOrderedMap<TKey,TValue>::Iterator InsertionOrderedMap<TKey,TValue>::end() {
	return _data.end();
}
template<typename TKey,typename TValue>
typename InsertionOrderedMap<TKey,TValue>::Iterator InsertionOrderedMap<TKey,TValue>::rbegin() {
	return _data.begin();
}
template<typename TKey,typename TValue>
typename InsertionOrderedMap<TKey,TValue>::Iterator InsertionOrderedMap<TKey,TValue>::rend() {
	return _data.end();
}
template<typename TKey,typename TValue>
bool InsertionOrderedMap<TKey,TValue>::empty() const {
	return _data.empty();
}
template<typename TKey,typename TValue>
std::size_t InsertionOrderedMap<TKey,TValue>::size() const {
	return _data.size();
}
template<typename TKey,typename TValue>
std::size_t InsertionOrderedMap<TKey,TValue>::max_size() const {
	return _data.size();
}
template<typename TKey,typename TValue>
bool InsertionOrderedMap<TKey,TValue>::contains_key(const TKey& key) const {
	return find(key) != end();
}
template<typename TKey,typename TValue>
bool InsertionOrderedMap<TKey,TValue>::contains_value(const TValue& value) const {
	bool res = false;
	for (ConstIterator i = _values.cbegin(); i != _values.cend(); ++i) {
		if (value == i->second) {
			res = true;
			break;
		}
	}
	return res;
}
template<typename TKey,typename TValue>
typename InsertionOrderedMap<TKey,TValue>::ConstIterator InsertionOrderedMap<TKey,TValue>::find(const TKey& key) const {
	for (ConstIterator i = _data.cbegin(); i != _data.cend(); ++i) {
		if (key == i->first) {
			return i;
		}
	}
	return _data.cend();
}
template<typename TKey,typename TValue>
std::size_t InsertionOrderedMap<TKey,TValue>::count(const TKey& key) const {
	std::size_t res = 0;
	for (Iterator i = _data.begin(); i != _data.end(); ++i) {
		if (key == i->first) {
			++res;
		}
	}
	return res;
}
template<typename TKey,typename TValue>
const TValue& InsertionOrderedMap<TKey,TValue>::at(const TKey& key) const {
	return const_cast<InsertionOrderedMap*>(this)->at(key);
}
template<typename TKey,typename TValue>
TValue& InsertionOrderedMap<TKey,TValue>::at(const TKey& key) {
	for (Iterator i = _data.begin(); i != _data.end(); ++i) {
		TKey& currentKey = i->first;
		if (key == currentKey) {
			return i->second;
		}
	}
	throw std::out_of_range("Map does not contain the specified key.");
}
template<typename TKey,typename TValue>
std::size_t InsertionOrderedMap<TKey,TValue>::erase(const TKey& key) {
	for (std:::deque<std::pair<TKey,TValue>>::iterator i = _data.begin(); i != _data.end(); ++i) {
		if (i->first == key) {
			_data.erase(i);
			return 1;
		}
	}
	return 0;
}
template<typename TKey,typename TValue>
bool InsertionOrderedMap<TKey,TValue>::insert(const TKey& key,TValue& value) {
	bool res = !contains_key(key);
	if (res) {
		_data.push_back(std::pair<TKey,TValue>(key,value));
	}
	return res;
}
template<typename TKey,typename TValue>
void InsertionOrderedMap<TKey,TValue>::swap(InsertionOrderedMap<TKey,TValue>& other) {
	InsertionOrderedMap<TKey,TValue> temp(*this);
	*this = other;
	other = temp;
}
template<typename TKey,typename TValue>
void InsertionOrderedMap<TKey,TValue>::clear() {
	_data.clear();
}
template<typename TKey,typename TValue>
TValue& InsertionOrderedMap<TKey,TValue>::operator [](const TKey& key) {
	try {
		return at(key);
	} catch (std::out_of_range) {
		_data.push_back(std::pair<TKey,TValue>(key,TValue()));
		return (*this)[key];
	}
}
template<typename TKey,typename TValue>
InsertionOrderedMap<TKey,TValue>& InsertionOrderedMap<TKey,TValue>::operator =(const InsertionOrderedMap<TKey,TValue>& other) {
	_data = other._data;
}
