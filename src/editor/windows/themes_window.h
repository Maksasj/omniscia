#ifndef _OMNISCIA_EDITOR_THEMES_WINDOW_H_
#define _OMNISCIA_EDITOR_THEMES_WINDOW_H_

#include <iostream>
#include <string>

#include "gfx.h"
#include "types.h"

#include "themes/themes.h"

#include "app_window.h"

namespace omniscia_editor::windows {
    using namespace omni::types;
    using namespace omniscia_editor::themes;

    class ThemesWindow : public AppWindow  {
        private:
            std::vector<std::shared_ptr<Theme>> _themes;
            
            u64 currentIndex;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ThemesWindow>;

            ThemesWindow() {
                _themes = {
                    std::make_shared<DeepDarkTheme>(),
                    std::make_shared<DraculaTheme>(),
                    std::make_shared<GreenTheme>(),
                    std::make_shared<RedTheme>(),
                    std::make_shared<SimpleTheme>()
                };

                currentIndex = 0;

                apply_default();
            };

            void render_window() override {
                if(!ImGui::Begin("Themes")) {
                    ImGui::End();
                    return;
                }

                const ImGuiIO& io = ImGui::GetIO(); 

                if (ImGui::BeginCombo("## themes combo list", _themes[currentIndex].get()->get_name().c_str(), ImGuiComboFlags_None)) {
                    for (u64 n = 0; n < _themes.size(); ++n) {
                        
                        const bool isSelected = (currentIndex == n);

                        if (ImGui::Selectable(_themes[n]->get_name().c_str(), isSelected))
                            currentIndex = n;

                        if (isSelected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }


                if(currentIndex >= _themes.size()) {
                    ImGui::End();
                    return;
                }

                const auto& selectedTheme = _themes[currentIndex];

                ImGui::Text("Theme: '%s'", selectedTheme->get_name().c_str());
                ImGui::Text("Author: '%s'", selectedTheme->get_author().c_str());

                if(ImGui::Button("Apply theme")) {
                    selectedTheme->apply_theme();
                }

                ImGui::SameLine();

                if(ImGui::Button("Reset theme")) {
                    apply_default();
                }

                ImGui::End();
            }

            void apply_default() {
                _themes[0]->apply_theme();
            }

            void render_properties() override {
                PropertiesFieldQuery::property_window_edit_query(*this);
            }

            static ThemesWindow& get_instance() {
                static ThemesWindow window;
                return window;
            }
    };
}

template<>																	               
struct omni::reflector::Reflection<omniscia_editor::windows::ThemesWindow> {									               
    const constexpr static std::type_info &typeInfo = typeid(omniscia_editor::windows::ThemesWindow);           
    const constexpr static auto clearTypeName = "ThemesWindow";
    const constexpr static auto meta = std::make_tuple(
    );																		               
};

#endif
