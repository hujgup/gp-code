#include "WorldSelector.h"
#include "Gameplay.h"

using namespace std;

const string WorldSelector::_DISPLAY_TEXT = "Zorkish :: Select Adventure" + GameState::HORIZONTAL_RULE + "\nChoose your adventure:";

GameState* WorldSelector::cmd_mountain() {
	Gameplay* g = (Gameplay*)(storage()->gameplay());
	g->world_name("Mountain");
	return g;
}
GameState* WorldSelector::cmd_water() {
	Gameplay* g = (Gameplay*)(storage()->gameplay());
	g->world_name("Water");
	return g;
}
GameState* WorldSelector::cmd_box() {
	Gameplay* g = (Gameplay*)(storage()->gameplay());
	g->world_name("Box");
	return g;
}
void WorldSelector::create_options() {
	add_option("Mountain World",bind(&WorldSelector::cmd_mountain,this));
	add_option("Water World",bind(&WorldSelector::cmd_water,this));
	add_option("Box World",bind(&WorldSelector::cmd_box,this));
}
WorldSelector::WorldSelector(ostream& output,istream& input,StateStorage* storage) : GameMenu(output,input,_DISPLAY_TEXT,storage) {
	create_options();
}
WorldSelector::WorldSelector(StateStorage* storage) : GameMenu(_DISPLAY_TEXT,storage) {
	create_options();
}
WorldSelector::~WorldSelector() {
}

