#include "Game.h"
#include "BitmapManager.h"
#include "Sprite.h"

//Testing creating sprites
Sprite* player = nullptr;

Game::Game()
{
	isRunning = false;
	window = nullptr;
	renderer = nullptr;
}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL Environment Initialized..." << std::endl;

		window = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			flags | SDL_WINDOW_SHOWN);
		if (window); std::cout << "Window Initialized..." << std::endl;

		renderer = SDL_CreateRenderer(
			window,
			-1,
			0);
		if (renderer) {
			std::cout << "Renderer Initialized..." << std::endl;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	
	//creating sprite here
	player = new Sprite();
	player->init("link.bmp");
}

void Game::handelEvents()
{
	//TODO: Add Event Handling

	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}

void Game::update()
{
	//TODO: allow "gameobjects" to use update
}


void Game::render()
{
	//frame_buffer is texture that gets wrapped around the screen
	//so we can manually edit the pixels on it
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_Texture* frame_buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 800, 600);

	player->draw(frame_buffer, 200, 200);
	player->draw(frame_buffer, 200, 400);
	player->draw(frame_buffer, 790, 400);
	player->draw(frame_buffer, 550, 590);


	SDL_RenderClear(renderer);

	SDL_UpdateWindowSurface(window);

	SDL_RenderCopy(renderer, frame_buffer, NULL, NULL);

	SDL_RenderPresent(renderer);

	SDL_DestroyTexture(frame_buffer);
}

void Game::clean()
{
	//TODO: I love throwing my memory into the void

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game Cleared" << std::endl;
}