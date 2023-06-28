#ifndef _OMNISCIA_EDITOR_TEXTURE_ASSET_H_
#define _OMNISCIA_EDITOR_TEXTURE_ASSET_H_

#include "../gfx.h"
#include "../types.h"

namespace omniscia_editor::systems {
    using namespace omni::types;

    struct TextureAsset {
        std::string _filePath;

        i32 _width;
        i32 _height;
        u32 _texture;

        friend class omni::reflector::FieldFriendlyScope;
        friend class omni::reflector::Reflection<TextureAsset>;
        friend class omni::reflector::serialization::JsonSerializer;

        bool load_asset_from_file();
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia_editor::systems, TextureAsset, _filePath);

#endif