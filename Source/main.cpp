#include "Apparatus/Window.hpp"
#include <iostream>

int main()
{
    flecs::world ecs;

    ecs.import <WindowModule::WindowModule>();

    flecs::entity the_window = ecs.entity("Window").set<WindowModule::Window>({
        "A Window",
        1200,
        700,
        WindowModule::WindowFlags::Shown | WindowModule::WindowFlags::Resizable,

    });

    return ecs.app().target_fps(60).run();
}