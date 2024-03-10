#include "InputMap.h"
#include "SDL.h"

InputMap::InputMap() {};

void InputMap::init() 
{
	addKeyboardMaping("player_up");
	addKeyboardMaping("player_down");
	addKeyboardMaping("player_left");
	addKeyboardMaping("player_right");
	addKeyboardMaping("QUIT_GAME");
};

void InputMap::getInput()
{
    //reset map
    for (const auto& pair : input) {
        input[pair.first] = 0;
    }


    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]) {
        input["player_up"] = 1;
    }

    if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]) {
        input["player_down"] = 1;
    }

    if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
        input["player_left"] = 1;
    }

    if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
        input["player_right"] = 1;
    }

    // Handle other events like SDL_QUIT separately
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            input["QUIT_GAME"] = 1;
        }
    }
}

bool InputMap::getAction(std::string action) 
{
	return input[action];
};

void InputMap::addKeyboardMaping(std::string action) 
{
	input[action] = 0;
};