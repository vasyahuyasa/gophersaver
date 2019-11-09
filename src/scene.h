#ifndef __SCENE_H__
#define __SCENE_H__

#include "render.h"

class Scene
{
public:
    Scene(Render *render) : render(render){};
    void update(int deltamillis);

private:
    Render *render;
};
#endif
