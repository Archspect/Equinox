#pragma once

#include <vector>

typedef void sysFuncSig(void);
typedef sysFuncSig *sysFuncSigPtr;

class Scheduler
{
  public:
    void add_init_system(sysFuncSig system);
    void add_update_system(sysFuncSig system);
    void add_tick_system(sysFuncSig system);
    void add_render_system(sysFuncSig system);
    void add_exit_system(sysFuncSig system);

    int run();

  private:
    std::vector<sysFuncSigPtr> m_initSystemsList;
    std::vector<sysFuncSigPtr> m_updateSystemsList;
    std::vector<sysFuncSigPtr> m_tickSystemsList;
    std::vector<sysFuncSigPtr> m_renderSystemsList;
    std::vector<sysFuncSigPtr> m_existSystemList;
};