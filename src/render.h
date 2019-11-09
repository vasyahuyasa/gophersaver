#ifndef __RENDER_H__
#define __RENDER_H__

#include "SDL2/SDL.h"
#include <list>

class Renderable
{
public:
    virtual void render(SDL_Renderer *ren) = 0;
};

class Render
{
public:
    Render(SDL_Renderer *renderer) : renderer(renderer){};
    void update();
    void addRenderable(Renderable *renderable);

private:
    std::list<Renderable *> renderables;
    SDL_Renderer *renderer;
};
#endif
