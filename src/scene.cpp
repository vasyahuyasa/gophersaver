#include "render.h"

class Scene
{
public:
    Scene(Render *render) : render(render){};

private:
    Render *render;
};
