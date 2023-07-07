#include "shader_asset.h"

omni::types::u32 omniscia::core::ShaderAsset::_count = 0;

omniscia::core::ShaderAsset::ShaderAsset() {
    ++_count;
}

omniscia::core::ShaderAsset::ShaderAsset(const std::string& filePath, const ShaderAssetType& shaderType) : Asset(filePath) {
    _asset = shaderType;
    ++_count;
}

void omniscia::core::ShaderAsset::load_asset() {
    //
}

omni::types::u32 omniscia::core::ShaderAsset::get_count() {
    return _count;
}
