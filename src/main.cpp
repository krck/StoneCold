
#include "EngineCore.hpp"

int main(int argc, const char* argv[]) {
	// Setup the game engine and start the main loop
	StoneCold::EngineCore engine("Stone Cold");
	return (engine.Initialize() ? engine.Run() : -1);
}
