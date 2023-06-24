#include "debug_rendering_stage_preview.h"
#include "game.h"

static void AspectRatio(ImGuiSizeCallbackData* data) { 
    float aspect_ratio = *(float*)data->UserData; 
    data->DesiredSize.x = std::max(data->DesiredSize.x, data->DesiredSize.y); 
    data->DesiredSize.y = (float)(int)(data->DesiredSize.x / aspect_ratio); 
}

void omniscia::core::DebugRenderingStagePreview::render() {
    ImGuiIO& io = ImGui::GetIO();

    const DebugInfo& debugInfo = DebugInfo::get_instance();

    float aspect_ratio = 16.0f / 9.0f;
    ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), AspectRatio, (void*)&aspect_ratio);
    ImGui::SetNextWindowBgAlpha(0.55f);
    if (ImGui::Begin("Rendering stage preview")) {
        const auto& stages = RenderStagePool::get_instance().get_stages();

        if (ImGui::BeginTable("Rendering stage preview table", 3)) {
            i32 row = 0;
            for(const auto& stage : stages) {
                if(row % 3 == 0) {
                    ImGui::TableNextRow();
                }

                ImGui::TableSetColumnIndex(row % 3);
                ImGui::Text("%s", stage.first.c_str());
                ImVec2 wsize = ImGui::GetWindowSize();
                wsize.x /= 3;
                wsize.y /= 3;
                ImGui::Image((ImTextureID)(intptr_t)stage.second->get_raw_texture(), wsize, ImVec2(0, 1), ImVec2(1, 0), ImVec4(1, 1, 1, 1), ImVec4(0, 0, 0, 1));

                ++row;
            }
            ImGui::EndTable();
        }
    }

    ImGui::End();
}

omniscia::core::DebugRenderingStagePreview& omniscia::core::DebugRenderingStagePreview::get_instance() {
    static DebugRenderingStagePreview instance;
    return instance;
}
