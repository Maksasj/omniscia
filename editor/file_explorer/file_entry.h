#ifndef _OMNISCIA_EDITOR_FILE_ENTRTY_H_
#define _OMNISCIA_EDITOR_FILE_ENTRTY_H_

#include "file_entry_type.h"

namespace omniscia_editor::editor {
    using namespace omni::types;

    struct FileEntry {
        FileEntryType _type;
        
        std::string _filePath;
        std::string _fileName;
        std::string _fileExtension;
        u64 _fileSize;
    };
}

#endif
