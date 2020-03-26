StoneCold (2D Game and Engine)
==============================

About
-----

StoneCold is a top-down, 2D roguelike RPG and comes with its own SDL2 based Engine. 

It will be developed over the course of 2020, inspired by yahtzee (zero punctuation) who developed 12 games in 12 Month ... but im not that crazy so its just one game in 12 Months. Always intrigued by 2D/3D Graphic-Engines i every now and then started developing my own, but either got bogged down in details or overwhelmed with possible features, so none ever made it out of prototype-status. But for 2020 the clear goal is to try again with a "Game (and architecture) first" approach. Which seems to be working way better than the old "Engine first!!1!", already.

The games concept is inspired by Diablo (Gameplay aspects), Action-RPGs just like Dark Souls (Gameplay aspects), Nuclear Throne (roguelike-ness and procedural map generation) and many more.

Using
-----

- C++ 17 (MSVC 14.24 VS2019)
- [SDL2 v2.0.10](https://www.libsdl.org/index.php) : Cross-platform Graphics and IO library
- [SDL_image v2.0.5](https://www.libsdl.org/projects/SDL_image/) : Loads images as SDL surfaces and textures
- [SDL_ttf v2.0.15](https://www.libsdl.org/projects/SDL_ttf/) : Allows the use of TrueType fonts in SDL applications
- All the SDL/SDL_image/SDL_ttf dependencies

Architecture and Code Structure
-------------------------------

The code is written in C++ 11 (and beyond) and in a object oriented manner. Simplicity (or rather: avoiding complexity) is a main goal. Well. Fingers crossed.

As stated, my basic approach of "i want to build a Engine" has changed for this project and the game/gameplay itself has top priority. Engine reusability, common Render-API, etc. were no factor when it came to the core design and left to SDL2 as much as possible. The result is a thighly coupled structure composed of four projects, that revolve around games resource management, game object creation, game state management, the Entity-Component-Sytem and feeding it all to SDL:
- <b>StoneCold.Base:</b> Basic Settings, common Types and Enums, Math and Exception classes
- <b>StoneCold.Engine:</b> Entity-Component-System, Game-State-Management and Event handling
- <b>StoneCold.Game:</b> Window creation, Levels/NPCs/Menu Setup, Manager init and main loop
- <b>StoneCold.Resources:</b> Resource management with Lifetime checks (loading and unloading)
- <b>StoneCold.Tests:</b> Unit Tests

The Engines core building blocks are the Entity–component–system (ECS) and the Game-State management. 

Copyright/Attribution Notices
-----------------------------

Some of the Textures are hand drawn (thanks MS Paint and Gimp) but all the nice looking ones are created by actual Artists:

- DawnBringer Color-Palette by Richard Fhager [link to his pixeljoint](http://pixeljoint.com/p/23821.htm)
- Dwarf Sprites by Elthen (Ahmet Avci) [link to his patreon](https://www.patreon.com/elthen)
- Mountain Background by NotTandy [link to his pixelart](https://www.pixilart.com/nottandy)
- UI Textures (RPG Pack) by Kenney Vleugels [link to his art](https://www.kenney.nl)
- Font Crom by russh (Russell Herschler) [link to his homepage](http://www.dragonfang.com/)
- Font OldeDethek by Pixel Sagas [link to the homepage](http://www.pixelsagas.com/)

Todo (current tasks)
--------------------

- [x] Add a common Color-Palette
- [ ] Map Texture overhaul (Use Color Palette, get the Walls and Wall-Tops right)
- [x] Map Generator overhaul (Code cleanup)
- [x] Add some basic GameStates (Intro, Game, Menu)
- [x] Add User Events to the SDL Event-System
- [x] Allow switching between the basic states
- [x] Add some basic GUI Elements (Label to the Intro, Buttons to the Menu)
- [ ] Replace old "oo-style" ECS with an actual ECS (!!!) 
- [ ] Bugfix: Collision detection
- [ ] Bugfix: libpng warning: iCCP: CRC error
- [ ] Finish ECS Unit Tests
- [ ] Finish Math class Unit Tests
- [ ] Render only Tiles visible by the Camera
- [ ] Add Controller Support
- [ ] Add a basic Options Menu with a default Keybinding images for Keyboard and Controller
- [ ] Automatically check if Controller is available / otherwise use Keyboard input
- [ ] Test, Cleanup, Fix, Optimize

Todo (backlog items)
--------------------
- Code fixes: -Wall -Wextra
- Add NPCs (Enemies with simple AI)
- Add Pickups and Buffs (Gold, Items, Chests)
- Add Player Actions (Dodge, Attack, Special-Attack)
- Add Player GUI (Lifebar, Action-Bar, Skill/Stat Window)
