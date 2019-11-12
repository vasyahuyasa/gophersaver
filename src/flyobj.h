#ifndef __FLYOBJ_H__
#define __FLYOBJ_H__

#include "SDL2/SDL.h"
#include "render.h"
#include "physics.h"

class FlyObj : public Drawable, public Physent
{
private:
    SDL_Texture *tex;
    int halfW, halfH;
    double angle;
    double rotate; // degrees per second

    void updatePos(Uint32 deltamillis);
    void updateAngle(Uint32 deltamillis);

public:
    FlyObj(SDL_Texture *texture, int width, int height, SDL_FPoint velocity, SDL_FPoint startPos, double rot) : tex(texture), halfW(width / 2), halfH(height / 2), angle(0), rotate(rot)
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
