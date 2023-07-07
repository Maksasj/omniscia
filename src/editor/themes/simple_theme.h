#ifndef _OMNISCIA_EDITOR_SIMPLE_THEME_H_
#define _OMNISCIA_EDITOR_SIMPLE_THEME_H_

#include "theme.h"

namespace omniscia_editor::level_editor::themes {
    using namespace omni::types;

    class SimpleTheme : public Theme {
        public:
            SimpleTheme();

            void apply_theme() override;
    };
    
}

#endif
