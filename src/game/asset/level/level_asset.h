#ifndef _LEVEL_ASSET_H_
#define _LEVEL_ASSET_H_

#include "scene/scene_loader/scene_loader.h"
#include "asset/level/level_asset_type.h"
#include "asset/asset.tpp"

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