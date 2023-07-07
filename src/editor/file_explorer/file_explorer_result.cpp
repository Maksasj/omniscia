#include "file_explorer_result.h"

omniscia_editor::editor::FileExplorerResult::FileExplorerResult(bool selected, FileEntryType type, std::string path) {
    _selected = selected;
    _type = type;
    _path = path;
}
