#include "debug_field_query.h"

template<>
void omniscia::core::DebugFieldQuery::debug_edit_field<bool>(const char* fieldName, bool& field) {
    if (ImGui::TreeNode(fieldName)) {
        ImGui::Text("Type: '%s'", "bool");
        ImGui::Text("Iternal type: '%s'", "bool");

        ImGui::Text("Value: ");
        ImGui::Checkbox("Enable", &field);

        ImGui::TreePop();
    }
}

template<>
void omniscia::core::DebugFieldQuery::debug_edit_field<omni::types::Vec2f>(const char* fieldName, omni::types::Vec2f& field) {
    using Ref = omni::reflector::Reflection<omni::types::Vec2f>;

    if (ImGui::TreeNode(fieldName)) {
        ImGui::Text("Type: '%s'", Ref::clearTypeName);
        ImGui::Text("Iternal type: '%s'", Ref::typeInfo.name());

        ImGui::Text("Value: ");
        ImGui::DragFloat("x", &field.x, 0.005f);
        ImGui::DragFloat("y", &field.y, 0.005f);

        ImGui::TreePop();
    }
}

template<>
void omniscia::core::DebugFieldQuery::debug_edit_field<omni::types::Vec3f>(const char* fieldName, omni::types::Vec3f& field) {
    using Ref = omni::reflector::Reflection<omni::types::Vec3f>;

    if (ImGui::TreeNode(fieldName)) {
        ImGui::Text("Type: '%s'", Ref::clearTypeName);
        ImGui::Text("Iternal type: '%s'", Ref::typeInfo.name());

        ImGui::Text("Value: ");
        ImGui::DragFloat("x", &field.x, 0.005f);
        ImGui::DragFloat("y", &field.y, 0.005f);
        ImGui::DragFloat("z", &field.z, 0.005f);

        ImGui::TreePop();
    }
}

template<>
void omniscia::core::DebugFieldQuery::debug_edit_field<omni::types::Vec4f>(const char* fieldName, omni::types::Vec4f& field) {
    using Ref = omni::reflector::Reflection<omni::types::Vec4f>;

    if (ImGui::TreeNode(fieldName)) {
        ImGui::Text("Type: '%s'", Ref::clearTypeName);
        ImGui::Text("Iternal type: '%s'", Ref::typeInfo.name());

        ImGui::Text("Value: ");
        ImGui::DragFloat("x", &field.x, 0.005f);
        ImGui::DragFloat("y", &field.y, 0.005f);
        ImGui::DragFloat("z", &field.z, 0.005f);
        ImGui::DragFloat("w", &field.w, 0.005f);

        ImGui::TreePop();
    }
}