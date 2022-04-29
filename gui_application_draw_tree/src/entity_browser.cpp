
#include "gui_application_draw_tree/entity_browser.h"
#include "gui_application_draw_tree/application.h"
#include "gui_application/glm_to_string.h"

namespace gui_application_draw_tree {

    EntityBrowser::EntityBrowser(Application& app) 
        : app(app)
    {

    }

    EntityBrowser::~EntityBrowser() 
    {

    }

    void EntityBrowser::setup()
    {

    }

    void EntityBrowser::frame()
    {

        ImGui::Begin("EntityBrowser");

        
        app.root->visit([this](auto& visit, auto* cf) -> void
        {
            if (!cf) return;
            std::string name = std::to_string(visit.depth) + " " + std::to_string(visit.index) + " " + cf->name;
            Drawable* drawable = static_cast<Drawable*>(cf->data);
            if (ImGui::TreeNode(name.c_str()))
            {
                if (drawable)
                {
                    ImGui::Checkbox("enabled", &drawable->enabled());
                }
                if (ImGui::TreeNode("transform"))
                {
                    imgui_coord_frame(cf);
                    ImGui::TreePop();
                }
                if (ImGui::TreeNode("children"))
                {
                    visit.children();
                    ImGui::TreePop();
                }
                else visit.skipChildren();
                ImGui::TreePop();
            }
            else visit.skipChildren();
        }  );
        ImGui::End();    
    }

    void EntityBrowser::imgui_coord_frame(Transform* tf)
    {
        auto localPos = tf->localPosition();
        auto scale = tf->localScale();
        auto eulerXYZ = glm::degrees( tf->localRotationEulerXYZ() );
        auto strWorldPose = std::to_string(tf->worldPose());

        ImGui::Text(strWorldPose.c_str());

        bool updatedPosition = false;
        updatedPosition |= ImGui::SliderFloat("localPos.x", &localPos.x, -100, 100);
        updatedPosition |= ImGui::SliderFloat("localPos.y", &localPos.y, -100, 100);
        updatedPosition |= ImGui::SliderFloat("localPos.z", &localPos.z, -100, 100);

        bool updatedScale = false;
        updatedScale |= ImGui::SliderFloat("scale.x", &scale.x, 0, 10);
        updatedScale |= ImGui::SliderFloat("scale.y", &scale.y, 0, 10);
        updatedScale |= ImGui::SliderFloat("scale.z", &scale.z, 0, 10);

        bool updatedEulerXYZ = false;
        updatedEulerXYZ |= ImGui::SliderFloat("euler.x", &eulerXYZ.x, -360, 360);
        updatedEulerXYZ |= ImGui::SliderFloat("euler.y", &eulerXYZ.y, -(90-1e-3f), (90 - 1e-3f));
        updatedEulerXYZ |= ImGui::SliderFloat("euler.z", &eulerXYZ.z, -360, 360);
        if (updatedPosition)
        {
            tf->setLocalPosition(localPos);
        }
        if (updatedScale)
        {
            tf->setLocalScale(scale);
        }
        if (updatedEulerXYZ)
        {
            tf->setLocalRotationEulerXYZ(glm::radians(eulerXYZ));
        }
    }

} // namespace gui_application_draw_tree
