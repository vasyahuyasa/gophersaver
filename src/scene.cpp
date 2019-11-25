#include "gophersaver.h"
#include "stdio.h"

namespace gopher
{
bool Scene::update()
{
    Uint32 deltamillis = SDL_GetTicks() - this->lastmillis;

    this->readMouseState();

    if (!this->canContinue())
    {
        return false;
    }

    this->phys->update(deltamillis);
    this->ren->draw();

    this->lastmillis = SDL_GetTicks();

    return true;
}

void Scene::readMouseState()
{
    SDL_PumpEvents();
    this->mouseInputMask = SDL_GetMouseState(&this->mouseX, &this->mouseY);
}

bool Scene::canContinue()
{
    return (this->mouseInputMask & SDL_BUTTON_LMASK) == 0;
}
}