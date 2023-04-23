#ifndef _LETTERBOX_CUTSCENE_EVENT_
#define _LETTERBOX_CUTSCENE_EVENT_

#include <string>

#include "cutscene_event.h"
#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    struct CE_LetterBoxProp {
        CE_Prop _base;
        std::string _message = "";
    };

    class CE_LetterBoxEvent : public CE_LetterBoxProp , public CE_Event {
        private:
            CE_LetterBoxEvent();
            CE_LetterBoxEvent(const CE_LetterBoxEvent&);
            void operator=(const CE_LetterBoxEvent&);

            Entity bottomBox;
            Entity upperBox;
        public:
            CE_LetterBoxEvent(const auto& data = CE_LetterBoxProp{});
            
            void execute() override;
    };
}

#endif
