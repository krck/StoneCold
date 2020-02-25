StoneCold (2D Game and Engine)
==============================

About
-----

StoneCold is a top-down, 2D roguelike RPG and comes with its own SDL2 based Engine. 

It will be developed over the course of 2020, inspired by yahtzee (zero punctuation) who developed 12 games in 12 Month ... but im not that crazy so its just one game in 12 Months. Always intrigued by 2D/3D Graphic-Engines, i every now and then started developing my own, but either got bogged down in details or overwhelmed with possible features, so none ever made it out of prototype-status. But for 2020 the clear goal is to try again with a "Game (and architecture) first" approach. Which seems to be working way better than the old "Engine first!!1!", already.

The games concept is inspired by Diablo (Gameplay aspects), Action-RPGs just like Dark Souls (Gameplay aspects), Nuclear Throne (roguelike-ness and procedural map generation) and many more.

Using
-----

- C++ 17 (MSVC 14.24 VS2019)
- [SDL2](https://www.libsdl.org/index.php) : Cross-platform Graphics and IO library
- [SDL_image 2.0](https://www.libsdl.org/projects/SDL_image/) : Loads images as SDL surfaces and textures
- [SDL_ttf 2.0](https://www.libsdl.org/projects/SDL_ttf/) : Allows the use of TrueType fonts in SDL applications
- All the SDL/SDL_image/SDL_ttf dependencies

Architecture and Code Structure
-------------------------------

The code is written in an object oriented manner and simplicity (or rather: avoiding complexity) is a main goal. The code and classes are structured and commented in a way that even a total game-programming noob like myself should still be able to comprehend the Game and Engine logic a few years down the line. Fingers crossed.

As stated, my basic approach of "i want to build a Engine" has changed for this project and the game/gameplay itself has top priority. Engine reusability, a common Render-API, etc. comes second. The result is a more thighly coupled structure composed of four projects, that obviously still need a Engine, but its more as a necessity and not the sole focus:
- <b>StoneCold.Base:</b> Basic Settings, SDL2 includes, common Types and Enums, Math (Vec2) classes
- <b>StoneCold.Engine:</b> ECS, Game-State management, Collision detection, procedural Map generation, etc.
- <b>StoneCold.Game:</b> Window creation, Main-Loop and the "SimulationManager" to setup Levels, NPCs, Menus, etc.
- <b>StoneCold.Resources:</b> Resource management with Lifetime checks (loading and unloading) and unique Resources

The Engines core building blocks are the Entity–component–system (ECS) and the Game-State management. 


Copyright/Attribution Notices
-----------------------------

Some of the Textures are hand drawn (thanks MS Paint and Gimp) but the nice looking ones are created by actual Artists:

- Dwarf Sprites: Elthen (Ahmet Avci) [link to his patreon](https://www.patreon.com/elthen)

Todo (current tasks)
--------------------

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
- Add Controller Support (Keyboard as fallback)
- Add NPCs (Enemies with simple AI)
