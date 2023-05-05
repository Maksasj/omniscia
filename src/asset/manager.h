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
#include <stdexcept>

namespace omniscia::core {
    using namespace omni::types;

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

    };
};

#endif
