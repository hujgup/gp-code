#pragma once

#include <string>
#include <iostream>
#include <memory>

class CellOccupier {
private:
	bool _empty;
	bool _impassable;
	std::string _name;
	std::string _desc;
	static CellOccupier* create_empty();
public:
	static const std::unique_ptr<CellOccupier> EMPTY;
	CellOccupier(std::string name,std::string desc,bool impassable);
	CellOccupier(std::string name,std::string desc);
	CellOccupier();
	bool is_impassable() const;
	std::string name() const;
	std::string desc() const;
	bool operator ==(const CellOccupier& other) const;
	bool operator !=(const CellOccupier& other) const;
	friend std::ostream& operator <<(std::ostream& stream,const CellOccupier& occupier);
};

