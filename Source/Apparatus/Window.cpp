#include "Window.hpp"
#include "Events.hpp"
#include "flecs/addons/cpp/mixins/pipeline/decl.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_syswm.h>

namespace WindowModule
{

WindowModule::WindowModule(flecs::world &ecs)
{
    ecs.module<WindowModule>();
    flecs::system InitWindow, UpdateWindow;
    SDL_Window *sdl_window;
    SDL_Event currentSDLEvent;
    SDL_SysWMinfo WMI;

    InitWindow = ecs.system<Window>("Initialize Window Module").kind(flecs::OnStart).each([&, this](Window &w) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            printf("Welp. Looks like SDL gave up :/\n");
            printf("It was saying something about, SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            SDL_Window *sdl_window =
                SDL_CreateWindow(w.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w.width, w.height, w.flags);
            if (sdl_window == NULL)
            {
                printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            }
        }
    });

    UpdateWindow =
        ecs.system<Window>("Loop forever to keep the window up").kind(flecs::OnUpdate).each([&, this](Window &w) {
            while (!w.quit)
            {
                while (SDL_PollEvent(&currentSDLEvent) != 0)
                {
                    switch (currentSDLEvent.type)
                    {
                    case SDL_WINDOWEVENT:

                        switch (currentSDLEvent.window.event)
                        {
                        case SDL_WINDOWEVENT_SHOWN:
                            ecs.event<Events::Window::Shown>().emit();
                            break;

                        case SDL_WINDOWEVENT_HIDDEN:
                            ecs.event<Events::Window::Hidden>().emit();
                            break;

                        case SDL_WINDOWEVENT_EXPOSED:
                            ecs.event<Events::Window::Exposed>().emit();
                            break;

                        case SDL_WINDOWEVENT_MOVED:
                            ecs.event<Events::Window::Moved>().emit();
                            break;

                        case SDL_WINDOWEVENT_RESIZED:
                            ecs.event<Events::Window::Resized>().emit();
                            break;

                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            ecs.event<Events::Window::SizeChanged>().emit();
                            break;

                        case SDL_WINDOWEVENT_MINIMIZED:
                            ecs.event<Events::Window::Minimized>().emit();
                            break;

                        case SDL_WINDOWEVENT_MAXIMIZED:
                            ecs.event<Events::Window::Maximized>().emit();
                            break;

                        case SDL_WINDOWEVENT_RESTORED:
                            ecs.event<Events::Window::Restored>().emit();
                            break;

                        case SDL_WINDOWEVENT_ENTER:
                            ecs.event<Events::Window::MouseFocus>().emit();
                            break;

                        case SDL_WINDOWEVENT_LEAVE:
                            ecs.event<Events::Window::MouseUnfocus>().emit();
                            break;

                        case SDL_WINDOWEVENT_FOCUS_GAINED:
                            ecs.event<Events::Window::KeyboardFocus>().emit();
                            break;

                        case SDL_WINDOWEVENT_FOCUS_LOST:
                            ecs.event<Events::Window::KeyboardUnfocus>().emit();
                            break;

                        case SDL_WINDOWEVENT_CLOSE:
                            ecs.event<Events::Window::Close>().emit();
                            break;

                        case SDL_WINDOWEVENT_TAKE_FOCUS:
                            ecs.event<Events::Window::OfferedFocus>().emit();
                            break;

                        case SDL_WINDOWEVENT_DISPLAY_CHANGED:
                            ecs.event<Events::Window::DisplayChanged>().emit();
                            break;
                        }
                    }
                }
            }
        });

    ecs.observer<Window>().event<Events::Window::Close>().each([&](Window &w) { w.quit = true; });
}

} // namespace WindowModule
