
#include "Game.hpp"

int main(int argc, const char* argv[]) {
	// Setup the Application and start the main game-loop
	StoneCold::Game app("Dwarf Game", "");
	return (app.Initialize() ? app.Run() : -1);
}
