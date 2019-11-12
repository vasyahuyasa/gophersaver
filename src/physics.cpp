#include "physics.h"

void Physics::update(Uint32 deltamillis)
{
    for (auto physent : this->physents)
    {
        physent->update(deltamillis);
        this->updateVelocity(physent);
    }
}

void Physics::addPhysent(Physent *physent)
{
    this->physents.push_back(physent);
}

void Physics::updateVelocity(Physent *physent)
{
    bool inverseX = false, inverseY = false;

    if ((physent->pos.x - (physent->w / 2)) < 0)
    {
        physent->pos.x = physent->w / 2;
        inverseX = physent->vel.x < 0;
    }

    if ((physent->pos.x + (physent->w / 2)) > this->w)
    {
        physent->pos.x = this->w - (physent->w / 2);
        inverseX = physent->vel.x > 0;
    }

    if ((physent->pos.y - (physent->h / 2)) < 0)
    {
        physent->pos.y = physent->h / 2;
        inverseY = physent->vel.y < 0;
    }

    if ((physent->pos.y + (physent->h / 2)) > this->h)
    {
        physent->pos.y = this->h - (physent->h / 2);
        inverseY = physent->vel.y > 0;
    }

    if (inverseX)
    {
        physent->vel.x *= -1;
    }

    if (inverseY)
    {
        physent->vel.y *= -1;
    }
}