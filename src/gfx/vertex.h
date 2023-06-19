/**
 * @file 
 * vertex.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <sstream>

#include "omni_types.tpp"
#include "gfx.h"

namespace omniscia::gfx {
    using namespace omni::types;

    /**
     * @brief Vertex - structure used for storing all 
     * opengl vertex data(pos, color and texture coordinates) 
    */
    struct Vertex {
        /** @brief Position of the vertex */
        Vec3f _pos;
        
        /** @brief Color of the vertex */
        Vec3f _color;
        
        /** @brief Texture coordinates of the vertex */
        Vec2f _texPos;

        /**
         * @brief Default constructor of the vertex structure
         * 
         * @param pos position of the vertex
         * @param color color of the vertex
         * @param texPos texture coordinates of the vertex
        */
        Vertex(const Vec3f& pos, const Vec3f& color, const Vec2f& texPos);

        /**
         * @brief Scales Vertex(position) by some value
         * 
         * @param scale by which scale vertex position 
        */
        void scale(const Vec3f& scale);

        /**
         * @brief Moves Vertex position by specifci value
         * 
         * @param pos possition by which to move vertex 
        */
        void transform(const Vec3f& pos = Vec3f{0.0f, 0.0f, 0.0f});

        /**
         * @brief Rotates vertex by some angle
         * 
         * @param angle by which vertex should be rotated 
        */
        void rotate(const f32& angle);

        /**
         * @brief Get string representation of the vertex
         * 
         * @return string representation of the vetex
        */
        std::string to_string() const;
    };
}

#endif