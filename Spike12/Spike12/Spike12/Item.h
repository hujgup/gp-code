#pragma once

#include "Object.h"

class Item : public Object {
private:
	std::string _name;
	std::string _desc;
public:
	Item(std::string name, std::string desc);
	Item(std::string name);
	Item();
	virtual ~Item();
	virtual std::string type_name() const override;
	std::string name() const;
	std::string desc() const;
	bool operator ==(const Item& other) const;
	bool operator !=(const Item& other) const;
};

namespace std {
	template<>
	struct hash<Item> {
		std::size_t operator ()(const Item& item) const {
			using std::size_t;
			using std::hash;
			using std::string;

			return hash<string>()(item.name());
		}
	};
}
