#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "asset.tpp"
#include "types.tpp"

namespace omniscia::core {
    struct Animation {
        Vec2f _spriteUvSize;
        Vec2f _spriteFrameSize;
        Vec2f _startPossition;

        u64 _frameCount;
        bool _direction;

        u64 _animationSpeed;

        Vec2f get_frame_size() const {
            return _spriteFrameSize;
        }

        Vec2f get_frame_offset(u32 currentFrame) const {
            if(_direction)
                return Vec2f{_startPossition.x + currentFrame*_spriteFrameSize.x, _startPossition.y};

            return Vec2f{_startPossition.x, _startPossition.y + _spriteFrameSize.y*currentFrame};
        }

        u64 get_frame_count() {
            return _frameCount;
        }
    };
}

#endif