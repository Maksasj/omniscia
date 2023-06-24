/**
 * @file 
 * properties.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _OMMNISCIA_PROPERTIES_H_
#define _OMMNISCIA_PROPERTIES_H_

// #define OMNI_TYPES_ENABLE_REFLECTIONS 
#include "omni_types.tpp"

// #define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::reflector;

    /**
     * @brief Properties singleton class, that will be used
     * for storing different app properties and settings
    */
    class Properties {
        public:
            u32 screenWidth;
            u32 screenHeight;

        private:
            Properties() {
                screenWidth = 1280;
                screenHeight = 720;
            }

        public:
            static Properties& get_instance() {
                static Properties editor;
                return editor;
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core, Properties, screenWidth, screenHeight);

#endif
