#ifndef _SOUND_ASSET_H_
#define _SOUND_ASSET_H_

#include "asset.tpp"
#include "sound.h"

namespace omniscia::core {
    class SoundAsset : public Asset<Sound> {
        static u32 _count;
        
        public:
            SoundAsset();
            SoundAsset(const std::string& file_path);

            void load_asset();

            static u32 get_count();
    };
}

#endif