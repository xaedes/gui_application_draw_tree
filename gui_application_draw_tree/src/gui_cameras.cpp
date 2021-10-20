
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
        m_activeCamera = &static_cast<CameraInterface&>(m_orbitalCamera);
        m_orbitalCamera.accessView().setDistance(36);
    }

    void GuiCameras::frame()
    {
        int display_w, display_h;
        glfwGetFramebufferSize(app.window(), &display_w, &display_h);
        // auto* vp = ImGui::GetMainViewport();
        // vp->WorkPos.x
    // WorkSize    
        auto cursor_pos = ImGui::GetMousePos();
        // auto win_pos = ImGui::GetWindowPos();
        m_cursor = glm::vec2(cursor_pos.x , (display_h-1) - cursor_pos.y);
        ImGui::Begin("Camera");

        PerspectiveProjection* projection = dynamic_cast<PerspectiveProjection*>(&m_activeCamera->projection());
        if (projection)
        {
            float fov_deg = projection->fov() * 180 / 3.14159 ;
            if (ImGui::SliderFloat("fov", &fov_deg, 0, 180))
            {
                projection->setFov(fov_deg * 3.14159 / 180);
            }
            bool changed = false;
            changed |= ImGui::SliderFloat("near", &projection->accessNearPlane(), 0, 100);
            changed |= ImGui::SliderFloat("far", &projection->accessFarPlane(), 0, 10000);
            if (changed)
            {
                projection->update();
            }

        }
        
        ImGui::BeginTabBar("Camera Options");

        if (ImGui::BeginTabItem("Orbital Camera"))
        {
            bool changed = false;
            auto& view = m_orbitalCamera.accessView();
            changed |= ImGui::SliderFloat("target.x", &view.accessTarget().x, -150, 150);
            changed |= ImGui::SliderFloat("target.y", &view.accessTarget().y, -150, 150);
            changed |= ImGui::SliderFloat("target.z", &view.accessTarget().z, -150, 150);
            changed |= ImGui::SliderFloat("roll",  &view.accessAngles().x, -3.14159 * 2, 3.14159 * 2);
            changed |= ImGui::SliderFloat("pitch", &view.accessAngles().y, -3.14159 * 2, 3.14159 * 2);
            changed |= ImGui::SliderFloat("yaw",   &view.accessAngles().z, -3.14159 * 2, 3.14159 * 2);
            static float max_distance = 150;
            changed |= ImGui::SliderFloat("distance", &view.accessDistance(), 0, max_distance);
            changed |= ImGui::Checkbox("swap y & z", &view.accessSwapYZ());
            if (view.distance() >= max_distance)
            {
                max_distance = view.distance() + 20;
            }
            if (changed)
            {
                view.update();
            }
            ImGui::EndTabItem();
            m_activeCamera = &static_cast<CameraInterface&>(m_orbitalCamera);

            updateInput(*m_activeCamera, view);
        }
        if (ImGui::BeginTabItem("First Person Camera"))
        {
            bool changed = false;
            auto& view = m_firstPersonCamera.accessView();
            changed |= ImGui::SliderFloat("position.x", &view.accessPosition().x, -100, 100);
            changed |= ImGui::SliderFloat("position.y", &view.accessPosition().y, -100, 100);
            changed |= ImGui::SliderFloat("position.z", &view.accessPosition().z, -100, 100);
            changed |= ImGui::SliderFloat("roll",  &view.accessRollPitchYaw().x, -3.14159 * 2, 3.14159 * 2);
            changed |= ImGui::SliderFloat("pitch", &view.accessRollPitchYaw().y, -3.14159 * 2, 3.14159 * 2);
            changed |= ImGui::SliderFloat("yaw",   &view.accessRollPitchYaw().z, -3.14159 * 2, 3.14159 * 2);
            if (changed)
            {
                view.update();
            }
            ImGui::EndTabItem();
            m_activeCamera = &static_cast<CameraInterface&>(m_firstPersonCamera);
            updateInput(*m_activeCamera, view);
        }
        if (ImGui::BeginTabItem("Look At Camera"))
        {
            bool changed = false;
            auto& view = m_lookAtCamera.accessView();
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
            ImGui::EndTabItem();
            m_activeCamera = &static_cast<CameraInterface&>(m_lookAtCamera);
            updateInput(*m_activeCamera, view);
        }
        ImGui::EndTabBar();

        ImGui::End();

        if (m_activeCamera)
        {
            m_activeCamera->projection().setViewportSize({ display_w, display_h });
            m_projection = m_activeCamera->projection().mat();
            m_view = m_activeCamera->view().mat();
            m_projection_view = m_projection * m_view;
        }

    }

    void GuiCameras::updateInput(CameraInterface& cam, FirstPersonView& fpv_view)
    {

    }

    void GuiCameras::updateInput(CameraInterface& cam, LookAtView& lookat_view)
    {

    }

    void GuiCameras::updateInput(CameraInterface& cam, OrbitalView& view)
    {

    }

        


} // namespace gui_application_draw_tree

