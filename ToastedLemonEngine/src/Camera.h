#pragma once
class Camera
{
public:
	Camera();
	void init(int xpos, int ypos, int width, int height);
	void update(int xpos, int ypos);

	int getX();
	int getY();

	void setMapSize(int width, int height);
private:
	//POSITION OF THE CAMERA
	int xpos;
	int ypos;

	//SIZE OF THE MAP
	int width;
	int height;
};

