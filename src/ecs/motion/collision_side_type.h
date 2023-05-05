/**
 * @file 
 * collision_side_type.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _COLLISION_SIDE_TYPE_H_
#define _COLLISION_SIDE_TYPE_H_

namespace omniscia::core::ecs {    
    /**
     * @brief CollisionSide - enum used for storing 
     * from which side collision acquired
    */
    enum CollisionSide {
        /** @brief There is no collision */
        NONE,
        
        /** @brief Collision from left side */
        LEFT,
        
        /** @brief Collision from right side */
        RIGHT,

        /** @brief Collision from top side */
        TOP,

        /** @brief Collision from bottom side */
        BOTTOM
    };
}

#endif
