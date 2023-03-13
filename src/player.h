#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"

#include "ecs_player_controller.h"
#include "ecs_positioned.h"

namespace omniscia::core {
    class Player : public Entity<10> {
        private:
            ECS_Index<ECS_PlayerController> pcIndex;
        public:
            Player() {
                pcIndex = component_сontainer.add_and_index(std::make_shared<ECS_PlayerController>());
            }

            void update() {
                std::shared_ptr<ECS_PlayerController> pc = ref<ECS_PlayerController>(pcIndex);
                ++pc.get()->pp;
            }

            int read() {
                std::shared_ptr<ECS_PlayerController> pc = ref<ECS_PlayerController>(pcIndex);

                return pc.get()->pp;
            }
    };
}

#endif

/*
class container { int array[1000]; }

class BaseClass { 
    container bag;

    BaseClass clone() {
        BaseClass a = *this;
        return a;
    } 
}

class ChildClass : BaseClass {
    ..
    int* element // reference to specifc element of 'container'
    ..
}

ChildClass child1;
ChildClass child2 = child1.clone(); // child2 - still references to child1 container element

That if 'int* element', would be some sort of relative 
poiter, akka delta from 'this' and actual location to element,
Will it work correctly ? Is it possible to breake this, with specific 
class instances(, akka if class instance have templated array instance) ? 

class ChildClass : BaseClass {
    ..
    relative_ptr<int> element // offset from 'this' to specific element of 'container' 
    ..
}
*/

