#ifndef _OMNISCIA_EDITOR_THEME_H_
#define _OMNISCIA_EDITOR_THEME_H_

#include <string>

#include "../gfx.h"

namespace omniscia_editor::level_editor::themes {
    class Theme {
        std::string _name;
        std::string _author;
        public:
            Theme(std::string name, std::string author) : _name(name), _author(author) {

            }

            virtual void apply_theme() {

            }
    };
    
}

#endif
