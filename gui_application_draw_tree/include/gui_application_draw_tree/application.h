#pragma once

#include "gui_application/gui_application.h"
#include "draw_tree_gl/drawable/drawable.h"

#include "gui_application_draw_tree/entity_browser.h"
#include "gui_application_draw_tree/gui_cameras.h"
#include "gui_application_draw_tree/renderer.h"
#include "gui_application_draw_tree/simulation_clock.h"
#include "gui_application_draw_tree/time.h"
#include "gui_application_draw_tree/random.h"

#include "gui_application_draw_tree/version.h"

namespace gui_application_draw_tree {

    class Application : public gui_application::GuiApplication
    {
    public:
        using Drawable = draw_tree_gl::drawable::Drawable;
        using memory_pool_type = typename Drawable::memory_pool_type;
        using Transform = typename Drawable::Transform;

        Application();
        virtual ~Application();
        virtual void setup() override;
        virtual void frame() override;

        virtual void setupDrawables();

        memory_pool_type    pool;
        Transform::pointer  root;

        Renderer            renderer;

        Time                time;
        GuiCameras          cameras;
        EntityBrowser       entityBrowser;
        SimulationClock     simulationClock;
        Random              random;
    };

} // namespace gui_application_draw_tree
