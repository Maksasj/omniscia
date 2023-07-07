#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_

#include <iostream>

#include "asset/font/font_asset.h"
#include "asset/texture/texture_manager.h"
#include "asset/manager.h"

namespace omniscia::core {
    using namespace omni::types;

    class FontManager : Manager<FontAsset> {
        private:
            FontManager() {};
            FontManager(FontManager const&) {};
            void operator=(FontManager const&) {};

        protected:
            std::unordered_map<std::string, FontAsset> _data;
            
        public:
            FontAsset& get(const std::string& key);

            void add_asset(const std::string& filePath, const std::string& key, const FontAssetProp& prop);
            
            void check_assets() const;

            static FontManager& get_instance() {
                static FontManager instance;
                return instance;
            }
    };
};

#endif
