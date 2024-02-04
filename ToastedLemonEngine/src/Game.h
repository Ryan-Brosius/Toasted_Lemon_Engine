#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>

#define WIDTH 800
#define HEIGHT 600

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handelEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};
