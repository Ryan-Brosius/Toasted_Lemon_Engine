#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <map>
#include "Camera.h"
class Player;

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

	void* createNetworkPlayer(int newPlayerUID);

	void GetPlayerPosition(double* posBuffer);

	void moveNetPlayer(int UID, double xpos, double ypos);
	
	//Rendering
	void* texturePixels;
	int texturePitch;
	Camera* camera;

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* frame_buffer1;
	SDL_Texture* frame_buffer2;

	//Used to get deltaTime
	Uint32 lastUpdate;
	Uint32 currentUpdate;

	//Map of networked players to gameobjects
	std::map<int, Player*> networkMap;
};

