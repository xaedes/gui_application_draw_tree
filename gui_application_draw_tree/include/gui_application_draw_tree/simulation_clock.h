#pragma once

#include "draw_tree_gl/drawable/drawable.h"
#include "gl_classes/imgui_gl.h"

#include "gui_application_draw_tree/version.h"

namespace gui_application_draw_tree {

    class Application;
    class SimulationClock
    {
    public:
        using Drawable = draw_tree_gl::drawable::Drawable;
        using Transform = typename Drawable::Transform;
        
        SimulationClock(Application& app);
        virtual ~SimulationClock();
        void setup();
        void frame();

        inline double dt() const { return m_dt; }
        inline double secondsSinceStart() const { return m_currentTime; }
        // inline std::chrono::time_point<std::chrono::high_resolution_clock> start() const { return m_start; }
        // inline std::chrono::time_point<std::chrono::high_resolution_clock> now() const { return m_now; }
        // inline std::chrono::time_point<std::chrono::high_resolution_clock> lastTime() const { return m_lastTime2; }
        
        inline bool paused() const { return m_pauseManual || m_pauseForced; }

        inline bool timeJumped() const { return m_timeJumped; }

        inline Transform::pointer display() const { return m_display; }

        void reset();
        void rewind();
    protected:
        void update();
        
        Application& app;
        
        Drawable::pointer m_displayContainer;
        Transform::pointer m_display;

        double m_dt;
        double m_minDt;
        double m_maxDt;
        double m_currentTime;
        float m_maxTime;
        float m_maxTimeIncreaseThreshold;
        double m_clockSpeed;
        bool m_pauseManual;
        bool m_pauseForced;
        bool m_showAdvanced;
        bool m_timeJumped;
    };

} // namespace gui_application_draw_tree

