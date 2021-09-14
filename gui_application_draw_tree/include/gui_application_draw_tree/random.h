#pragma once

#include <random>

#include "gui_application/random.h"

#include "gui_application_draw_tree/version.h"

namespace gui_application_draw_tree {

    class Application;
    class Random : public gui_application::Random
    {
    public:
        Random(Application& app);
        virtual ~Random();
        void setup();
        void frame();
        
    protected:
        Application& app;
    };

} // namespace gui_application_draw_tree

