#ifndef __RENDER_H__
#define __RENDER_H__

#include "gophersaver.h"
#include <list>

class Renderable
{
public:
    virtual void draw(SDL_Renderer *ren) = 0;
};

class Render
{
public:
    Render(SDL_Renderer *ren) : renderer(ren){};
    void draw();
    void addRenderable(Renderable *renderable);

private:
    std::list<Renderable *> renderables;
    SDL_Renderer *renderer;
};
#endif
