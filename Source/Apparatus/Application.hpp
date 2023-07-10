#pragma once
#include "Module.hpp"
#include "Scheduler.hpp"
#include <entt/entity/fwd.hpp>
#include <entt/entt.hpp>

class Application
{
  public:
    void add_module(Module mod);

  private:
    entt::registry m_Registry;
    std::vector<Module> m_Modules;

    void run();
};
