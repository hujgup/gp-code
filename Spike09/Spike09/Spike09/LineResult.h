#pragma once

#include "Object.h"

struct LineResult : public Object {
	LineResult();
	virtual ~LineResult();
	virtual std::string type_name() const override;
	bool valid;
	std::string error;
	std::string id;
	std::string regex;
	bool has_error() const;
};
