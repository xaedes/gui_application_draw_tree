#pragma once

#include "draw_tree_gl/drawable/drawable.h"
#include "gl_classes/imgui_gl.h"

#include "gui_application_draw_tree/version.h"

namespace gui_application_draw_tree {

    class Application;
    class EntityBrowser
    {
    public:
        using Drawable = draw_tree_gl::drawable::Drawable;
        using Transform = typename Drawable::Transform;
        
        EntityBrowser(Application& app);
        virtual ~EntityBrowser();
        void setup();
        void frame();
        
    protected:
        void imgui_coord_frame(Transform* tf);
        Application& app;
    };

} // namespace gui_application_draw_tree

