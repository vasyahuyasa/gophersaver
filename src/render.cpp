#include "render.h"

void Render::update()
{
    for (auto renderable : renderables)
    {
        renderable->render(renderer);
    }
}

void Render::addRenderable(Renderable *renderable)
{
    renderables.push_back(renderable);
}