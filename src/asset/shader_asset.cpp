#include "shader_asset.h"

u32 omniscia::core::ShaderAsset::_count = 0;

omniscia::core::ShaderAsset::ShaderAsset() {
    ++_count;
}

omniscia::core::ShaderAsset::ShaderAsset(const std::string& file_path, const ShaderAssetType& shaderType) : Asset(file_path) {
    _asset = shaderType;
    ++_count;
}

void omniscia::core::ShaderAsset::load_asset() {
    //
}

u32 omniscia::core::ShaderAsset::get_count() {
    return _count;
}
