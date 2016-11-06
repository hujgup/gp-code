#include "Inventory.h"

using namespace std;

IHasInventory::~IHasInventory() {
}
bool IHasInventory::operator ==(const IHasInventory& other) const {
	return type_id() == other.type_id() && id() == other.id();
}
bool IHasInventory::operator !=(const IHasInventory& other) const {
	return !(*this == other);
}