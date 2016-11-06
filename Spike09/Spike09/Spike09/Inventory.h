#pragma once

#include <vector>
#include <map>
#include <memory>
#include "Object.h"

class Item;
class IHasInventory;

class IInventory : public Object {
private:
	class ContainerMap : public Object {
	private:
		std::map<Item*, IHasInventory*> _ITEM_TO_CONTAINER_MAP;
		std::map<IHasInventory*, std::vector<Item*>> _CONTAINER_TO_ITEM_MAP;
	public:
		ContainerMap();
		virtual ~ContainerMap();
		virtual std::string type_name() const override;
		bool contains_item(const Item* item) const;
		bool contains_container(const IHasInventory* container) const;
		void register_container(IHasInventory* container);
		void update(Item* item, IHasInventory* container);
		std::vector<Item*> query(std::string name, IInventory* container);
		void clear();
		const IHasInventory* operator [](const Item* item) const;
		const std::vector<Item*>* operator [](const IInventory* container) const;
		IHasInventory* operator [](Item* item);
		std::vector<Item*>* operator [](IInventory* container);
	};
protected:
	static ContainerMap _CONTAINER_MAP;
public:
	virtual ~IInventory();
	static void clear_references();
	virtual std::vector<Item*> all_items() const = 0;
	virtual unsigned int total_item_count() const = 0;
	virtual unsigned int item_count(std::string name) const = 0;
	virtual bool can_access_item(Item& item) const = 0;
	virtual bool has_item(std::string name) const = 0;
	virtual unsigned int move_items(std::string name, IHasInventory& moveTo, unsigned int quantity) = 0;
	virtual bool move_item(std::string name, IHasInventory& moveTo) = 0;
	virtual bool move_item(Item& item, IHasInventory& moveTo) = 0;
	virtual void clear(IHasInventory& moveTo) = 0;
	friend class Item;
};


class BasicInventory : public IInventory {
public:
	BasicInventory();
	virtual ~BasicInventory();
	virtual std::string type_name() const override;
	virtual std::vector<Item*> all_items() const override;
	virtual unsigned int total_item_count() const override;
	virtual unsigned int item_count(std::string name) const override;
	virtual bool has_item(std::string name) const override;
	virtual bool can_access_item(Item& item) const override;
	virtual unsigned int move_items(std::string name, IHasInventory& moveTo, unsigned int quantity) override;
	virtual bool move_item(std::string name, IHasInventory& moveTo) override;
	virtual bool move_item(Item& item, IHasInventory& moveTo) override;
	virtual void clear(IHasInventory& removeTo) override;
};



class IHasInventory : public Object {
public:
	virtual ~IHasInventory();
	virtual unsigned char type_id() const = 0;
	virtual unsigned long id() const = 0;
	virtual IInventory& inventory() = 0;
	virtual bool operator ==(const IHasInventory& other) const;
	virtual bool operator !=(const IHasInventory& other) const;
};

class Item : public IHasInventory {
private:
	static std::map<unsigned long, std::shared_ptr<Item>> _REFERENCES;
	unsigned long _id;
	std::string _name;
	std::string _desc;
	BasicInventory _inv;
	Item(unsigned long id, std::string name, std::string desc, IHasInventory& container);
public:
	Item();
	virtual ~Item();
	static void clear_references();
	static bool exists(unsigned long id);
	static Item& create(unsigned long id, std::string name, std::string desc, IHasInventory& container);
	static Item& get(unsigned long id, const IHasInventory& container);
	static Item& get(unsigned long id);
	static unsigned long get_id_by_name(std::string name);
	static std::vector<Item> all_items();
	virtual std::string type_name() const override;
	virtual unsigned char type_id() const override;
	virtual unsigned long id() const override;
	virtual IInventory& inventory() override;
	std::string name() const;
	std::string desc() const;
	bool has_container() const;
	IHasInventory& container();
	void container(const IHasInventory& newContainer);
	bool operator ==(const Item& other) const;
	bool operator !=(const Item& other) const;
};

namespace std {
	template<>
	struct hash<Item> {
		std::size_t operator ()(const Item& item) const {
			using std::hash;
			using std::string;

			return hash<string>()(item.name());
		}
	};
}

