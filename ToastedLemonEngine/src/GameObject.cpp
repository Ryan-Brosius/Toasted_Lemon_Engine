#include "GameObject.h"

GameObject::GameObject()
{
	xpos = 0;
	ypos = 0;
	rotation = 0;
	x_scale = 1;
	y_scale = 1;
}

GameObject::GameObject(double x, double y, double rot, double width, double height)
{
	xpos = (x == NULL) ? 0 : x;
	ypos = (y == NULL) ? 0 : y;
	rotation = (rot == NULL) ? 0 : rot;
	x_scale = (width == NULL) ? 1 : width;
	y_scale = (height == NULL) ? 1 : height;
}

GameObject::~GameObject() {}

void GameObject::Update() {}

void GameObject::Render(SDL_Texture* framebuffer) {}

void GameObject::setPosition(double x, double y) 
{
	xpos = x;
	ypos = y;
}

void GameObject::setRotation(double rot)
{
	rotation = rot;
}

void GameObject::setScale(int w, int h)
{
	x_scale = w;
	y_scale = h;
}