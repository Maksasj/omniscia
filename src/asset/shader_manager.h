#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

#include <iostream>

#include "shader_asset.h"
#include "manager.h"

namespace omniscia::core {
    class ShaderManager : Manager<ShaderAsset> {
        private:
            ShaderManager() {};
            ShaderManager(ShaderManager const&) {};
            void operator=(ShaderManager const&) {};

        protected:
            std::unordered_map<std::string, ShaderAsset> _data;
        
        public:
            ShaderAsset* get(const std::string& key);
            void add_asset(const std::string& file_path, const std::string& key, const ShaderAssetType& shaderType);
            void load_assets();

            static ShaderManager& get_instance() {
                static ShaderManager instance;
                return instance;
            }
    };
};

#endif
