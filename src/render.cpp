#include "gophersaver.h"
namespace gopher
{
void Render::draw()
{
    SDL_RenderClear(renderer);

    for (auto drawable : drawables)
    {
        drawable->draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Render::addRenderable(Drawable *drawable)
{
    drawables.push_back(drawable);
}
} // namespace gopher
