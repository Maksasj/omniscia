#ifndef _OMNISCIA_EDITOR_FILE_EXPLORER_H_
#define _OMNISCIA_EDITOR_FILE_EXPLORER_H_

#include <string>
#include <Windows.h>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <functional>
#include <sstream>
#include <fstream>
#include <iostream>

#include "file_explorer_result.h"
#include "file_entry.h"

#include "../gfx.h"
#include "../types.h"

namespace omniscia_editor::editor {
    using namespace omni::types;
    namespace fs = std::filesystem;
    
    class FileExplorer {
        private:
            std::filesystem::path _currentPath;
            std::vector<FileEntry> _files;
            u64 _selectedFile;

            bool _hiddenFiles;
            
            const u64 _pathStringMaxSize = 256; 
            char textInputFieldBuffer[265];

            void reaload_files();

            FileExplorer(std::string _startFilePath);
        public:
            static FileExplorer& get_instance();

            FileExplorerResult render();
    };
}

#endif
