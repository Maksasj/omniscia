/**
 * @file 
 * manager.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <fstream>
#include <string>
#include <unordered_map>

namespace omniscia::core {

    /**
     * @brief Check if file exist
     * 
     * @param path - path to the file, that needed to be checked
     * @return true - file exist
     * @return false - file does not exist
     */
    inline bool file_exist(const std::string& path) {
        std::ifstream f(path.c_str());
        return f.good();   
    }

    /**
     * @brief Manager - generic class for all manager classes. Used for TextureManager,
     * ShaderManager, AnimationManager and etc. 

     * @tparam Type of the asset that will be stored in this manager instance 
     */
    template<typename T>
    class Manager {
        public:
            /**
             * @brief Returns existing Asset by it index
             * 
             * @param key of the needed asset
             * @return const T& returns
            */
            static const T& get(const std::string& key);

            /**
             * @brief Adds asset to asset manager, and binds it to provided key
             * 
             * @param filePath path to the asset file
             * @param key key that will be associated with this asset
            */
            static void add_asset(const std::string& filePath, const std::string& key);
            
            /**
             * @brief Loads all asset that are stored in this manager instance
            */
            static void load_assets();
    };
};

#endif
