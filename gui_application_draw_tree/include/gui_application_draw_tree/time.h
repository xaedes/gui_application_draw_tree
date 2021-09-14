#pragma once

#include <chrono>

#include "draw_tree_gl/drawable/drawable.h"
#include "gl_classes/imgui_gl.h"

#include "gui_application_draw_tree/version.h"

namespace gui_application_draw_tree {

    class Application;
    class Time
    {
    public:
        using Drawable = draw_tree_gl::drawable::Drawable;
        using Transform = typename Drawable::Transform;
        
        Time(Application& app);
        virtual ~Time();
        void setup();
        void frame();
        

        inline double dt() const { return m_dt; }
        inline double secondsSinceStart() const { return m_secondsSinceStart; }
        inline std::chrono::time_point<std::chrono::high_resolution_clock> start() const { return m_start; }
        inline std::chrono::time_point<std::chrono::high_resolution_clock> now() const { return m_now; }
        inline std::chrono::time_point<std::chrono::high_resolution_clock> lastTime() const { return m_lastTime2; }
    protected:
        Application& app;
        double m_dt;
        double m_secondsSinceStart;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_now;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTime2;

    };

} // namespace gui_application_draw_tree

