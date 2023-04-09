#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include <iostream>

#include "sound_asset.h"
#include "manager.h"

#include "sound_fx.h"

namespace omniscia::core {
    class SoundManager : Manager<SoundAsset> {
        private:
            SoundManager() {};
            SoundManager(SoundManager const&) {};
            void operator=(SoundManager const&) {};

        protected:
            std::unordered_map<std::string, SoundAsset> _data;
        
        public:
            SoundAsset* get(const std::string& key);
            void add_asset(const std::string& file_path, const std::string& key);
            void check_assets() const;
            void load_assets();

            static SoundManager& get_instance() {
                static SoundManager instance;
                return instance;
            }
    };
};

#endif
