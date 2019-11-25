#include "gophersaver.h"
#include "stdio.h"
#include "unistd.h"
#include "assets/assets.h"
#include <list>
#include <tuple>
#include <ctime>
#include <string>
#include <iostream>
#include <X11/Xlib.h>

const int minVelocity = -500;
const int maxVelocity = 500;
const int minRotate = -180;
const int maxRotate = 180;
const char *screensaverName = "Gophersaver";

using namespace gopher;

struct windowSize
{
    int w, h;
};

std::list<FlyObj *> loadEntitiesForRender(SDL_Renderer *render, int screenWidth, int screenHeight)
{
    std::list<FlyObj *> entities;

    // list of images
    for (auto &&img : {
             std::tuple<unsigned char *, unsigned int>{src_assets_astro_gopher_1_png, src_assets_astro_gopher_1_png_len},
             std::tuple<unsigned char *, unsigned int>{src_assets_astro_gopher_2_png, src_assets_astro_gopher_2_png_len},
             std::tuple<unsigned char *, unsigned int>{src_assets_astro_gopher_3_png, src_assets_astro_gopher_3_png_len},
             std::tuple<unsigned char *, unsigned int>{src_assets_astro_gopher_4_png, src_assets_astro_gopher_4_png_len}})
    {
        SDL_RWops *rw = SDL_RWFromConstMem(std::get<0>(img), std::get<1>(img));
        if (rw == nullptr)
        {
            throw "Can not load from const memory: " + std::string(SDL_GetError());
        }

        SDL_Surface *surface = IMG_LoadPNG_RW(rw);
        if (surface == nullptr)
        {
            throw "Can not load image from memory: " + std::string(SDL_GetError());
        }

        SDL_Texture *tex = SDL_CreateTextureFromSurface(render, surface);
        if (surface == nullptr)
        {
            throw "Can not crete texture from surface: " + std::string(SDL_GetError());
        }

        SDL_FPoint velocity{(float)(minVelocity + std::rand() % (maxVelocity - minVelocity)), (float)(minVelocity + std::rand() % (maxVelocity - minVelocity))};
        SDL_FPoint startPos{(float)(std::rand() % screenWidth), (float)(std::rand() % screenHeight)};
        double rotate = minRotate + std::rand() % (maxRotate - minRotate);

        entities.push_back(new FlyObj(tex, surface->w, surface->w, velocity, startPos, rotate));

        SDL_FreeSurface(surface);

        if (SDL_RWclose(rw) != 0)
        {
            throw "Can not close SDL_RWops: " + std::string(SDL_GetError());
        }
    }
    return entities;
}

bool needSetRootWindow(int argc, char *argv[])
{
    for (auto i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "-root" || arg == "--root")
        {
            return true;
        }
    }
    return false;
}

long unsigned int xscreensaveWindowId()
{
    char *widEnv = getenv("XSCREENSAVER_WINDOW");
    if (widEnv == nullptr)
    {
        return 0;
    }

    return strtol(widEnv, (char **)nullptr, 0);
}

windowSize *getWindowSize(long unsigned int windowId)
{
    Display *display = XOpenDisplay(nullptr);
    if (display == nullptr)
    {
        return nullptr;
    }

    XWindowAttributes windowAttributes;
    Window window = (Window)windowId;
    XGetWindowAttributes(display, window, &windowAttributes);
    XCloseDisplay(display);
}

/**
 * https://github.com/mbeckersys/xscreensaver-bigclock/blob/master/main.cpp
 */
SDL_Window *initWithXscreensaverWindow(long unsigned int xScreensaverWindowId)
{
    return SDL_CreateWindowFrom((void *)xScreensaverWindowId);
}

/**
 * Screensaver SDL root window hack
 * https://discourse.libsdl.org/t/drawing-on-the-root-window/1160/2
 */
void setRootWindow()
{
    printf("xwid=%s\n", getenv("XSCREENSAVER_WINDOW"));

    char windowidEnv[32];
    const char *display = std::getenv("DISPLAY");
    Display *di = XOpenDisplay(display);
    Window root = XDefaultRootWindow(di);
    std::sprintf(windowidEnv, "%ld", root);
    SDL_setenv("SDL_WINDOWID", windowidEnv, 1);
    std::cout << "using root window id: " << root << std::endl;
}

int main(int argc, char *argv[])
{
    std::srand(unsigned(std::time(0)));

    if (needSetRootWindow(argc, argv))
    {
        setRootWindow();
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    

    /*
    SDL_DisplayMode displayMode;
    if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0)
    {
        printf("SDL_GetCurrentDisplayMode Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    */
    auto screenWidth = displayMode.w;
    auto screenHeight = displayMode.h;

    /*
    SDL_Window *win = SDL_CreateWindow(screensaverName, 0, 0, screenWidth, screenHeight, SDL_WINDOW_FOREIGN);
    if (win == nullptr)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    */

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        printf("SDL_CreateRenderer Error %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    Physics *physics = new Physics(screenWidth, screenHeight);
    Render *render = new Render(ren);
    Scene *scene = new Scene(render, physics);

    for (auto entry : loadEntitiesForRender(ren, screenWidth, screenHeight))
    {
        render->addRenderable(entry);
        physics->addPhysent(entry);
    }

    bool running = true;

    while (running)
    {
        running = scene->update();
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return EXIT_SUCCESS;
}
