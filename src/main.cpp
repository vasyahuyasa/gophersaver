#include "gophersaver.h"
#include "stdio.h"
#include "unistd.h"

const int width = 1500;
const int height = 1000;

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        printf("SDL_CreateRenderer Error %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Surface *bmp = SDL_LoadBMP("grumpy-cat.bmp");
    if (bmp == nullptr)
    {
        printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == nullptr)
    {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    Physics *physics = new Physics(width, height);
    Render *render = new Render(ren);
    Scene *scene = new Scene(render, physics);

    FlyObj *fly1 = new FlyObj(tex, 100, 100, SDL_FPoint{500, 500}, SDL_FPoint{100, 100}, 30);
    FlyObj *fly2 = new FlyObj(tex, 100, 100, SDL_FPoint{400, -500}, SDL_FPoint{200, 200}, 50);
    FlyObj *fly3 = new FlyObj(tex, 100, 100, SDL_FPoint{300, 700}, SDL_FPoint{300, 300}, 150);
    FlyObj *fly4 = new FlyObj(tex, 100, 100, SDL_FPoint{-500,-3400}, SDL_FPoint{400, 400}, 50);
    FlyObj *fly5 = new FlyObj(tex, 100, 100, SDL_FPoint{100, -200}, SDL_FPoint{500, 500}, 50);

    render->addRenderable(fly1);
    render->addRenderable(fly2);
    render->addRenderable(fly3);
    render->addRenderable(fly4);
    render->addRenderable(fly5);

    physics->addPhysent(fly1);
    physics->addPhysent(fly2);
    physics->addPhysent(fly3);
    physics->addPhysent(fly4);
    physics->addPhysent(fly5);

    bool running = true;

    while (running)
    {
        running = scene->update();
        SDL_Delay(10);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return EXIT_SUCCESS;
}
