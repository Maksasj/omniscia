#include "imgui/debug_field_query.h"

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
void omniscia::core::DebugFieldQuery::debug_edit_field<omni::types::u64>(const char* fieldName, omni::types::u64& field) {
    if (ImGui::TreeNode(fieldName)) {
        ImGui::Text("Type: '%s'", "u64");
        ImGui::Text("Iternal type: '%s'", "unsigned long long");

        ImGui::Text("Value: ");
        ImGui::DragScalar("value: ", ImGuiDataType_U64, &field, 1u, 0);

        ImGui::TreePop();
    }
}

template<>
void omniscia::core::DebugFieldQuery::debug_edit_field<omni::types::i32>(const char* fieldName, omni::types::i32& field) {
    if (ImGui::TreeNode(fieldName)) {
        ImGui::Text("Type: '%s'", "i32");
        ImGui::Text("Iternal type: '%s'", "signed long");

        ImGui::Text("Value: ");
        ImGui::DragScalar("value: ", ImGuiDataType_S32, &field, 1, 0);

        ImGui::TreePop();
    }
}

template<>
void omniscia::core::DebugFieldQuery::debug_edit_field<omni::types::u32>(const char* fieldName, omni::types::u32& field) {
    if (ImGui::TreeNode(fieldName)) {
        ImGui::Text("Type: '%s'", "u32");
        ImGui::Text("Iternal type: '%s'", "unsigned long");

        ImGui::Text("Value: ");
        ImGui::DragScalar("value: ", ImGuiDataType_U32, &field, 1u, 0);

        ImGui::TreePop();
    }
}

template<>
void omniscia::core::DebugFieldQuery::debug_edit_field<omni::types::f32>(const char* fieldName, omni::types::f32& field) {
    if (ImGui::TreeNode(fieldName)) {
        ImGui::Text("Type: '%s'", "f32");
        ImGui::Text("Iternal type: '%s'", "float");

        ImGui::Text("Value: ");
        ImGui::DragFloat("value: ", &field, 0.005f);

        ImGui::TreePop();
    }
}

template<>
void omniscia::core::DebugFieldQuery::debug_edit_field<std::string>(const char* fieldName, std::string& field) {
    if (ImGui::TreeNode(fieldName)) {
        ImGui::Text("Type: '%s'", "string");
        ImGui::Text("Iternal type: '%s'", "std::basic_string<char, std::char_traits<char>, std::allocator<char>>");

        char buffer[256] = { 0 };
        field.copy(buffer, field.size());

        ImGui::Text("Value: ");
        ImGui::InputText("string: ", buffer, 256);
        field = std::string(buffer);

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