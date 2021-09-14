#pragma once

#include "draw_tree_gl/drawable/drawable.h"
#include "draw_tree_gl/shader/default_program.h"
#include "draw_tree_gl/renderer.h"
#include "gl_classes/imgui_gl.h"

#include "gui_application_draw_tree/version.h"

namespace gui_application_draw_tree {

    class Application;
    class Renderer : public draw_tree_gl::Renderer
    {
    public:
        using Drawable = draw_tree_gl::drawable::Drawable;
        using Transform = typename Drawable::Transform;
        using DefaultProgram = draw_tree_gl::shader::DefaultProgram;
        
        Renderer(Application& app);
        virtual ~Renderer();
        void setup() override;
        void frame();
        
    protected:
        Application& app;
        draw_tree_gl::Renderer m_renderer;
    };

} // namespace gui_application_draw_tree

