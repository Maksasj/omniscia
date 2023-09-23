#include "history_window.h"

#include "systems/level_manager.h"

omniscia_editor::windows::HistoryWindow::HistoryWindow() {
    _visibleSteps = 8.0;
    _autoScroll = true;

    _massiveUndoTimesMax = 5;
};

void omniscia_editor::windows::HistoryWindow::record(const std::string& label) {
    const LevelData& levelData = systems::LevelManager::get_instance()._levelData;

    _history.push_back(HistoryRecord{ levelData, label });
} 

void omniscia_editor::windows::HistoryWindow::undo(const u64& times) {
    HistoryRecord topRecord;
    
    for(auto i = 0; i < std::min(times, _history.size()); ++i) {
        topRecord = _history[_history.size() - 1];
        _history.pop_back();
    }

    LevelData& levelData = systems::LevelManager::get_instance()._levelData;
    levelData = topRecord._levelData;
}

void omniscia_editor::windows::HistoryWindow::render_window() {
    if(!ImGui::Begin("History")) {
        ImGui::End();
        return;
    }

    if (ImGui::BeginChild("scrolling", ImVec2(-FLT_MIN, _visibleSteps * ImGui::GetTextLineHeightWithSpacing()), true, ImGuiWindowFlags_HorizontalScrollbar)) {
        
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
         
        for(const auto& record : _history) {
            ImGui::Text("%s", record._label.c_str());
        }

        ImGui::PopStyleVar();

        if (_autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);

        ImGui::EndChild();
    }

    ImGui::Text("Auto scroll");
    ImGui::SameLine();
    ImGui::Checkbox("## history auto scroll checkbox", &_autoScroll);
    
    ImGui::SameLine(ImGui::GetWindowSize().x - 2.0f * (ImGui::CalcTextSize("Undo 5 ").x + ImGui::GetStyle().FramePadding.x * 2.0f));

    if(ImGui::Button("Undo")) {
        undo(1);
    }

    ImGui::SameLine();
    if(ImGui::Button(("Undo " + std::to_string(_massiveUndoTimesMax)).c_str())) {
        undo(_massiveUndoTimesMax);
    }

    ImGui::End();
}

void omniscia_editor::windows::HistoryWindow::render_properties() {
    PropertiesFieldQuery::property_window_edit_query(*this);
}

omniscia_editor::windows::HistoryWindow& omniscia_editor::windows::HistoryWindow::get_instance() {
    static HistoryWindow window;
    return window;
}
