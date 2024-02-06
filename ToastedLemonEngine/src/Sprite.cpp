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
}

Sprite::~Sprite()
{}

void Sprite::init(const char* fileName)
{
	sprite = BitmapManager::LoadBitmap(fileName);
	width = sprite->w;
	height = sprite->w;
}

double d_rotation = 0;

void Sprite::draw(SDL_Texture* targetTexture, int targetX, int targetY)
{
    if ((targetX + width) < 0 || (targetX - width) > WIDTH) return;

    if ((targetY + height) < 0 || (targetY - height) > HEIGHT) return;

    void* texturePixels;
    int texturePitch;
    SDL_LockTexture(targetTexture, NULL, &texturePixels, &texturePitch);

    Uint32* pixels = (Uint32*)texturePixels;
    Uint32*  spritePixels = (Uint32*)sprite->pixels;
    for (int offsetY = 0; offsetY < height*scale_y; ++offsetY) {
        for (int offsetX = 0; offsetX < width*scale_x; ++offsetX) {
            
            int current_x = offsetX;
            int current_y = offsetY;
            rotation(M_PI + d_rotation, &current_x, &current_y);
            d_rotation += 3.14 / (60 * 100000);
            current_x += targetX;
            current_y += targetY;

            //int targetIndex = (targetY + offsetY) * (texturePitch / 4) + targetX + (offsetX);


            //rotation(M_PI / 2, &current_x, &current_y);

            int targetIndex = current_y * (texturePitch / 4) + current_x;

            int spriteIndex = ((offsetY - (offsetY % scale_y)) / scale_y) * width +
                (((offsetX - (offsetX % scale_x)) / scale_x));

            //std::cout << "Length: " << targetX + (offsetX) << " Height: " << (targetY + offsetY) << std::endl;

            if (spritePixels[spriteIndex] == 4285822068) continue; //This is a transparent pixel

            if (targetIndex >= 0 && targetIndex < texturePitch / 4 * HEIGHT &&
                (targetX + offsetX) >= 0 && (targetX + offsetX) < WIDTH &&
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

void Sprite::rotation(double rotation, int* x, int* y) {
    //Rotates around center point of the sprite
    //x_not y_not
    int x0 = *x - (width / 2) * scale_x;
    int y0 = *y - (height / 2) * scale_y;
    int new_x = (int)SDL_round(cos(rotation) * x0 + sin(rotation) * y0);
    int new_y = (int)SDL_round(-1 * sin(rotation) * x0 + cos(rotation) * y0);

    *x = scale_x * (width / 2) + new_x;
    *y = scale_y * (height / 2) + new_y;
}

void Sprite::scale(int x_scale, int y_scale)
{
    scale_x = x_scale;
    scale_y = y_scale;
}