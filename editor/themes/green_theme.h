#ifndef _OMNISCIA_EDITOR_GREEN_THEME_H_
#define _OMNISCIA_EDITOR_GREEN_THEME_H_

#include "theme.h"

namespace omniscia_editor::level_editor::themes {
    class GreenTheme : public Theme {
        public:
            GreenTheme();

            void apply_theme() override;
    };
    
}

#endif
