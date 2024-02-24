#pragma once
#include "Game.h"
#include "Animation.h"

extern Game* game;

class GameObject
{
public:
	GameObject(double xpos, double ypos, double rotation, double x_scale, double y_scale);
	GameObject();
	~GameObject();
	
	void Update();							//Abstract Function
	void Render(SDL_Texture* framebuffer);	//Abstract Function

	void setPosition(double x, double y);
	void setRotation(double rotation);
	void setScale(int width, int height);

protected:
	//Double for pos so you can use time.deltatime
	//When rendering, should convert to int
	double xpos;
	double ypos;

	double rotation;
	int x_scale;
	int y_scale;

};


//Player gameobject
class Player : public GameObject
{
public:
	Animation* player_right = nullptr;
	Animation* player_up = nullptr;
	Animation* player_down = nullptr;
	Animation* currentAnimation = nullptr;


	Player(double xpos, double ypos, double rotation, double x_scale, double y_scale) :
		GameObject(xpos, ypos, rotation, x_scale, y_scale) {}
	
	void init()
	{
		player_right = new Animation();
		player_right->init("Assets/Sprites/sp_link_right.bmp", 2, 0.2);

		player_up = new Animation();
		player_up->init("Assets/Sprites/sp_link_backwards.bmp", 2, 0.2);

		player_down = new Animation();
		player_down->init("Assets/Sprites/sp_link_forward.bmp", 2, 0.2);

		currentAnimation = player_right;
	}

	void Update()
	{
		const Uint8* keys = SDL_GetKeyboardState(NULL);

		if (keys[SDL_SCANCODE_UP])
		{
			ypos -= 100 * game->deltaTime();
			currentAnimation = player_up;
		}
		if (keys[SDL_SCANCODE_DOWN])
		{
			ypos += 100 * game->deltaTime();
			currentAnimation = player_down;
		}
		if (keys[SDL_SCANCODE_RIGHT])
		{
			xpos += 100 * game->deltaTime();
			currentAnimation = player_right;
		}
		if (keys[SDL_SCANCODE_LEFT])
			xpos -= 100 * game->deltaTime();

		if (!keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT] && !keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_DOWN])
			currentAnimation->setAnimating(false);
		else
			currentAnimation->setAnimating(true);

		currentAnimation->update();

	}

	void Render(SDL_Texture* framebuffer)
	{
		Sprite* s = currentAnimation->getSprite();
		s->setRotation(rotation);
		s->scale(x_scale, y_scale);
		currentAnimation->draw(framebuffer, (int)xpos, (int)ypos);
	}
};