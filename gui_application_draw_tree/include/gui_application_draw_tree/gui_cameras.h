#pragma once

#include <glm/glm.hpp>

#include "gl_classes/imgui_gl.h"
#include "draw_tree_gl/drawable/drawable.h"
#include "cameras_gl/cameras.h"

#include "gui_application_draw_tree/version.h"

namespace gui_application_draw_tree {

    //template <class App>
    class Application;
    class GuiCameras
    {
    public:
        using Drawable = draw_tree_gl::drawable::Drawable;
        using Transform = typename Drawable::Transform;
        using CameraInterface              = cameras_gl::CameraInterface;
        using CameraProjectionInterface    = cameras_gl::CameraProjectionInterface;
        using CameraViewInterface          = cameras_gl::CameraViewInterface;
        using FirstPersonView              = cameras_gl::FirstPersonView;
        using LookAtView                   = cameras_gl::LookAtView;
        using OrbitalView                  = cameras_gl::OrbitalView;
        using FirstPersonPerspectiveCamera = cameras_gl::FirstPersonPerspectiveCamera;
        using OrbitalPerspectiveCamera     = cameras_gl::OrbitalPerspectiveCamera;
        using LookAtPerspectiveCamera      = cameras_gl::LookAtPerspectiveCamera;
        using PerspectiveProjection        = cameras_gl::PerspectiveProjection;

        GuiCameras(Application& app);
        virtual ~GuiCameras();
        void setup();
        void frame();

        CameraInterface* activeCamera() { return m_activeCamera; }
        glm::vec2 cursor() { return m_cursor; };

        const glm::mat4& projection() const { return m_projection; }
        const glm::mat4& view() const { return m_view; }
        const glm::mat4& projection_view() const { return m_projection_view; }
    protected:

        void updateInput(CameraInterface&, FirstPersonView& fpv_view);
        void updateInput(CameraInterface&, LookAtView& lookat_view);
        void updateInput(CameraInterface&, OrbitalView& orbital_view);
        
        Application& app;

        FirstPersonPerspectiveCamera m_firstPersonCamera;
        OrbitalPerspectiveCamera m_orbitalCamera;
        LookAtPerspectiveCamera m_lookAtCamera;
        
        CameraInterface* m_activeCamera = nullptr;
        glm::mat4 m_projection;
        glm::mat4 m_view;
        glm::mat4 m_projection_view;
        glm::vec2 m_cursor;
    };

} // namespace gui_application_draw_tree
