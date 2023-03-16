#ifndef _ASSET_H_
#define _ASSET_H_

#include <string>

namespace omniscia::core {
    template<typename T>
    class Asset {
        protected:
            T _asset;

            const std::string _file_path;
        public:
            Asset() {}
            Asset(const std::string& file_path) : _file_path(file_path) {}

            virtual void load_asset() const {};

            std::string get_file_path() const {
                return _file_path;
            }

            T* get_asset() {
                return &_asset;
            }
    };
}

#endif