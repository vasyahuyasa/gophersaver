#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "SDL2/SDL.h"
#include <list>

namespace gopher
{
class Physent
{
public:
    int w, h;
    SDL_FPoint pos;
    SDL_FPoint vel; // move speed pixel per second

    virtual void update(Uint32 deltamillis) = 0;
};

class Physics
{
private:
    std::list<Physent *> physents;
    int w, h;

    void updateVelocity(Physent *physent);

public:
    Physics(int width, int height) : w(width), h(height){};

    void update(Uint32 deltamillis);
    void addPhysent(Physent *physent);
};
} // namespace gopher

#endif
