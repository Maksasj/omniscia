#ifndef _SHADER_ASSET_H_
#define _SHADER_ASSET_H_

#include "asset.tpp"
#include "shader_asset_type.h"

namespace omniscia::core {
    class ShaderAsset : public Asset<ShaderAssetType> {
        public:
            ShaderAsset();
            ShaderAsset(const std::string& file_path, const ShaderAssetType& shadeType);

            void load_asset();
    };
}

#endif