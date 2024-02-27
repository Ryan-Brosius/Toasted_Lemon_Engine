#include "Sprite.h"
#include "Game.h"
#include "BitmapManager.h"

extern Game* game;

Sprite::Sprite()
{
	sprite = nullptr;

    //Actual width and height of the sprite
    sprite_width = 0;
    sprite_height = 0;

    //Width and Height of the drawn sprite
	width = 0;
	height = 0;

    //Hotx Hoty of the sprite positon
	hot_x = 0;
	hot_y = 0;

    //Scale of the sprite
    scale_x = 1;
    scale_y = 1;

    //Rotation in degrees of sprite
    rotation = 0;

    //Important for spite sheets
    //If not a sprite sheet, will remain at zero
    sheet_offset = 0;
}

Sprite::~Sprite()
{}

void Sprite::init(const char* fileName)
{
    //Loads bitmap as a surface
	sprite = BitmapManager::LoadBitmap(fileName);

    //Sets the ACTUAL sprite width/height
    sprite_width = sprite->w;
    sprite_height = sprite->h;

    //Sets the config for animation / spritesheets
	width = sprite->w;
	height = sprite->h;
}

void Sprite::draw(SDL_Texture* targetTexture, int targetX, int targetY)
{
    //Need to calculate rotation information here
    double widthScale = width * scale_x;
    double heightScale = height * scale_y;
    int widthSize = static_cast<int>(widthScale);
    int heightSize = static_cast<int>(heightScale);

    int texturePitch = game->texturePitch;

    //double r_cos = SDL_cos(rotation);
    //double r_sin = SDL_sin(rotation);
    double r_cos = 1;
    double r_sin = 0;

    int centerX = width / 2;
    int centerY = height / 2;

    if ((targetX + widthScale) < 0 || (targetX - widthScale) > WIDTH) return;
    if ((targetY + heightScale) < 0 || (targetY - heightScale) > HEIGHT) return;

    Uint32* pixels = static_cast<Uint32*>(game->texturePixels);
    Uint32* spritePixels = static_cast<Uint32*>(sprite->pixels);

    double inv_scale_x = 1.0 / scale_x;
    double inv_scale_y = 1.0 / scale_y;

    for (int offsetY = 0; offsetY < heightSize; ++offsetY) {
        int texture_y = static_cast<int>((offsetY + targetY - (heightSize - heightScale) / 2)) * (texturePitch / 4);
        for (int offsetX = 0; offsetX < widthSize; ++offsetX) {

            //Choose the pixel location that the pixel will be blit to on screen
            int texture_x = offsetX + targetX - (widthSize - widthScale) / 2;
            int targetIndex = texture_x + texture_y;

            //Rotate the pixel back to the original sprite image, to get color information
            int x0 = offsetX - centerX * scale_x - (widthSize - widthScale) / 2;
            int y0 = offsetY - centerY * scale_y - (heightSize - heightScale) / 2;

            int x_rot = static_cast<int>(r_cos * x0 + r_sin * y0 + centerX * scale_x);
            int y_rot = static_cast<int>(-r_sin * x0 + r_cos * y0 + centerY * scale_y);

            //Prevents drawing errors due to rotation expanding
            if (x_rot < 0 || y_rot < 0 || y_rot * inv_scale_y >= height || x_rot * inv_scale_x >= width) continue; 

            //offset on spritesheets
            int spriteIndex = static_cast<int>(y_rot * inv_scale_y) * sprite_width + static_cast<int>(x_rot * inv_scale_x) + sheet_offset;

            //Pixel is being drawn off the intended locaion
            if (texture_x < 0 || texture_x > WIDTH || texture_y < 0) continue;

            Uint32 pixelColor = spritePixels[spriteIndex];

            //This is a transparent pixel
            if ((pixelColor & 0x00FFFFFF) == 0) continue;

            if (targetIndex >= 0 && targetIndex < texturePitch / 4 * HEIGHT) {
                Uint8 r, g, b;
                SDL_GetRGB(pixelColor, sprite->format, &r, &g, &b);
                pixels[targetIndex] = SDL_MapRGB(sprite->format, r, g, b);
            }
        }
    }
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

void Sprite::setSpriteSheet(int sprites)
{
    width = width / sprites;
}

void Sprite::setSheetOffset(int offset) {
    sheet_offset = offset * width;
}