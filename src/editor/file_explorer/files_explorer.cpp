#include "files_explorer.h"

void omniscia_editor::editor::FileExplorer::reaload_files() {
    _files.clear();
    for (const auto & entry : fs::directory_iterator(_currentPath)) {
        if(entry.path().extension().string() == ".sys") continue;
        
        if(!_hiddenFiles) {
            DWORD attributes = GetFileAttributes(entry.path().string().c_str());
            if (attributes & FILE_ATTRIBUTE_HIDDEN) continue;
        }

        FileEntryType type = _FILE;

        if(entry.is_directory()) {
            type = _DIRECTORY;
        }

        FileEntry file = (FileEntry) {
            ._type = type,

            ._filePath = entry.path().string(),
            ._fileName = entry.path().filename().string(),
            ._fileExtension = entry.path().extension().string(),
            ._fileSize = entry.file_size(),
        };

        _files.push_back(file);
    }

    sort(_files.begin(), _files.end(), [](const FileEntry& a, const FileEntry& b) {
        return (a._type > b._type) ? true : (a._type == b._type ? a._fileExtension > b._fileExtension : false);
    });
}

omniscia_editor::editor::FileExplorer::FileExplorer(std::string _startFilePath) {
    _currentPath = _startFilePath;
    _selectedFile = 0;
    _hiddenFiles = false;

    reaload_files();

    _startFilePath.copy(textInputFieldBuffer, _startFilePath.size());
}

omniscia_editor::editor::FileExplorer& omniscia_editor::editor::FileExplorer::get_instance() {
    static FileExplorer fileExplorer(fs::current_path().string()); //C:\\Programming\\c++\\omniscia\\assets

    return fileExplorer;
}

omniscia_editor::editor::FileExplorerResult omniscia_editor::editor::FileExplorer::render() {
    auto flag = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse;

    auto returnValue = FileExplorerResult(false);

    ImGui::SetNextWindowSize({550, 450});
    ImGui::Begin("File explorer", NULL, flag);

    if(ImGui::Button("Go up")) {
        if(_currentPath.has_parent_path()) {
            _currentPath = _currentPath.parent_path();
            reaload_files();
        }
    }
    
    ImGui::SameLine();
    ImGui::Text("%s", _currentPath.string().c_str());
    ImGui::BeginListBox("## File explorer list", ImVec2(-FLT_MIN, 20 * ImGui::GetTextLineHeightWithSpacing()));
    
    for(u64 i = 0; i < _files.size(); ++i) {
        auto& file =  _files[i];

        std::stringstream ss;

        if(file._type == _DIRECTORY) {
            ss << "[DIR] ";
        } else if(file._type == _FILE) {
            ss << "[_FILE] ";
        }

        ss << file._fileName;

        bool selected = (_selectedFile == i);
        if(ImGui::Selectable(ss.str().c_str(), selected)) {
            _selectedFile = i;

            if(selected)
                ImGui::SetItemDefaultFocus();

        };
        
        if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
            if(file._type == _FILE) {
                /* Select file and return */
                if(std::filesystem::exists(_files[_selectedFile]._filePath)) {
                    std::filesystem::directory_entry entry(_files[_selectedFile]._filePath);

                    FileEntryType type = _FILE;
                    if(entry.is_directory())
                        type = _DIRECTORY;

                    returnValue = FileExplorerResult(true, type, _files[_selectedFile]._filePath);
                }
            } else if(file._type == _DIRECTORY) {
                _currentPath = file._filePath;
                reaload_files();
            }
        };
    }

    ImGui::EndListBox();
    
    static u64 _prevSelectedFile = 0;

    if(_selectedFile != _prevSelectedFile && _selectedFile < _files.size()) {
        std::memset(textInputFieldBuffer, 0, _pathStringMaxSize);
        _files[_selectedFile]._filePath.copy(textInputFieldBuffer, _files[_selectedFile]._filePath.size());
        _prevSelectedFile = _selectedFile;
    }
    ImGui::InputText("## File path", textInputFieldBuffer, _pathStringMaxSize);
    
    ImGui::SameLine();
    if(ImGui::Button("Select") && _selectedFile < _files.size()) {

        /* Select file and return */
        if(std::filesystem::exists(textInputFieldBuffer)) {
            std::filesystem::directory_entry entry(textInputFieldBuffer);

            FileEntryType type = _FILE;
            if(entry.is_directory())
                type = _DIRECTORY;

            returnValue = FileExplorerResult(true, type, textInputFieldBuffer);
        }
    }
    
    ImGui::SameLine();
    if(ImGui::Button("Clear")) {
        std::memset(textInputFieldBuffer, 0, 64);
    }

    ImGui::SameLine();
    if(ImGui::Button("Reload")) {
        reaload_files();
    }

    if(ImGui::Checkbox("Hidden files", &_hiddenFiles)) {
        reaload_files();
    }

    ImGui::SameLine();

    if(_selectedFile < _files.size()) {
        auto& file = _files[_selectedFile];

        if(file._type == _DIRECTORY) {
            if(ImGui::Button("Open")) {
                _currentPath = file._filePath;
                reaload_files();
            }
        } else if(file._type == _FILE) {
            ImGui::Text("File size: %llu [bytes]", file._fileSize);
            ImGui::SameLine();
            ImGui::Text(", extension: '%s'", file._fileExtension.c_str());
        }
    }

    ImGui::End();

    return returnValue;
}
