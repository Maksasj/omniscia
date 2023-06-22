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

#include "omni_types.tpp"

namespace omniscia::core {
    using namespace omni::types;
    
    /**
     * @brief Properties singleton class, that will be used
     * for storing different app properties and settings
    */
    class Properties {
        private:

        public:
            /**
             * @brief Screen width size 
            */
            //static const u32 screenWidth = 1920; 
            static u32 screenWidth; 
            
            /**
             * @brief Screen height size 
            */
            //static const u32 screenHeight = 1080; 
            static u32 screenHeight; 
    };
}

#endif
