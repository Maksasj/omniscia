#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include <iostream>

#include "manager.h"
#include "texture_asset.h"

namespace omniscia::core {
    class TextureManager : Manager<TextureAsset> {
        private:
            TextureManager() {};
            TextureManager(TextureManager const&) {};
            void operator=(TextureManager const&) {};

        protected:
            std::unordered_map<std::string, TextureAsset> _data;
            
        public:
            TextureAsset& get(const std::string& key);
            void add_asset(const std::string& file_path, const std::string& key);
            void load_assets();

            static TextureManager& get_instance() {
                static TextureManager instance;
                return instance;
            }
    };
};

#endif
