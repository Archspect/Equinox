#include "Apparatus/Window.hpp"
#include <iostream>

int main(int, char *[])
{
    flecs::world ecs;

    ecs.import <WindowModule::WindowModule>();

    flecs::entity the_window = ecs.entity("Window").set<WindowModule::Window>({
        "The Equinox",
        1234,
        567,
        WindowModule::WindowFlags::Shown | WindowModule::WindowFlags::Resizable,
        false,
    });

    while (ecs.progress())
    {
    }
    return 0;
}