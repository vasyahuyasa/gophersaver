#ifndef __SCENE_H__
#define __SCENE_H__

#include "render.h"
#include "physics.h"

namespace gopher
{
class Scene
{
public:
    Scene(Render *render, Physics *physics) : ren(render), phys(physics), lastmillis(SDL_GetTicks()){};
    bool update();

private:
    Render *ren;
    Physics *phys;
    Uint32 lastmillis;
    int mouseX;
    int mouseY;
    Uint32 mouseInputMask;

    void readMouseState();
    bool canContinue();
};
} // namespace gopher
#endif
