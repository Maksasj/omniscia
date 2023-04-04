#ifndef _OMNISCIA_EDITOR_RED_THEME_H_
#define _OMNISCIA_EDITOR_RED_THEME_H_

#include "theme.h"

namespace omniscia_editor::level_editor::themes {
    class RedTheme : public Theme {
        public:
            RedTheme();

            void apply_theme() override;
    };
    
}

#endif
