StoneCold (Game and Engine)
===========================

About
--------

StoneCold is a top-down, 2D roguelike RPG and comes with its own SDL2 based Engine. 

Its developed, because i was always intrigued by 2D/3D Graphic-Engines, but whenever i started developing my own i either got bogged down in details or overwhelmed with possible features. So none ever made it out of prototype-status. But for 2020 i set myself a goal to try again with a "Game (and architecture) first" approach. Which seems to be working way better than the old "Engine first!!1!".

The games concept is inspired by Diablo (Gameplay aspects), Action-RPGs just like Dark Souls (Gameplay aspects), Nuclear Throne (roguelike-ness and procedural map generation) and many more.

Using
--------

- C++ 17 (MSVC 14.24 VS2019)
- [SDL2](https://www.libsdl.org/index.php) : Cross-platform Graphics and IO library
- [SDL_image 2.0](https://www.libsdl.org/projects/SDL_image/) : Loads images as SDL surfaces and textures
- [SDL_ttf 2.0](https://www.libsdl.org/projects/SDL_ttf/) : Allows the use of TrueType fonts in SDL applications
- All the SDL/SDL_image/SDL_ttf dependencies

Todo (current tasks)
------------

- [x] Update map algorithm to also add the "shadow" floor-tiles
- [x] Update the Map-Textures (Add Teleport-Pad and make them look nice)
- [x] Update the EngineCore to factor in ReosurceLifetime as well
- [x] Add batch rendering to the Engine (based on Texture Id)
- [x] Update the ECS (Extract Animation, fix FixedSprite, ...)
- [x] Fix Collision detection and update it, to work with smaller hitboxes
- [ ] Collision-check and render only objects, that are visible by the Camera
- [ ] Test, Cleanup, Fix, Optimize

Todo (backlog items)
--------------------
- Add Game-States (Game/Menu/Cutscene/...)
- Add a GUI (Menu and Ingame-Lifebar, etc.)
- Add NPCs (Enemies with simple AI)

Copyright/Attribution Notices
-----------------------------

- Dwarf Sprites: Elthen (Ahmet Avci) [link to his patreon](https://www.patreon.com/elthen)
