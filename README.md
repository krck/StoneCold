StoneCold (2D Game and Engine)
==============================

# Table of Contents  
1. [About](#about)  
2. [Game Design Document](#gdd)  
3. [Technical Description](#technical)  
4. [Copyright and Attribution Notices](#copyr)
5. [Workitems](#work)


<a name="about"/>

# 1. About

This game will be developed over the course of 2020, inspired by yahtzee (zero punctuation) who developed 12 games in 12 months ... but i am not that crazy so it’s just one game in 12 Months. Always intrigued by 2D/3D Graphic-Engines i every now and then started developing my own, but either got bogged down in details or overwhelmed with possible features, so none ever made it out of prototype-status. But for 2020 the clear goal is to try again with a "Game (and architecture) first" approach. Which seems to be working way better than the old "Engine first!!1!", already.

<a name="gdd"/>

# 2. Game Design Document

### 2.1 Project Description
 
StoneCold is a 2D, top-down, tile-based RPG and comes with its own SDL2 based Engine. The concept is heavily inspired by Diablo (Gameplay aspects), Action-RPGs like Dark Souls (Gameplay aspects), Nuclear Throne (procedural map generation) and many more.

### 2.2 Story, Characters and Theme

The main character is a dwarf called Henry and lives in the small village Boulder, by the Mountain. Many years ago, a strange comet impacted nearby and shattered its core all over the dwarven kingdom. A special metal was found in those fragments, mined and forged by the dwarves. This special metal has great abilities once forged, but all the raw fragments that are still out there, not found for many years, started corrupting the land around them and spawning strange creatures that now threaten the dwarven kingdom.

### 2.3 Progression

The player starts out in a town-hub, to which he can return to at any moment and progresses through a series of zones (grasslands, highlands, desert, arctic, castles, ...). Each zone has a bunch of levels and ends in a boss fight. Each level of a zone needs a specific quest/task to be completed, before moving on to the next level (find all X, kill all Y, ...). Once all zones are traversed Henry reaches the biggest of the raw comet-fragments and fights the final boss, to cleanse the lands for good.

After that an "endless-mode" will be unlocked in town, to level/quest/grind further.

### 2.4 Gameplay and User Skills

- Keyboard / Controller input
- Navigating different map types and dungeons
- Tactical action combat, learning AI behavior and terrain to maximize the chances of survival
- Stat and skill management - improve your chances of survival for different threats
- Long and short-term resource management
- Ideally there is enough depth for actuals "builds" and "combos"

### 2.5 Game Mechanics

- Items and Powerups
- Special Moves (on cooldown)
- Healing potion (on cooldown)
- ...

### 2.6 Progression, Challenge and Losing

- Defeat enemies, get XP, Level up
- Each level allows to advance a specific skill or stat
- Enemy difficulty increases slow during "story" and fast during "endless" mode
- ...
If all health is lost, the level will be reset and has to be started from the beginning (Zone progression stays).

### 2.7 Art Style and Music

2d Pixel-Art using the dawnbringer color palette. Most sprites are aimed to be 32x32 (pixels in image) and then displayed with a three-times scaling 96x96 (pixels on screen). Some are hand drawn but most of the characters, enemies, etc. will be open source artworks by various artists (see below).

<a name="technical"/>

# 3. Technical Description

### 3.1 Language and libraries

- C++ 17 (Compiler: MSVC 14.24, IDE: VS2019)
- [SDL2 v2.0.10](https://www.libsdl.org/index.php) : Cross-platform Graphics and IO library
- [SDL_image v2.0.5](https://www.libsdl.org/projects/SDL_image/) : Loads images as SDL surfaces and textures
- [SDL_ttf v2.0.15](https://www.libsdl.org/projects/SDL_ttf/) : Allows the use of TrueType fonts in SDL applications
- All the SDL/SDL_image/SDL_ttf dependencies

### 3.2 Architecture and Code Structure

The code is written in C++ 11 (and beyond) and in a object oriented manner. Simplicity (or rather: avoiding complexity) is a main goal. Well. Fingers crossed.

As stated, my basic approach of "i want to build a Engine" has changed for this project and the game/gameplay itself has top priority. Engine reusability, common Render-API, etc. were no factor when it came to the core design and left to SDL2 as much as possible. The result is a thigh coupled structure composed of four projects, that revolve around games resource management, game object creation, game state management, the Entity-Component-Sytem and feeding it all to SDL:
- <b>StoneCold.Base:</b> Basic Settings, common Types and Enums, Math and Exception classes
- <b>StoneCold.Engine:</b> Entity-Component-System, Game-State-Management and Event handling
- <b>StoneCold.Game:</b> Window creation, Levels/NPCs/Menu Setup, Manager init and main loop
- <b>StoneCold.Resources:</b> Resource management with Lifetime checks (loading and unloading)
- <b>StoneCold.Tests:</b> Unit Tests

The Engines core building blocks are the Entity–component–system (ECS) and the Game-State management. 

<a name="copyr"/>

# 4. Copyright and Attribution Notices

Some of the Textures are hand drawn (thanks MS Paint and Gimp) but all the nice looking ones are created by actual Artists:

- DawnBringer Color-Palette by Richard Fhager [link to his pixeljoint](http://pixeljoint.com/p/23821.htm)
- Dwarf Sprites by Elthen (Ahmet Avci) [link to his patreon](https://www.patreon.com/elthen)
- Skeleton Sprites by Jesse Munguia [link to his homepage](https://jessemunguia.com/)
- Mountain Background by NotTandy [link to his pixelart](https://www.pixilart.com/nottandy)
- UI Textures (RPG Pack) by Kenney Vleugels [link to his art](https://www.kenney.nl)
- Font Crom by russh (Russell Herschler) [link to his homepage](http://www.dragonfang.com/)
- Font OldeDethek by Pixel Sagas [link to the homepage](http://www.pixelsagas.com/)

<a name="work"/>

# 5. Workitems

### 5.1 Current tasks

- [ ] Update the Skeleton Texture (Weapon and colors)
- [ ] Pre-defined Monster/Player/MapTile/... data
- [ ] AI-Systems in the ECS (Check if Player is visible, close, ... and set flags)
- [ ] Player and Monster Actions: Melee Attack, Dodge, Special-Attack
- [ ] Player and Monster Status Components and Systems (Health, Damage, Armor, ...)
- [ ] Pathfinding AI (A*)

### 5.2 Backlog, cleanup and housekeeping

- [ ] Unit Tests ECS classes
- [ ] Unit Tests Vec2/Vec4 classes
- [ ] Unit Tests DecisionTree
- [ ] Render only Tiles visible by the Camera
- [ ] Map Texture overhaul (Use Color Palette, get the Walls and Wall-Tops right)
- [ ] Move States to the Game Project (and Managers to the Engine Project)
- [ ] Replace all SDL_Rects with Vec2/Vec4
- [ ] Static code analysis with "-Wall" "-Wextra"

### 5.3 Known Bugs

- [ ] libpng warning: iCCP: CRC error (On Texture loading)

### 5.4 Future features

- Add different Map-Generation algorithms (Rooms/Indoor, Caves)
- Add Portals and automatic Level-Loading (maybe Loading-Screen or transition effect)
- Add Player GUI (Lifebar, Action-Bar, Skill/Stat Window)
- Add Pickups and Buffs (Gold, Items, Chests)
- Add Controller Support (with automatic check if Controller is available)
- Add a basic Options Menu and Save/Load functionality 
- Add Sound and Music
