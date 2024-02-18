#include "Sprite.h"
#include "Game.h"
#include "BitmapManager.h"

Sprite::Sprite()
{
	sprite = nullptr;
	width = 0;
	height = 0;
	hot_x = 0;
	hot_y = 0;
    scale_x = 1;
    scale_y = 1;
    rotation = 0;
}

Sprite::~Sprite()
{}

void Sprite::init(const char* fileName)
{
	sprite = BitmapManager::LoadBitmap(fileName);
	width = sprite->w;
	height = sprite->w;
}


//Wow whoever wrote this should get fired
//TODO: clean up this code so I don't cry when I look at it
void Sprite::draw(SDL_Texture* targetTexture, int targetX, int targetY)
{
    //Need to calculate rotation information here
    double widthScale = width * scale_x;
    double heightScale = height * scale_y;

    double r_cos = SDL_cos(rotation);
    double r_sin = SDL_sin(rotation);
    
    //Fix this later to only create size needed
    int widthSize = widthScale * 2;
    int heightSize = heightScale * 2;

    int centerX = width / 2;
    int centerY = height / 2;

    if ((targetX + widthScale) < 0 || (targetX - widthScale) > WIDTH) return;
    if ((targetY + heightScale) < 0 || (targetY - heightScale) > HEIGHT) return;

    void* texturePixels;
    int texturePitch;
    SDL_LockTexture(targetTexture, NULL, &texturePixels, &texturePitch);

    Uint32* pixels = (Uint32*)texturePixels;
    Uint32*  spritePixels = (Uint32*)sprite->pixels;
    for (int offsetY = 0; offsetY < widthSize; ++offsetY) {
        for (int offsetX = 0; offsetX < heightSize; ++offsetX) {
            
            //Choose the pixel location that the pixel will be blit to on screen
            int texture_x = offsetX + targetX - (widthSize - widthScale) / 2;
            int texture_y = ((offsetY + targetY) - (heightSize - heightScale) / 2) * (texturePitch / 4);
            int targetIndex = texture_x + texture_y;
            
            //Rotate the pixel back to the original sprite image, to get color information
            int x0 = offsetX - (width / 2) * scale_x - (widthSize - widthScale)/2;
            int y0 = offsetY - (height / 2) * scale_y - (heightSize - heightScale)/2;

            int x_rot = r_cos * x0 + r_sin * y0 + (centerX * scale_x);
            int y_rot = -r_sin * x0 + r_cos * y0 + (centerY * scale_y);

            if (x_rot < 0 || y_rot < 0 || (y_rot / scale_y) >= height || (x_rot / scale_x) >= width) continue;  //Prevents drawing errors due to rotation expanding

            int spriteIndex = (y_rot / scale_y) * width + (x_rot / scale_x);

            if (texture_x < 0 || texture_x > WIDTH || texture_y < 0) continue;  //Pixel is being drawn off the intended locaion

            if (spritePixels[spriteIndex] == 4285822068) continue; //This is a transparent pixel

            if (targetIndex >= 0 && targetIndex < texturePitch / 4 * HEIGHT &&
                spriteIndex >= 0 && spriteIndex < width * height) {
                Uint32 pixelColor = spritePixels[spriteIndex];
                Uint8 r, g, b;
                SDL_GetRGB(pixelColor, sprite->format, &r, &g, &b);

                pixels[targetIndex] = SDL_MapRGB(sprite->format, r, g, b);
            }
        }
    }

    SDL_UnlockTexture(targetTexture);
}

void Sprite::scale(int x_scale, int y_scale)
{
    scale_x = x_scale;
    scale_y = y_scale;
}

void Sprite::setRotation(double rot)
{
    rotation = rot * (M_PI / 180);
}

double Sprite::getRotation()
{
    return rotation * (180.0 / M_PI);
}