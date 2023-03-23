#ifndef _SHADER_ASSET_H_
#define _SHADER_ASSET_H_

#include "shader_asset_type.h"
#include "asset.tpp"

namespace omniscia::core {
    class ShaderAsset : public Asset<ShaderAssetType> {
        static u32 _count;
        
        public:
            ShaderAsset();
            ShaderAsset(const std::string& file_path, const ShaderAssetType& shadeType);

            void load_asset();

            static u32 get_count();
    };
}

#endif