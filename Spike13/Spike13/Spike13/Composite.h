#pragma once

#include <vector>
#include "Component.h"

class Composite : public Component {
private:
	std::vector<Component*> _components;
protected:
	virtual void do_this(BinaryWriter& output,std::map<unsigned long,void*> input) override;
public:
	virtual ~Composite();
	static const unsigned long id;
	virtual unsigned long cmp_id() const override;
	void add(Component* c);
	bool contains(Component* c);
	Component* get(Component* c);
	bool remove(Component* c);
};

