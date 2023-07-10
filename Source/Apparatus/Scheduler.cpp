#include "Scheduler.hpp"

void Scheduler::add_init_system(sysFuncSig system)
{
    m_initSystemsList.push_back(system);
}

void Scheduler::add_update_system(sysFuncSig system)
{
    m_updateSystemsList.push_back(system);
}

void Scheduler::add_tick_system(sysFuncSig system)
{
    m_tickSystemsList.push_back(system);
}

void Scheduler::add_render_system(sysFuncSig system)
{
    m_renderSystemsList.push_back(system);
}

void Scheduler::add_exit_system(sysFuncSig system)
{
    m_renderSystemsList.push_back(system);
}
