#pragma once

#include <map>
#include "BinaryWriter.h"

class Component {
private:
	static unsigned long _next;
protected:
	static unsigned long acquire_id();
	virtual void do_this(BinaryWriter& output,std::map<unsigned long,void*> input) = 0;
public:
	virtual ~Component();
	virtual unsigned long cmp_id() const = 0;
	void exec(BinaryWriter& output,std::map<unsigned long,void*> input);
	void exec(BinaryWriter& output);
	bool operator ==(const Component& other) const;
	bool operator !=(const Component& other) const;
};

class HealthComponent : public Component {
private:
	unsigned long _hp;
protected:
	virtual void do_this(BinaryWriter& output,std::map<unsigned long,void*> input) override;
public:
	HealthComponent(unsigned long init);
	static const unsigned long id;
	virtual unsigned long cmp_id() const override;
	unsigned long hp() const;
	void hp(unsigned long value);
};

class DamageComponent : public Component {
private:
	unsigned long _dmg;
protected:
	virtual void do_this(BinaryWriter& output,std::map<unsigned long,void*> input) override;
public:
	DamageComponent(unsigned long init);
	static const unsigned long id;
	virtual unsigned long cmp_id() const override;
	unsigned long dmg() const;
	void dmg(unsigned long value);
};

class ItemComponent : public Component {
protected:
	virtual void do_this(BinaryWriter& output,std::map<unsigned long,void*> input) override;
public:
	static const unsigned long id;
	virtual unsigned long cmp_id() const override;
};

/*
1. Game objects that receive attributes (damage, health, flammability, etc.) from component
objects rather than inheritance.
2. Game objects that receive actions (can be picked up, can be attacked, etc.) from component
objects rather than inheritance 
*/



