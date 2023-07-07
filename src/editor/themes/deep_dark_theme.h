#ifndef _OMNISCIA_EDITOR_DEEP_DARK_THEME_H_
#define _OMNISCIA_EDITOR_DEEP_DARK_THEME_H_

#include "theme.h"

namespace omniscia_editor::level_editor::themes {
    using namespace omni::types;

    class DeepDarkTheme : public Theme {
        public:
            DeepDarkTheme();

            void apply_theme() override;
    };
    
}

#endif
