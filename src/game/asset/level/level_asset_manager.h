#ifndef _LEVEL_ASSET_MANAGER_H_
#define _LEVEL_ASSET_MANAGER_H_

#include <iostream>

#include "level_asset.h"
#include "manager.h"

namespace omniscia::core {
    using namespace omni::types;

    class LevelAssetManager : Manager<LevelAsset> {
        private:
            LevelAssetManager() {};
            LevelAssetManager(LevelAssetManager const&) {};
            void operator=(LevelAssetManager const&) {};

        protected:
            std::unordered_map<std::string, LevelAsset> _data;
        
        public:
            LevelAsset* get(const std::string& key);

            void add_asset(const std::string& filePath, const std::string& key, const LevelAssetType& levelType);

            void check_assets() const;

            static LevelAssetManager& get_instance() {
                static LevelAssetManager instance;
                return instance;
            }
    };
};

#endif
