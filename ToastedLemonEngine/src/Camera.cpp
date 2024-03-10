#include "Camera.h"

Camera::Camera()
{
	xpos = 0;
	ypos = 0;
	width = 0;
	height = 0;
}

void Camera::init(int x, int y, int w, int h)
{
	xpos = x;
	ypos = y;
	width = w;
	height = h;
}

void Camera::update(int x, int y)
{
	xpos = x;
	ypos = y;

	if (xpos < 0)
		xpos = 0;
	if (ypos < 0)
		ypos = 0;
	if (xpos > width)
		xpos = width;
	if (ypos > height)
		ypos = height;
}

int Camera::getX()
{
	return xpos;
}

int Camera::getY()
{
	return ypos;
}

void Camera::setMapSize(int w, int h)
{
	width = w;
	height = h;
}