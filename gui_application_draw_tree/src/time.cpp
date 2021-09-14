
#include "gui_application_draw_tree/renderer.h"
#include "gui_application_draw_tree/application.h"
#include "gui_application/glm_to_string.h"

namespace gui_application_draw_tree {

    Time::Time(Application& app) 
        : app(app)
    {

    }

    Time::~Time() 
    {

    }

    void Time::setup()
    {
        m_dt = 1.0 / 60.0;
        m_start = std::chrono::high_resolution_clock::now();
        m_now = std::chrono::high_resolution_clock::now();
        m_lastTime = std::chrono::high_resolution_clock::now();
        m_lastTime2 = std::chrono::high_resolution_clock::now();
    }

    void Time::frame()
    {
        auto m_now = std::chrono::high_resolution_clock::now();
        m_dt = std::chrono::duration<double>(m_now - m_lastTime).count();
        m_secondsSinceStart = std::chrono::duration<double>(m_now - m_start).count();
        if (m_dt > 1) m_dt = 1.0 / 60.0;
        m_lastTime2 = m_lastTime;
        m_lastTime = m_now;
    }


} // namespace gui_application_draw_tree
