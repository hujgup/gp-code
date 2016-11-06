#pragma once

#include "Object.h"

struct EmptyEventArgs : Object {
	virtual ~EmptyEventArgs();
	virtual std::string type_name() const override;
};
