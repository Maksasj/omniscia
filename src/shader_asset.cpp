#include "shader_asset.h"

omniscia::core::ShaderAsset::ShaderAsset() {

}

omniscia::core::ShaderAsset::ShaderAsset(const std::string& file_path, const ShaderAssetType& shaderType) : Asset(file_path) {
    _asset = shaderType;
}

void omniscia::core::ShaderAsset::load_asset() {
    //
}
