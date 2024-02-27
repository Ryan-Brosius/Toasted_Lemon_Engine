# Toasted Lemon Engine

![alt text](https://i.imgur.com/KeG8zxb.png)

Toasted Lemon Engine is an early-stage game engine built for Windows. The sole purpose is to design an engine to support creating old RPG classics like the Legend of Zelda, Dragon Quest, Crono-trigger, Final Fantasy, and more!

## Getting Started

Visual Studio 2022 is recommended, Toasted Lemon Engine is currently untested on other development builds.

**1. Download the Repository**
```bash
git clone --recursive https://github.com/Ryan-Brosius/Toasted_Lemon_Engine
```
**2. Configuring the dependencies:**\
All dependencies should be linked once you pull the repo. If you are getting errors for ``SDL2.dll not found`` move the SDL2.dll into your build directory. This should fix all issues.

## The Plan
The plan for Toasted Lemon Engine is to create a powerful 2D rendering engine that supports a wide variety of features that would be useful for these types of games. On top of this, it serves as a tool to teach us *(the developers)* game design, game engine architecture, game engine techniques, and much more! 

### Main features of our engine:
- Fast 2D rendering (Sprites, UI, etc)
- Animation Engine
- Audio System
- Collision Detection
- Networking