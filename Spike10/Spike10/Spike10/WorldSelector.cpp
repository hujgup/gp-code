#include "WorldSelector.h"
#include "Gameplay.h"
#include "WorldSwitchMessage.h"

using namespace std;

const string WorldSelector::_DISPLAY_TEXT = "Zorkish :: Select Adventure" + GameState::HORIZONTAL_RULE + "\nChoose your adventure:";

GameState* WorldSelector::push_world(string worldName) {
	WorldSwitchMessage msg(worldName);
	storage()->dispatcher().dispatch(msg);
	return storage()->gameplay();
}
void WorldSelector::create_options() {
	add_option("Mountain World",bind(&WorldSelector::push_world,this,"Mountain"));
	add_option("Water World",bind(&WorldSelector::push_world,this,"Water"));
	add_option("Box World",bind(&WorldSelector::push_world,this,"Box"));
}
WorldSelector::WorldSelector(ostream& output,istream& input,StateStorage* storage) : GameMenu(output,input,_DISPLAY_TEXT,storage) {
	create_options();
}
WorldSelector::WorldSelector(StateStorage* storage) : GameMenu(_DISPLAY_TEXT,storage) {
	create_options();
}
WorldSelector::~WorldSelector() {
}
string WorldSelector::type_name() const {
	return "WorldSelector";
}

