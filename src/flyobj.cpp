#include "gophersaver.h"
#include "stdio.h"
#include <cmath>

void FlyObj::draw(SDL_Renderer *ren)
{
    SDL_Rect dst = {(int)(this->pos.x - this->halfW), (int)(this->pos.y - this->halfH), this->w, this->h};
    SDL_RenderCopyEx(ren, this->tex, nullptr, &dst, this->angle, nullptr, SDL_FLIP_NONE);
}

void FlyObj::update(Uint32 deltamillis)
{
    this->updatePos(deltamillis);
    this->updateAngle(deltamillis);
}

void FlyObj::updatePos(Uint32 deltamillis)
{
    this->pos.x += this->vel.x * (float)deltamillis / 1000.0;
    this->pos.y += this->vel.y * (float)deltamillis / 1000.0;
}

void FlyObj::updateAngle(Uint32 deltamillis)
{
    this->angle += this->rotate * (float)deltamillis / 1000.0;

    if (this->angle < 0)
    {
        this->angle = 360.0f - this->angle;
    }

    if (this->angle >= 360.0f)
    {
        this->angle = this->angle - 360.0f;
    }
}