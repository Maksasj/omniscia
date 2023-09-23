#ifndef _OMNISCIA_EDITOR_APP_WINDOW_H_
#define _OMNISCIA_EDITOR_APP_WINDOW_H_

#include <iostream>
#include <string>

#include "properties_field_query.h"

#include "gfx.h"
#include "types.h"

namespace omniscia_editor::windows {
    class AppWindow {
        private:
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<AppWindow>;

            virtual void render_window() {}

            virtual void render_properties() {}
    };
}

#endif
