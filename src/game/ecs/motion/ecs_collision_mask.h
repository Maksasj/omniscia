/**
 * @file 
 * ecs_collision_mask.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_COLLISION_MASK_H_
#define _ECS_COMPONENT_COLLISION_MASK_H_

#include "entity.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    
    /**
     * @brief CollisionMask - enum that describes different
     * collision layers, used by collision detection components (aabb)
    */
    enum CollisionMask {
        /** @brief There is no collision mask */
        CollisionMask_None              = 0,
        
        /** @brief Collision with player entity */
        CollisionMask_Player            = 1 << 0,

        /** @brief Collision with ambient entity */
        CollisionMask_AmbientEntities   = 1 << 1,

        /** @brief Collision with tiles */
        CollisionMask_Tiles             = 1 << 2,
        
        CollisionMask_Interactable      = 1 << 3,

        CollisionMask_Deadly            = 1 << 4,
        
        /*
        CollisionMask_Layer6            = 1 << 4,
        CollisionMask_Layer7            = 1 << 5,
        CollisionMask_Layer8            = 1 << 6,
        CollisionMask_Layer9            = 1 << 7,
        CollisionMask_Layer10           = 1 << 8,
        CollisionMask_Layer11           = 1 << 9,
        CollisionMask_Layer12           = 1 << 10,
        CollisionMask_Layer13           = 1 << 11,
        CollisionMask_Layer14           = 1 << 12,
        CollisionMask_Layer15           = 1 << 13,
        CollisionMask_Layer16           = 1 << 14,
        CollisionMask_Layer17           = 1 << 15,
        CollisionMask_Layer18           = 1 << 16,
        CollisionMask_Layer19           = 1 << 17,
        CollisionMask_Layer20           = 1 << 18,
        CollisionMask_Layer21           = 1 << 19,
        CollisionMask_Layer22           = 1 << 20,
        CollisionMask_Layer23           = 1 << 21,
        CollisionMask_Layer24           = 1 << 22,
        CollisionMask_Layer25           = 1 << 23,
        CollisionMask_Layer26           = 1 << 24,
        CollisionMask_Layer27           = 1 << 25,
        CollisionMask_Layer28           = 1 << 26,
        CollisionMask_Layer29           = 1 << 27,
        CollisionMask_Layer30           = 1 << 28,
        CollisionMask_Layer31           = 1 << 29,
        CollisionMask_Layer32           = 1 << 30,
        */
    };
}

#endif
