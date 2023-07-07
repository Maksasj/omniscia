#ifndef _DEBUG_FIELD_QUERY_
#define _DEBUG_FIELD_QUERY_

#include <functional>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "omni_reflector.h"

#define OMNI_TYPES_ENABLE_REFLECTIONS
#include "omni_types.tpp"

#include "gfx.h"

namespace omniscia::core {
    using namespace omni::types;

    struct DebugFieldQuery {
        template<typename _T>
        static void debug_edit_field(const char* fieldName, _T& field);

        template<typename _ComponentType>
        static void debug_component_edit_query(_ComponentType& component);
    };
}

namespace omniscia::core {
    using namespace omni::types;

    template<typename _ComponentType>
    void DebugFieldQuery::debug_component_edit_query(_ComponentType& component) {
        using Ref = omni::reflector::Reflection<_ComponentType>;

        if(ImGui::TreeNode(Ref::clearTypeName)) {
            omni::reflector::FieldFriendlyScope::for_each_field<omni::reflector::predicate::is_any>(component, [&](const char* fieldName, auto& field) {
                DebugFieldQuery::debug_edit_field(fieldName, field);
            });

            ImGui::TreePop();
        }
    }
}

#endif
