#ifndef _OMNISCIA_EDITOR_PROPERTIES_FIELD_QUERY_H_
#define _OMNISCIA_EDITOR_PROPERTIES_FIELD_QUERY_H_

#include "omni_reflector.h"

#include "../gfx.h"
#include "../types.h"

namespace omniscia_editor::windows {
    using namespace omni::types;

    struct PropertiesFieldQuery {
        template<typename _T>
        static void property_edit_field(const char* fieldName, _T& field);

        template<typename _WindowType>
        static void property_window_edit_query(_WindowType& component);
    };
}

namespace omniscia_editor::windows {
    using namespace omni::types;

    template<typename _WindowType>
    void PropertiesFieldQuery::property_window_edit_query(_WindowType& component) {
        using Ref = omni::reflector::Reflection<_WindowType>;

        omni::reflector::FieldFriendlyScope::for_each_field<omni::reflector::predicate::is_any>(component, [&](const char* fieldName, auto& field) {
            PropertiesFieldQuery::property_edit_field(fieldName, field);
        });
    }
}

#endif
