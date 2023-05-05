/**
 * @file 
 * asset.tpp
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ASSET_H_
#define _ASSET_H_

#include <string>

#include "types.tpp"

namespace omniscia::core {
    using namespace omni::types;

    /**
     * @brief 
     * Asset - generic type for all assets, 
     * used by animation asset, texture, shader and etc.
     * 
     * @tparam T - asset base 
    */
    template<typename T>
    class Asset {
        protected:
            /** @brief Used for storing asset instance */
            T _asset;

            /** @brief file path to the asset */
            const std::string _filePath;
        public:
            /**
             * @brief Default construct
            */
            Asset() {}

            /**
             * @brief Creates new asset instance and stores file path to it
             * 
             * @param filePath path to the asset file
            */
            Asset(const std::string& filePath) : _filePath(filePath) {}

            /**
             * @brief 
             * Virtual method used for loading asset
            */
            virtual void load_asset() const {};

            /**
             * @brief Returns file path to the asset
             * 
             * @return file path to the asset file source
            */
            std::string get_file_path() const {
                return _filePath;
            }

            /**
             * @brief Returns pointer to raw asset data
             * 
             * @return Pointer to raw asset data
            */
            T* get_asset() {
                return &_asset;
            }

            /**
             * @brief Get current count of existing Asset instances
             * 
             * @return u32 representing the current count of Asset instances
            */
            static u32 get_count() { return 0; }
    };
}

#endif