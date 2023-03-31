#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <fstream>
#include <string>
#include <unordered_map>

namespace omniscia::core {
    inline bool file_exist(const std::string& name) {
        std::ifstream f(name.c_str());
        return f.good();   
    }

    template<typename T>
    class Manager {
        public:
            static const T& get(const std::string& key);
            static void add_asset(const std::string& file_path, const std::string& key);
            static void load_assets();
    };
};

#endif
