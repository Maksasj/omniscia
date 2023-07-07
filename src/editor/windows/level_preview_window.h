#ifndef _OMNISCIA_EDITOR_LEVEL_PREVIEW_WINDOW_H_
#define _OMNISCIA_EDITOR_LEVEL_PREVIEW_WINDOW_H_

#include <iostream>
#include <string>

#include "../gfx.h"
#include "../types.h"

#include "app_window.h"
#include "tools_window.h"

namespace omniscia_editor::windows {
    using namespace omni::types;

    class LevelPreviewWindow : public AppWindow {
        private:
            f32 _zoom;
            Vec2f _scroll;

            /* Intermediate things */
            Vec2f _cursorPos;

            /* Properies */
            f32 _gridSize;

            f32 _zoomSpeed;
            f32 _maxZoom;
            f32 _minZoom;

            bool _renderAxis;
            bool _renderGrid;

            bool _renderScreenboxPreview;
            Vec2f _screenboxPreviewSize;
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<LevelPreviewWindow>;
            friend class LevelPreviewHelpWindow;

            LevelPreviewWindow();

            Vec2f get_scroll() const;

            f32 get_zoom() const;

            Vec2f get_curson_pos() const;

            f32 get_grid_size() const;

            void render_window() override;

            void render_properties() override;

            static LevelPreviewWindow& get_instance();
    };
}

template<>																	               
struct omni::reflector::Reflection<omniscia_editor::windows::LevelPreviewWindow> {									               
    const constexpr static std::type_info &typeInfo = typeid(omniscia_editor::windows::LevelPreviewWindow);           
    const constexpr static auto clearTypeName = "LevelPreviewWindow";
    const constexpr static auto meta = std::make_tuple(
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_gridSize, "Grid size"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_renderAxis, "Render axis"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_renderGrid, "Render grid"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_zoomSpeed, "Zoom zpeed"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_maxZoom, "Max zoom"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_minZoom, "Min zoom"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_renderScreenboxPreview, "Render screenbox preview"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_screenboxPreviewSize, "Screenbox preview size")
    );																		               
};

#endif
