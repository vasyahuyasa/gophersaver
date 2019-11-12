#include "gophersaver.h"

void Render::draw()
{
    SDL_RenderClear(renderer);

    for (auto renderable : renderables)
    {
        renderable->draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Render::addRenderable(Renderable *renderable)
{
    renderables.push_back(renderable);
}
