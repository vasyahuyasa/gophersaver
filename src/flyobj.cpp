#include "gophersaver.h"
#include "stdio.h"

void FlyObj::draw(SDL_Renderer *ren)
{
    SDL_Rect dst = {(int)(this->pos.x - this->halfW), (int)(this->pos.y - this->halfH), this->w, this->h};
    SDL_RenderCopy(ren, this->tex, nullptr, &dst);

    printf("draw %f %f\n", pos.x, pos.y);
}

void FlyObj::update(Uint32 deltamillis)
{
    this->pos.x += this->vel.x * (float)deltamillis / 1000.0;
    this->pos.y += this->vel.y * (float)deltamillis / 1000.0;
}