
#include "EngineCore.hpp"
#include "ResourceCore.hpp"

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

//
// Referenced Projects
// - StoneCold.Engine
// - StoneCold.Resources
// 
// Using Static Libraries (.libs) instead of Dynamic Libraries (.dlls)
// to ensure all StoneCold source code will be put into the .exe file
// and only external code (SDL2, ...) needs to be added dynamically
//

int main(int argc, const char* argv[]) {
	// Setup the game engine and start the main loop
	StoneCold::Engine::EngineCore engine("Stone Cold");
	return (engine.Initialize() ? engine.Run() : -1);
}
