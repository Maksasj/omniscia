#ifndef _OMNISCIA_EDITOR_DRACULA_THEME_H_
#define _OMNISCIA_EDITOR_DRACULA_THEME_H_

#include "theme.h"

namespace omniscia_editor::level_editor::themes {
    class DraculaTheme : public Theme {
        public:
            DraculaTheme();

            void apply_theme() override;
    };
    
}

#endif
