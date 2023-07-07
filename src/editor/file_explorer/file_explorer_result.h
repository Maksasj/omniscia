#ifndef _OMNISCIA_EDITOR_FILE_EXPLORER_RESULT_H_
#define _OMNISCIA_EDITOR_FILE_EXPLORER_RESULT_H_

#include "file_entry_type.h"

namespace omniscia_editor::editor {
    using namespace omni::types;

    struct FileExplorerResult {
        bool _selected;
        FileEntryType _type;
        std::string _path;

        FileExplorerResult(bool selected, FileEntryType type = _FILE, std::string path = "");
    };
}

#endif
