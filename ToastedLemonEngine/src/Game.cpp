#include "Game.h"
#include "BitmapManager.h"
#include "Sprite.h"
#include "Animation.h"
#include "GameObject.h"
#include "TilesheetMap.h"

//Testing creating sprites
Player* player = nullptr;
TilesheetMap* map = nullptr;

Game::Game()
{
	isRunning = false;
	window = nullptr;
	renderer = nullptr;
	frame_buffer1 = nullptr;
	frame_buffer2 = nullptr;

	lastUpdate = 0;
	currentUpdate = 0;
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
			SDL_RENDERER_ACCELERATED);
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

	//Create mah frame buffers
	frame_buffer1 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 800, 600);
	frame_buffer2 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 800, 600);
	SDL_SetTextureBlendMode(frame_buffer1, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(frame_buffer2, SDL_BLENDMODE_BLEND);
	
	//creating sprite here
	player = new Player(NULL, NULL, NULL, 3, 3);
	player->init();
	map = new TilesheetMap();
}

void* Game::createNetworkPlayer(int newPlayerUID)
{
	Player* netPlayer;

	netPlayer = new Player(NULL, NULL, NULL, 3, 3);
	netPlayer->init();
	netPlayer->SetUID(newPlayerUID);
	netPlayer->Render(frame_buffer1);
	std::cout << "New player spawned" << "\n";
	return netPlayer;
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

	//DeltaTime Setup
	//Prob should be moved in a different area later????
	lastUpdate = currentUpdate;
	currentUpdate = SDL_GetTicks();

	//Gameobject Testing
	player->Update();
}


void Game::render()
{
	//frame_buffer is texture that gets wrapped around the screen
	//so we can manually edit the pixels on it
	SDL_SetRenderTarget(renderer, frame_buffer1);
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	//Clears texture

	void* pixels;
	int pitch;
	SDL_LockTexture(frame_buffer1, NULL, &pixels, &pitch);
	memset(pixels, 0, pitch * HEIGHT);
	SDL_UnlockTexture(frame_buffer1);

	SDL_RenderClear(renderer);
	
	SDL_LockTexture(frame_buffer1, NULL, &texturePixels, &texturePitch);

	//draw player sprite
	//will be changed with container of all sprites in the future :)
	map->DrawMap(frame_buffer1);
	player->Render(frame_buffer1);

	SDL_UnlockTexture(frame_buffer1);


	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, frame_buffer1, NULL, NULL);

	SDL_RenderPresent(renderer);

	SDL_Texture* temp = frame_buffer1;
	frame_buffer1 = frame_buffer2;
	frame_buffer2 = temp;
}

void Game::clean()
{
	//TODO: I love throwing my memory into the void
	player->Clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game Cleared" << std::endl;
}

double Game::deltaTime()
{
	return ((double)currentUpdate - lastUpdate) / 1000.0;
}