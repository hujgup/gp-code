#include "MainMenu.h"
#include "HallOfFame.h"
#include "Credits.h"
#include "CommandLister.h"
#include "WorldSelector.h"

using namespace std;

const string MainMenu::_DISPLAY_TEXT = "Zorkish :: Main Menu" + GameState::HORIZONTAL_RULE + "\nWelcome to Zorkish Adventures";

GameState* MainMenu::cmd_select() {
	return storage()->world_selector();
}
GameState* MainMenu::cmd_scores() {
	return storage()->hall_of_fame();
}
GameState* MainMenu::cmd_help() {
	return storage()->command_lister();
}
GameState* MainMenu::cmd_about() {
	return storage()->credits();
}
GameState* MainMenu::cmd_quit() {
	return storage()->quit();
}

void MainMenu::create_options() {
	add_option("Select Adventure and Play", bind(&MainMenu::cmd_select,this));
	add_option("Hall of Fame",bind(&MainMenu::cmd_scores,this));
	add_option("Help",bind(&MainMenu::cmd_help,this));
	add_option("About",bind(&MainMenu::cmd_about,this));
	add_option("Quit",bind(&MainMenu::cmd_quit,this));
}
MainMenu::MainMenu(ostream& output, istream& input,StateStorage* storage) : GameMenu(output,input,_DISPLAY_TEXT,storage) {
	create_options();
}
MainMenu::MainMenu(StateStorage* storage) : GameMenu(_DISPLAY_TEXT,storage) {
	create_options();
}
MainMenu::~MainMenu() {
}
string MainMenu::type_name() const {
	return "MainMenu";
}
