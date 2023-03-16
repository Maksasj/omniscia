#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

#include <iostream>

#include "manager.h"
#include "shader_asset.h"

namespace omniscia::core {
    class ShaderManager : Manager<ShaderAsset> {
        protected:
            static std::unordered_map<std::string, ShaderAsset> _data;
        public:
            static ShaderAsset* get(const std::string& key);
            static void add_asset(const std::string& file_path, const std::string& key, const ShaderAssetType& shaderType);
            static void load_assets();
    };
};

#endif
