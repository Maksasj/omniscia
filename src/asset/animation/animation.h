/**
 * @file 
 * animation.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "asset.tpp"
#include "omni_types.tpp"

namespace omniscia::core {
    using namespace omni::types;

    /**
     * @brief
     * Animation - class used for storing all information related to a single 
     * animation instance, current frame, animation speed, etc. 
     */
    struct Animation {
        /** @brief UV size of the used texture */
        Vec2f _spriteUvSize;
        
        /** @brief UV frame size */
        Vec2f _spriteFrameSize;

        /** @brief Possition of the animation frame */
        Vec2f _startPossition;

        /** @brief Total frmae count */
        u64 _frameCount;

        /** @brief Direction of animation (in which direction frames will be stepped) */
        bool _direction;

        /** @brief Animation speed */
        u64 _animationSpeed;

        bool _continuous;

        /**
         * @brief Get animation frame uv size
         * 
         * @return Vec2f vector represents uv metrics of the current frame
         */
        Vec2f get_frame_size() const {
            return _spriteFrameSize;
        }

        /**
         * @brief Calculates new frame possition from provided frame
         * 
         * @param currentFrame - current frame
         * @return Vec2f Position of the frame at 'currentFrame'
        */
        Vec2f get_frame_offset(u32 currentFrame) const {
            if(_direction)
                return Vec2f{_startPossition.x + currentFrame*_spriteFrameSize.x, _startPossition.y};

            return Vec2f{_startPossition.x, _startPossition.y + _spriteFrameSize.y*currentFrame};
        }

        /**
         * @brief Get the total frame count on this animation
         * 
         * @return u64 total frame count 
        */
        u64 get_frame_count() {
            return _frameCount;
        }
    };
}

#endif