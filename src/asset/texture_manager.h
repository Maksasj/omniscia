#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include <iostream>

#include "manager.h"
#include "texture_asset.h"

namespace omniscia::core {
    class TextureManager : Manager<TextureAsset> {
        protected:
            static std::unordered_map<std::string, TextureAsset> _data;
        public:
            static TextureAsset& get(const std::string& key);
            static void add_asset(const std::string& file_path, const std::string& key);
            static void load_assets();
    };
};

#endif
