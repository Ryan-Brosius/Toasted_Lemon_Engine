#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

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

	double deltaTime();

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	SDL_Texture* frame_buffer1;
	SDL_Texture* frame_buffer2;

	Uint32 lastUpdate;
	Uint32 currentUpdate;
};

