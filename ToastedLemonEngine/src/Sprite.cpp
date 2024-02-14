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

double d_rotation = 0;


//Wow whoever wrote this should get fired
//TODO: clean up this code so I don't cry when I look at it
void Sprite::draw(SDL_Texture* targetTexture, int targetX, int targetY)
{
    //Need to calculate rotation information here
    double widthScale = width * scale_x;
    double heightScale = height * scale_y;

    double r_cos = SDL_cos(rotation);
    double r_sin = SDL_sin(rotation);

    int widthSize = (int) (widthScale * r_cos + heightScale * r_sin);
    int heightSize = (int) (widthScale * r_sin + heightScale * r_cos);

    widthSize = widthScale * 2;
    heightSize = heightScale * 2;

    if ((targetX + width) < 0 || (targetX - width) > WIDTH) return;
    if ((targetY + height) < 0 || (targetY - height) > HEIGHT) return;

    void* texturePixels;
    int texturePitch;
    SDL_LockTexture(targetTexture, NULL, &texturePixels, &texturePitch);

    Uint32* pixels = (Uint32*)texturePixels;
    Uint32*  spritePixels = (Uint32*)sprite->pixels;
    for (int offsetY = 0; offsetY < widthSize; ++offsetY) {
        for (int offsetX = 0; offsetX < heightSize; ++offsetX) {
            
            int current_x = offsetX;
            int current_y = offsetY;

            current_x += targetX;
            current_y += targetY;

            int centerX = width / 2;
            int centerY = height / 2;

            rotation += 3.14 / (60 * 100000);

            // std::cout << temp_x << " " << temp_y << std::endl;
            //exit(1);

            int targetIndex = current_y * (texturePitch / 4) + current_x;

            //int targetIndex = current_y * (texturePitch / 4) + current_x;

            //int spriteIndex = ((offsetY - (offsetY % scale_y)) / scale_y) * width +
             //  (((offsetX - (offsetX % scale_x)) / scale_x));
            int x0 = offsetX - (width / 2) * scale_x - (widthSize - widthScale)/2;
            int y0 = offsetY - (height / 2) * scale_y - (heightSize - heightScale)/2; //lol fix this 53 shit later

     

            int temp_x = r_cos * x0 + r_sin * y0;
            int temp_y = -r_sin * x0 + r_cos * y0;

            temp_x += (width / 2) * scale_x;
            temp_y += (height / 2) * scale_y;

            if (temp_x < 0 || temp_y < 0 || (temp_y / scale_y) >= height || (temp_x / scale_x) >= width) continue;

            int spriteIndex = (temp_y / scale_y) * width + (temp_x / scale_x);

            if (spriteIndex < 0 || spriteIndex > width * height) continue;

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

//void Sprite::rotation(double rotation, int* x, int* y) {
//    //Rotates around center point of the sprite
//    //x_not y_not
//    double x0 = *x - (width / 2.0) * scale_x;
//    double y0 = *y - (height / 2.0) * scale_y;
//
//    double r_sin = sin(rotation);
//    double r_cos = cos(rotation);
//
//    double new_x = r_cos * x0 + r_sin * y0;
//    double new_y = -r_sin * x0 + r_cos * y0;
//
//    *x = (int)(scale_x * (width / 2.0) + round(new_x));
//    *y = (int)(scale_y * (height / 2.0) + round(new_y));
//}

void Sprite::scale(int x_scale, int y_scale)
{
    scale_x = x_scale;
    scale_y = y_scale;
}