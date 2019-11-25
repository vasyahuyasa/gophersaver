#ifndef __RENDER_H__
#define __RENDER_H__

#include "gophersaver.h"
#include <list>

namespace gopher
{
class Drawable
{
public:
    virtual void draw(SDL_Renderer *ren) = 0;
};

class Render
{
public:
    Render(SDL_Renderer *ren) : renderer(ren){};
    void draw();
    void addRenderable(Drawable *renderable);

private:
    std::list<Drawable *> drawables;
    SDL_Renderer *renderer;
};
} // namespace gopher

#endif
