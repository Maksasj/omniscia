#ifndef _OMNISCIA_EDITOR_METRICS_WINDOW_H_
#define _OMNISCIA_EDITOR_METRICS_WINDOW_H_

#include <iostream>
#include <string>

#include "gfx.h"
#include "types.h"

#include "app_window.h"

namespace omniscia_editor::windows {
    using namespace omni::types;

    class MetricsWindow : public AppWindow  {
        private:

            /* Properies */
            bool _renderFrameRate;
            bool _renderTriangleInfo;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<MetricsWindow>;

            MetricsWindow() {
                _renderFrameRate = true;
                _renderTriangleInfo = true;
            };

            void render_window() override {
                if(!ImGui::Begin("Metrics")) {
                    ImGui::End();
                    return;
                }

                const ImGuiIO& io = ImGui::GetIO(); 

                if(_renderFrameRate)
                    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                
                if(_renderTriangleInfo)
                    ImGui::Text("%d vertices, %d indices (%d triangles)", io.MetricsRenderVertices, io.MetricsRenderIndices, io.MetricsRenderIndices / 3);

                ImGui::End();
            }

            void render_properties() override {
                PropertiesFieldQuery::property_window_edit_query(*this);
            }

            static MetricsWindow& get_instance() {
                static MetricsWindow window;
                return window;
            }
    };
}

template<>																	               
struct omni::reflector::Reflection<omniscia_editor::windows::MetricsWindow> {									               
    const constexpr static std::type_info &typeInfo = typeid(omniscia_editor::windows::MetricsWindow);           
    const constexpr static auto clearTypeName = "MetricsWindow";
    const constexpr static auto meta = std::make_tuple(
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::MetricsWindow::_renderFrameRate, "Render frame rate"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::MetricsWindow::_renderTriangleInfo, "Render triangle info")
    );																		               
};

#endif
