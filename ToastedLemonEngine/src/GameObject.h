#pragma once
#include "Game.h"
#include "Animation.h"
#include "Audio.h"
#include "InputMap.h"

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

	void getPosition(double* posBuffer);

	int getX();
	int getY();
protected:
	//Double for pos so you can use time.deltatime
	//When rendering, should convert to int
	double xpos;
	double ypos;

	int renderxpos;
	int renderypos;

	double rotation;
	int x_scale;
	int y_scale;

	int UID;

};


//Player gameobject
class Player : public GameObject
{
public:
	Animation* player_right = nullptr;
	Animation* player_up = nullptr;
	Animation* player_down = nullptr;
	Animation* player_left = nullptr;
	Animation* currentAnimation = nullptr;
	Audio* audio = nullptr;
	int bgmLength = 0;
	double bgmTimer = 0;
	InputMap* input = game->input;
	bool moving = 0;

	int animEnum = 0;
	enum animation
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	Player(double xpos, double ypos, double rotation, double x_scale, double y_scale) :
		GameObject(xpos, ypos, rotation, x_scale, y_scale)
	{
		renderxpos = 0;
		renderypos = 0;
	}

	void init()
	{
		// Creating audio object
		audio = new Audio();
		audio->PlayAudio("Pop.wav", 0);

		player_right = new Animation();
		player_right->init("Assets/Sprites/sp_link_right.bmp", 2, 0.2);

		player_up = new Animation();
		player_up->init("Assets/Sprites/sp_link_backwards.bmp", 2, 0.2);

		player_down = new Animation();
		player_down->init("Assets/Sprites/sp_link_forward.bmp", 2, 0.2);

		player_left = new Animation();
		player_left->init("Assets/Sprites/sp_link_left.bmp", 2, 0.2);

		currentAnimation = player_right;

		bgmLength = audio->PlayAudio("TheFinalOfTheFantasy.wav", 1);
	}

	void Update()
	{
		renderxpos = (int)(xpos - game->camera->getX());
		renderypos = (int)(ypos - game->camera->getY());
		moving = false;

		bgmTimer += game->deltaTime();
		if (bgmTimer >= bgmLength) {
			audio->StopAudio("TheFinalOfTheFantasy.wav");
			audio->PlayAudio("TheFinalOfTheFantasy.wav", 0);
			bgmTimer = 0;
		}

		if (input->getAction("player_up"))
		{
			ypos -= 100 * game->deltaTime();
			currentAnimation = player_up;
			animEnum = UP;
			moving = true;
		}
		if (input->getAction("player_down"))
		{
			ypos += 100 * game->deltaTime();
			currentAnimation = player_down;
			animEnum = DOWN;
			moving = true;
		}
		if (input->getAction("player_right"))
		{
			xpos += 100 * game->deltaTime();
			currentAnimation = player_right;
			animEnum = RIGHT;
			moving = true;
		}
		if (input->getAction("player_left"))
		{
			xpos -= 100 * game->deltaTime();
			currentAnimation = player_left;
			animEnum = LEFT;
			moving = true;
		}

		if (!moving) {
			currentAnimation->setAnimating(false);
			audio->StopAudio("RustlingGrass.wav");
		}
		else {
			currentAnimation->setAnimating(true);
			audio->PlayAudio("RustlingGrass.wav", 0);
		}

		currentAnimation->update();
	}

	void Clean() {
		audio->StopAudio("TheFinalOfTheFantasy.wav");
		audio->~Audio();
	}

	void Render(SDL_Texture* framebuffer)
	{
		Sprite* s = currentAnimation->getSprite();
		s->setRotation(rotation);
		s->scale(x_scale, y_scale);
		currentAnimation->draw(framebuffer, renderxpos, renderypos);
	}

	void SetUID(int id)
	{
		UID = id;
	}

	int GetUID()
	{
		return UID;
	}

	void setAnimation(int animation, double localtime, int animating)
	{
		switch (animation)
		{
		case UP:
			currentAnimation = player_up;
			break;
		case DOWN:
			currentAnimation = player_down;
			break;
		case RIGHT:
			currentAnimation = player_right;
			break;
		case LEFT:
			currentAnimation = player_left;
			break;
		default:
			break;
		}

		currentAnimation->setLocalTime(localtime);
		currentAnimation->setAnimating(animating);
		currentAnimation->update();
	}

	void setRenderPos(int renderX, int renderY)
	{
		renderxpos = renderX;
		renderypos = renderY;
	}
};


