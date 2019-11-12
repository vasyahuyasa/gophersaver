#ifndef __STATICSPRITE_H__
#define __STATICSPRITE_H__

#include "SDL2/SDL.h"
#include "render.h"

class StaticSprite : Drawable
{
private:
    SDL_Texture *tex;
    int w, h;
    SDL_Point pos;

public:
    StaticSprite(SDL_Texture *texture, int width, int height, SDL_Point position) : tex(texture), w(width), h(height), pos(position){};

    void draw(SDL_Renderer *ren) override;
};

#endif