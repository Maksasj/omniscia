#include "properties_field_query.h"

template<>
void omniscia_editor::windows::PropertiesFieldQuery::property_edit_field<bool>(const char* fieldName, bool& field) {
    auto flags = ImGuiTreeNodeFlags_DefaultOpen;
    
    if (ImGui::TreeNodeEx(fieldName, flags)) {
        ImGui::Text("Value: ");
        ImGui::SameLine();
        ImGui::Checkbox("## value", &field);

        ImGui::TreePop();
    }
}

template<>
void omniscia_editor::windows::PropertiesFieldQuery::property_edit_field<omni::types::f32>(const char* fieldName, omni::types::f32& field) {
    auto flags = ImGuiTreeNodeFlags_DefaultOpen;
    
    if (ImGui::TreeNodeEx(fieldName, flags)) {
        ImGui::Text("Value: ");
        ImGui::SameLine();
        ImGui::DragFloat("## value", &field, 0.005f);

        ImGui::TreePop();
    }
}

template<>
void omniscia_editor::windows::PropertiesFieldQuery::property_edit_field<std::string>(const char* fieldName, std::string& field) {
    auto flags = ImGuiTreeNodeFlags_DefaultOpen;
    
    if (ImGui::TreeNodeEx(fieldName, flags)) {
        char buffer[256] = { 0 };
        field.copy(buffer, field.size());

        ImGui::Text("Value: ");
        ImGui::SameLine();
        ImGui::InputText("#v# alue", buffer, 256);
        field = std::string(buffer);

        ImGui::TreePop();
    }
}