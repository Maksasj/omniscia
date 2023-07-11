#ifndef _OMNISCIA_EDITOR_HISTORY_WINDOW_H_
#define _OMNISCIA_EDITOR_HISTORY_WINDOW_H_

#include <iostream>
#include <string>
#include <stack>

#include "gfx.h"
#include "types.h"

#include "level_data.h"
#include "app_window.h"

namespace omniscia_editor::windows {
    using namespace omni::types;
    using namespace omniscia::core;

    class HistoryWindow : public AppWindow  {
        struct HistoryRecord {
            LevelData _levelData;
            std::string _label;
        };

        private:
            std::deque<HistoryRecord> _history;

            /** Properties */
            f32 _visibleSteps;
            bool _autoScroll;

            u64 _massiveUndoTimesMax;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<HistoryWindow>;

            HistoryWindow();

            void record(const std::string& label);

            void undo(const u64& times);

            void render_window() override;

            void render_properties() override;

            static HistoryWindow& get_instance();
    };
}

template<>																	               
struct omni::reflector::Reflection<omniscia_editor::windows::HistoryWindow> {									               
    const constexpr static std::type_info &typeInfo = typeid(omniscia_editor::windows::HistoryWindow);           
    const constexpr static auto clearTypeName = "HistoryWindow";
    const constexpr static auto meta = std::make_tuple(
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::HistoryWindow::_visibleSteps, "Visible steps"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::HistoryWindow::_autoScroll, "Auto scroll"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::HistoryWindow::_massiveUndoTimesMax, "Huge undo count")
    );
};

#endif
