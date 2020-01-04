
#include "Game.hpp"

int main(int argc, const char* argv[]) {
	// Setup the Application and start the main game-loop
	StoneCold::Game app("Stone Cold");
	return (app.Initialize() ? app.Run() : -1);
}
