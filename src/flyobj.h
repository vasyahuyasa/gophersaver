#ifndef __FLYOBJ_H__
#define __FLYOBJ_H__

#include "SDL2/SDL.h"
#include "render.h"
#include "physics.h"

class FlyObj : public Renderable, public Physent
{
private:
    SDL_Texture *tex;
    int halfW, halfH;

public:
    FlyObj(SDL_Texture *texture, int width, int height, SDL_FPoint velocity, SDL_FPoint startPos) : tex(texture), halfW(width / 2), halfH(height / 2)
    {
        this->pos = startPos;
        this->w = width;
        this->h = height;
        this->vel = velocity;
    };

    void draw(SDL_Renderer *ren) override;
    void update(Uint32 deltamillis) override;
};

#endif
