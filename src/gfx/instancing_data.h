#ifndef _INSTANCING_DATA_H_
#define _INSTANCING_DATA_H_

#define UNIFORM_INSTANCING_DATA_SIZE 1000

#include "types.tpp"

namespace omniscia::gfx {
    struct InstancingData {
        Vec2f _position;
        Vec2f _scale;
        Vec2f _frameSize;
        Vec2f _frameOffset;
    };
}

#endif