#pragma once

#include <glm/glm.hpp>
#include <type_traits>

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
        
        using PerspectiveProjection         = cameras_gl::PerspectiveProjection;
        using SymmetricOrthogonalProjection = cameras_gl::SymmetricOrthogonalProjection;

        using FirstPersonPerspectiveCamera = cameras_gl::FirstPersonPerspectiveCamera;
        using OrbitalPerspectiveCamera     = cameras_gl::OrbitalPerspectiveCamera;
        using LookAtPerspectiveCamera      = cameras_gl::LookAtPerspectiveCamera;

        using FirstPersonSymmetricOrthogonalCamera  = cameras_gl::FirstPersonSymmetricOrthogonalCamera;
        using LookAtSymmetricOrthogonalCamera       = cameras_gl::LookAtSymmetricOrthogonalCamera;
        using OrbitalSymmetricOrthogonalCamera      = cameras_gl::OrbitalSymmetricOrthogonalCamera;


        GuiCameras(Application& app);
        virtual ~GuiCameras();
        void setup();
        void frame();

        CameraInterface* activeCamera() { return getCamera(activeCameraIndex()); }
        glm::vec2 cursor() { return m_cursor; };

        const glm::mat4& projection() const { return m_projection; }
        const glm::mat4& view() const { return m_view; }
        const glm::mat4& projection_view() const { return m_projection_view; }

    protected:
        void update(CameraInterface&, PerspectiveProjection* projection);
        void update(CameraInterface&, SymmetricOrthogonalProjection* projection);

        void update(CameraInterface&, FirstPersonView* view);
        void update(CameraInterface&, LookAtView* view);
        void update(CameraInterface&, OrbitalView* view);
        
    protected:
        void update(CameraInterface&, PerspectiveProjection& projection);
        void update(CameraInterface&, SymmetricOrthogonalProjection& projection);

        void update(CameraInterface&, FirstPersonView& view);
        void update(CameraInterface&, LookAtView& view);
        void update(CameraInterface&, OrbitalView& view);
        
    protected:
        void updateFromImGui(CameraInterface&, PerspectiveProjection& projection);
        void updateFromImGui(CameraInterface&, SymmetricOrthogonalProjection& projection);

        void updateFromImGui(CameraInterface&, FirstPersonView& view);
        void updateFromImGui(CameraInterface&, LookAtView& view);
        void updateFromImGui(CameraInterface&, OrbitalView& view);
        
    protected:
        void updateFromInput(CameraInterface&, PerspectiveProjection& projection);
        void updateFromInput(CameraInterface&, SymmetricOrthogonalProjection& projection);
        
        void updateFromInput(CameraInterface&, FirstPersonView& view);
        void updateFromInput(CameraInterface&, LookAtView& view);
        void updateFromInput(CameraInterface&, OrbitalView& view);
        
        bool SliderFloatWithUnit(const char* name, float* ptr, float min, float max, float ui_unit);

        Application& app;

        FirstPersonPerspectiveCamera         m_firstPersonPerspectiveCamera;
        OrbitalPerspectiveCamera             m_orbitalPerspectiveCamera;
        LookAtPerspectiveCamera              m_lookAtPerspectiveCamera;

        FirstPersonSymmetricOrthogonalCamera m_firstSymmetricOrthogonalPersonCamera;
        LookAtSymmetricOrthogonalCamera      m_lookAtSymmetricOrthogonalCamera;
        OrbitalSymmetricOrthogonalCamera     m_orbitalSymmetricOrthogonalCamera;

        PerspectiveProjection         m_perspectiveProjection;
        SymmetricOrthogonalProjection m_symmetricOrthogonalProjection;

        FirstPersonView m_firstPersonView;
        LookAtView      m_lookAtView;
        OrbitalView     m_orbitalView;

        using NumProjection = std::integral_constant<uint32_t, 2>;
        using NumView = std::integral_constant<uint32_t, 3>;
        
        CameraInterface* getCamera(int index);

        uint32_t activeCameraIndex() const { return m_activeProjection*NumView::value+m_activeView; }

        uint32_t m_activeProjection = 0;
        uint32_t m_activeView = 0;

        float D2R = 3.1415926535897932384626433832795f / 180.0f;
        float R2D = 180.0f / 3.1415926535897932384626433832795f;

        glm::mat4 m_projection;
        glm::mat4 m_view;
        glm::mat4 m_projection_view;
        glm::vec2 m_cursor;
    };

} // namespace gui_application_draw_tree
