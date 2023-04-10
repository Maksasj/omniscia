/**
 * @file 
 * shader_asset_type.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _SHADER_ASSET_TYPE_H_
#define _SHADER_ASSET_TYPE_H_

#include "asset.tpp"

namespace omniscia::core {
    /**
     * @brief ShaderAssetType - enum used for describing shader type
    */
    enum ShaderAssetType {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };
}

#endif