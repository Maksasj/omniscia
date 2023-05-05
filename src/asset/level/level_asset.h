#ifndef _LEVEL_ASSET_H_
#define _LEVEL_ASSET_H_

#include "scene_loader.h"
#include "level_asset_type.h"
#include "asset.tpp"

namespace omniscia::core {
    using namespace omni::types;

    class LevelAsset : public Asset<LevelAssetType> {
        private:
            static u32 _count;
        
        public:
            LevelAsset();
            
            LevelAsset(const std::string& filePath, const LevelAssetType& levelAssetType);

            void load_asset(Scene& scene);

            static u32 get_count();
    };
}

#endif