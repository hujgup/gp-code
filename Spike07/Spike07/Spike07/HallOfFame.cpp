#include "HallOfFame.h"

using namespace std;

void HallOfFame::output_content() const {
	_output << "Zorkish :: Hall of Fame" + GameState::HORIZONTAL_RULE << endl;
	_output << "Top 10 Zorkish Adventure Champions" << endl;
	_output << "1. JOHN CITIZEN, Mountain World, 1" << endl;
}
GameState* HallOfFame::next_state() const {
	return storage()->main_menu();
}
HallOfFame::HallOfFame(ostream& output,istream& input,StateStorage* storage) : GameSplash(output,input,storage) {
}
HallOfFame::HallOfFame(StateStorage* storage) : GameSplash(storage) {
}
HallOfFame::~HallOfFame() {
}
