#ifndef _OMNISCIA_EDITOR_TEXTURE_MANAGER_SYSTEM_H_
#define _OMNISCIA_EDITOR_TEXTURE_MANAGER_SYSTEM_H_

#include <fstream>
#include <string>
#include <unordered_map>

#include "gfx.h"
#include "types.h"
#include "window.h"

#include "asset_manager.h"

#include "texture_asset.h"

namespace omniscia_editor::systems {
    using namespace omni::types;
    using namespace omni::reflector;
    using namespace omni::reflector::serialization;

    class TextureManager : public AssetManager {
        protected:
            std::unordered_map<std::string, TextureAsset> _data;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<TextureManager>;
            friend class omni::reflector::serialization::JsonSerializer;

            void reload_assets(const std::string& filePath) override {
                    using json = nlohmann::json;

                    std::ifstream file(filePath);
                    const auto object = json::parse(file);

                    TextureManager manager = JsonSerializer::json_deserialize<TextureManager>(object);

                    for(const auto& asset : manager._data)
                        _data[asset.first] = TextureAsset{asset.second._filePath};

                    for(auto& asset : _data)
                        asset.second.load_asset_from_file();

                    file.close();
            } 

            u64 get_asset_count() override {
                return _data.size();
            }

            void render_asset_preview(const bool& fancyPreview) override {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.2f, 0.2f, 1.0f});

                if (ImGui::BeginTable("split", 7, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings)) {
                    for(const auto& assetInstance : _data) {
                        const TextureAsset& asset = assetInstance.second; 

                        ImGui::TableNextColumn();
                
                        if(!fancyPreview) {
                            if(ImGui::Button(assetInstance.first.c_str(), ImVec2(ImGui::GetColumnWidth(), ImGui::GetColumnWidth()))) {
                                GLFWwindow* window = Window::get_instance()->get_backend();

                                glfwSetClipboardString(window, assetInstance.first.c_str());
                            }
                        } else {
                            ImVec2 buttonSize = ImVec2(ImGui::GetColumnWidth(), ImGui::GetColumnWidth());

                            if(asset._width > asset._height) {
                                buttonSize.y *= static_cast<f32>(asset._height) / static_cast<f32>(asset._width);
                            } else {
                                buttonSize.x *= static_cast<f32>(asset._height) / static_cast<f32>(asset._width);
                            }

                            if(ImGui::ImageButton((void*)(intptr_t)assetInstance.second._texture, buttonSize)) {
                                GLFWwindow* window = Window::get_instance()->get_backend();

                                glfwSetClipboardString(window, assetInstance.first.c_str());
                            }
                        }
                        
                    }
                    ImGui::EndTable();
                }
                
                ImGui::PopStyleColor();
            }

            static TextureManager& get_instance() {
                static TextureManager instance;
                return instance;
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia_editor::systems, TextureManager, _data);

#endif
