#ifndef _OMNISCIA_EDITOR_ASSET_MANAGER_SYSTEM_H_
#define _OMNISCIA_EDITOR_ASSET_MANAGER_SYSTEM_H_

#include <iostream>
#include <string>

#include "../gfx.h"
#include "../types.h"

namespace omniscia_editor::systems {
    class AssetManager {
        private:
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<AssetManager>;
            friend class omni::reflector::serialization::JsonSerializer;

            virtual void reload_assets(const std::string& filePath) {}

            virtual u64 get_asset_count() { return 0; }

            virtual void render_asset_preview(const bool& fancyPreview) {}
    };
}

#endif
