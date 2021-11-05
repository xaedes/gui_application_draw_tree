
#include "gui_application_draw_tree/gui_cameras.h"
#include "gui_application_draw_tree/application.h"
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <string>

namespace gui_application_draw_tree {

    GuiCameras::GuiCameras(Application& app) 
        : app(app)
        , m_projection_view(glm::mat4(1))
    {
    }

    GuiCameras::~GuiCameras() 
    {

    }

    void GuiCameras::setup()
    {
        m_activeProjection = 0;
        m_activeView = 1;
        // m_activeCamera = &static_cast<CameraInterface&>(m_orbitalCamera);
        m_orbitalView.setDistance(36);
        m_orbitalView.setDistance(6000); 
        m_perspectiveProjection.setFarPlane(10000);
        m_symmetricOrthogonalProjection.setFarPlane(10000);
        m_symmetricOrthogonalProjection.setWidth(3000);
    }

    void GuiCameras::frame()
    {
        int display_w, display_h;
        glfwGetFramebufferSize(app.window(), &display_w, &display_h);
        auto cursor_pos = ImGui::GetMousePos();
        m_cursor = glm::vec2(cursor_pos.x , (display_h-1) - cursor_pos.y);
        ImGui::Begin("Camera");
        {
            ImGui::BeginTabBar("Projection Options");
            {
                if (ImGui::BeginTabItem("Perspective Projection"))
                {
                    m_activeProjection = 0;
                    update(*activeCamera(), dynamic_cast<PerspectiveProjection*>(&activeCamera()->projection()));
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Orthogonal Projection"))
                {
                    m_activeProjection = 1;
                    update(*activeCamera(), dynamic_cast<SymmetricOrthogonalProjection*>(&activeCamera()->projection()));
                    ImGui::EndTabItem();
                }
            }
            ImGui::EndTabBar();

            ImGui::BeginTabBar("View Options");
            {
                if (ImGui::BeginTabItem("Orbital View"))
                {
                    m_activeView = 1;
                    update(*activeCamera(), dynamic_cast<OrbitalView*>(&activeCamera()->view()));
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("First Person View"))
                {
                    m_activeView = 0;
                    update(*activeCamera(), dynamic_cast<FirstPersonView*>(&activeCamera()->view()));
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Look At  View"))
                {
                    m_activeView = 2;
                    update(*activeCamera(), dynamic_cast<LookAtView*>(&activeCamera()->view()));
                    ImGui::EndTabItem();
                }
            }
            ImGui::EndTabBar();
        }
        ImGui::End();

        if (activeCamera())
        {
            auto cam = activeCamera();
            cam->projection().setViewportSize({ display_w, display_h });
            m_projection = cam->projection().mat();
            m_view = cam->view().mat();
            m_projection_view = m_projection * m_view;
        }
    }

    GuiCameras::CameraInterface* GuiCameras::getCamera(int index)
    {
        switch(index)
        {
        case 0: return static_cast<CameraInterface*>(&m_firstPersonPerspectiveCamera);         break;
        case 1: return static_cast<CameraInterface*>(&m_orbitalPerspectiveCamera);             break;
        case 2: return static_cast<CameraInterface*>(&m_lookAtPerspectiveCamera);              break;
        case 3: return static_cast<CameraInterface*>(&m_firstSymmetricOrthogonalPersonCamera); break;
        case 4: return static_cast<CameraInterface*>(&m_orbitalSymmetricOrthogonalCamera);     break;
        case 5: return static_cast<CameraInterface*>(&m_lookAtSymmetricOrthogonalCamera);      break;
        default: return nullptr;                                                               break;
        }
    }

    void GuiCameras::update(CameraInterface& cam, PerspectiveProjection* projection)
    {
        if (projection != nullptr) update(cam, *projection);
    }

    void GuiCameras::update(CameraInterface& cam, SymmetricOrthogonalProjection* projection)
    {
        if (projection != nullptr) update(cam, *projection);
    }

    void GuiCameras::update(CameraInterface& cam, FirstPersonView* view)
    {
        if (view != nullptr) update(cam, *view);
    }

    void GuiCameras::update(CameraInterface& cam, LookAtView* view)
    {
        if (view != nullptr) update(cam, *view);
    }

    void GuiCameras::update(CameraInterface& cam, OrbitalView* view)
    {
        if (view != nullptr) update(cam, *view);
    }

    void GuiCameras::update(CameraInterface& cam, PerspectiveProjection& projection)
    {
        projection = m_perspectiveProjection;
        updateFromImGui(cam, projection);
        updateFromInput(cam, projection);
        m_perspectiveProjection = projection;
    }

    void GuiCameras::update(CameraInterface& cam, SymmetricOrthogonalProjection& projection)
    {
        projection = m_symmetricOrthogonalProjection;
        updateFromImGui(cam, projection);
        updateFromInput(cam, projection);
        m_symmetricOrthogonalProjection = projection;
    }

    void GuiCameras::update(CameraInterface& cam, FirstPersonView& view)
    {
        view = m_firstPersonView;
        updateFromImGui(cam, view);
        updateFromInput(cam, view);
        m_firstPersonView = view;
    }

    void GuiCameras::update(CameraInterface& cam, LookAtView& view)
    {
        view = m_lookAtView;
        updateFromImGui(cam, view);
        updateFromInput(cam, view);
        m_lookAtView = view;
    }

    void GuiCameras::update(CameraInterface& cam, OrbitalView& view)
    {
        view = m_orbitalView;
        updateFromImGui(cam, view);
        updateFromInput(cam, view);
        m_orbitalView = view;
    }

    void GuiCameras::updateFromImGui(CameraInterface& cam, PerspectiveProjection& projection)
    {
        // float fov_deg = projection.fov() * 180 / 3.14159 ;
        // if (ImGui::SliderFloat("fov", &fov_deg, 0, 180))
        // {
        //     projection.setFov(fov_deg * 3.14159 / 180);
        // }
        bool changed = false;
        changed |= SliderFloatWithUnit("near", &projection.accessFov(), 0, 100, R2D);
        changed |= ImGui::SliderFloat("near", &projection.accessNearPlane(), 0, 100);
        changed |= ImGui::SliderFloat("far", &projection.accessFarPlane(), 0, 10000);
        if (changed)
        {
            projection.update();
        }
    }

    void GuiCameras::updateFromImGui(CameraInterface& cam, SymmetricOrthogonalProjection& projection)
    {
        bool changed = false;
        static float max_width = 10000;
        static float max_offset_x = 2000;
        static float max_offset_y = 2000;
        changed |= ImGui::SliderFloat("width", &projection.accessWidth(), 0, max_width);
        changed |= ImGui::SliderFloat("offset_x", &(projection.accessOffset().x), -max_offset_x, max_offset_x);
        changed |= ImGui::SliderFloat("offset_y", &(projection.accessOffset().y), -max_offset_x, max_offset_y);
        changed |= ImGui::SliderFloat("near", &projection.accessNearPlane(), 0, 100);
        changed |= ImGui::SliderFloat("far", &projection.accessFarPlane(), 0, 10000);
        if (projection.width() >= max_width) max_width = projection.width() + 100;
        if (abs(projection.offset().x) >= max_offset_x) max_offset_x = abs(projection.offset().x) + 100;
        if (abs(projection.offset().y) >= max_offset_y) max_offset_y = abs(projection.offset().y) + 100;
        if (changed)
        {
            projection.update();
        }
    }

    void GuiCameras::updateFromImGui(CameraInterface& cam, FirstPersonView& view)
    {
        bool changed = false;
        changed |= ImGui::SliderFloat("position.x", &view.accessPosition().x, -100, 100);
        changed |= ImGui::SliderFloat("position.y", &view.accessPosition().y, -100, 100);
        changed |= ImGui::SliderFloat("position.z", &view.accessPosition().z, -100, 100);
        changed |= SliderFloatWithUnit("roll",  &view.accessRollPitchYaw().x, -360, 360, R2D);
        changed |= SliderFloatWithUnit("pitch", &view.accessRollPitchYaw().y, -360, 360, R2D);
        changed |= SliderFloatWithUnit("yaw",   &view.accessRollPitchYaw().z, -360, 360, R2D);
        if (changed)
        {
            view.update();
        }
    }

    void GuiCameras::updateFromImGui(CameraInterface& cam, LookAtView& view)
    {
        bool changed = false;
        changed |= ImGui::SliderFloat("position.x", &view.accessPosition().x, -100, 100);
        changed |= ImGui::SliderFloat("position.y", &view.accessPosition().y, -100, 100);
        changed |= ImGui::SliderFloat("position.z", &view.accessPosition().z, -100, 100);
        changed |= ImGui::SliderFloat("target.x", &view.accessTarget().x, -100, 100);
        changed |= ImGui::SliderFloat("target.y", &view.accessTarget().y, -100, 100);
        changed |= ImGui::SliderFloat("target.z", &view.accessTarget().z, -100, 100);
        if (changed)
        {
            view.update();
        }
    }

    void GuiCameras::updateFromImGui(CameraInterface& cam, OrbitalView& view)
    {
        bool changed = false;
        changed |= ImGui::SliderFloat("target.x", &view.accessTarget().x, -150, 150);
        changed |= ImGui::SliderFloat("target.y", &view.accessTarget().y, -150, 150);
        changed |= ImGui::SliderFloat("target.z", &view.accessTarget().z, -150, 150);
        changed |= SliderFloatWithUnit("roll",  &view.accessAngles().x, -360, 360, R2D);
        changed |= SliderFloatWithUnit("pitch", &view.accessAngles().y, -360, 360, R2D);
        changed |= SliderFloatWithUnit("yaw",   &view.accessAngles().z, -360, 360, R2D);
        static float max_distance = 150;
        changed |= ImGui::SliderFloat("distance", &view.accessDistance(), 0, max_distance);
        changed |= ImGui::Checkbox("swap y & z", &view.accessSwapYZ());
        if (view.distance() >= max_distance) max_distance = view.distance() + 20;
        if (changed)
        {
            view.update();
        }
    }

    bool GuiCameras::SliderFloatWithUnit(const char* name, float* ptr, float min, float max, float ui_unit)
    {
        float value_scaled = (*ptr) * ui_unit;
        if (ImGui::SliderFloat(name, &value_scaled, min, max))
        {
            *ptr = value_scaled / ui_unit;
            return true;
        }
        return false;
    }

    void GuiCameras::updateFromInput(CameraInterface& cam, PerspectiveProjection& projection)
    {

    }

    void GuiCameras::updateFromInput(CameraInterface& cam, SymmetricOrthogonalProjection& projection)
    {

    }

    void GuiCameras::updateFromInput(CameraInterface& cam, FirstPersonView& view)
    {

    }

    void GuiCameras::updateFromInput(CameraInterface& cam, LookAtView& view)
    {

    }

    void GuiCameras::updateFromInput(CameraInterface& cam, OrbitalView& view)
    {

    }

        


} // namespace gui_application_draw_tree

