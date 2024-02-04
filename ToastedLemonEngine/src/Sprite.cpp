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
}

Sprite::~Sprite()
{}

void Sprite::init(const char* fileName)
{
	sprite = BitmapManager::LoadBitmap(fileName);
	width = sprite->w;
	height = sprite->w;
}

void Sprite::draw(SDL_Texture* targetTexture, int targetX, int targetY)
{
    if ((targetX + width) < 0 || (targetX - width) > WIDTH) return;

    if ((targetY + height) < 0 || (targetY - height) > HEIGHT) return;

    void* texturePixels;
    int texturePitch;
    SDL_LockTexture(targetTexture, NULL, &texturePixels, &texturePitch);

    Uint32* pixels = (Uint32*)texturePixels;
    Uint32*  spritePixels = (Uint32*)sprite->pixels;
    for (int offsetY = 0; offsetY < height; ++offsetY) {
        for (int offsetX = 0; offsetX < width; ++offsetX) {

            //If pixel is off screen, dont draw it
            if (targetX + offsetX >= WIDTH || targetX + offsetX < 0)
                continue;
            if (targetY + offsetY >= HEIGHT || targetY + offsetY < 0)
                continue;

            int targetIndex = (targetY + offsetY) * (texturePitch / 4) + (targetX + offsetX);
            int spriteIndex = offsetY * width + offsetX;

            Uint32 pixelColor = spritePixels[spriteIndex];
            Uint8 r, g, b;
            SDL_GetRGB(pixelColor, sprite->format, &r, &g, &b);

            pixels[targetIndex] = SDL_MapRGB(sprite->format, r, g, b);
        }
    }

    SDL_UnlockTexture(targetTexture);
}