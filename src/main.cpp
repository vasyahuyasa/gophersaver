#include "gophersaver.h"
#include "stdio.h"
#include "unistd.h"

/*
void update(Sprite *sprite)
{
    SDL_PumpEvents();
    if (SDL_GetMouseState(&sprite->x, &sprite->y) & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        exit(EXIT_SUCCESS);
    }
}
*/

/*
void render(SDL_Renderer *ren, Sprite *sprite)
{
    SDL_Rect dst = {sprite->x, sprite->y, 100, 100};

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, sprite->texture, nullptr, &dst);
    SDL_RenderPresent(ren);
    SDL_Delay(10);
}
*/

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

    FlyObj *fly = new FlyObj(tex, 100, 100, SDL_FPoint{0.5, 0.5}, SDL_FPoint{100, 100});
    render->addRenderable(fly);
    physics->addPhysent(fly);

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
