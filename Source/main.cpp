#include "bgfx/defines.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_video.h>
#include <bgfx/bgfx.h>
#include <stdio.h>

SDL_Window *window = NULL;
const int WIDTH = 640;
const int HEIGHT = 480;
int main(int argc, char *args[])
{

    // Initialize SDL systems
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create a window
        window = SDL_CreateWindow("The Equinox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
    }

    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(window, &wmi))
    {
        return 1;
    }

    bgfx::Init bgfxInitStruct;

    bgfxInitStruct.resolution.width = WIDTH;
    bgfxInitStruct.resolution.height = HEIGHT;
    bgfxInitStruct.resolution.reset = BGFX_RESET_VSYNC;
    bgfxInitStruct.type = bgfx::RendererType::Count;
    bgfxInitStruct.platformData.ndt = wmi.info.x11.display;
    bgfxInitStruct.platformData.nwh = (void *)(uintptr_t)wmi.info.x11.window;

    bgfx::init(bgfxInitStruct);

    // Poll for events and wait till user closes window
    int width = WIDTH;
    int height = HEIGHT;

    bool quit = false;
    SDL_Event currentEvent;
    while (!quit)
    {
        while (SDL_PollEvent(&currentEvent) != 0)
        {
            if (currentEvent.type == SDL_QUIT)
            {
                quit = true;
            }

            switch (currentEvent.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_WINDOWEVENT:
                if (currentEvent.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    SDL_GetWindowSize(window, &width, &height);
                }
            }
        }

        bgfx::reset(width, height, BGFX_RESET_VSYNC);
        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000FF, 1.0f, 0);

        // Enable debug text.
        bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

        // Set view rectangle for 0th view
        bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height));

        // Clear the view rect
        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x7700FFFF, 1.0f, 0);

        // Set empty primitive on screen
        bgfx::touch(0);

        /*
        Put this inside the event loop of SDL, to render bgfx output
        */
        bgfx::frame();
    }

    // Free up window
    SDL_DestroyWindow(window);
    // Shutdown SDL
    SDL_Quit();

    return 0;
}
