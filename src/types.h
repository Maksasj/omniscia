#ifndef _OMMNISCIA_TYPES_H_
#define _OMMNISCIA_TYPES_H_

#include <cstdint>

typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;

typedef int8_t      i8;
typedef int16_t     i16;
typedef int32_t     i32;
typedef int64_t     i64;

typedef float       f32; 
typedef double      f64; 

namespace omniscia::core {
    struct Vec2f {
        f32 x;
        f32 y;

        Vec2f operator+(const Vec2f& vec) { return Vec2f{x + vec.x, y + vec.y }; }
        Vec2f operator-(const Vec2f& vec) { return Vec2f{x - vec.x, y - vec.y }; }
        Vec2f operator*(const Vec2f& vec) { return Vec2f{x * vec.x, y * vec.y }; }
        Vec2f operator/(const Vec2f& vec) { return Vec2f{x / vec.x, y / vec.y }; }
    };

    struct Vec3f : Vec2f {
        f32 z;

        Vec3f operator+(const Vec3f& vec) { return Vec3f{x + vec.x, y + vec.y, z + vec.z}; }
        Vec3f operator-(const Vec3f& vec) { return Vec3f{x - vec.x, y - vec.y, z - vec.z}; }
        Vec3f operator*(const Vec3f& vec) { return Vec3f{x * vec.x, y * vec.y, z * vec.z}; }
        Vec3f operator/(const Vec3f& vec) { return Vec3f{x / vec.x, y / vec.y, z / vec.z}; }

        Vec3f& operator+=(const Vec3f& vec){
            this->x += vec.x;
            this->y += vec.y;
            this->z += vec.z;
            return *this;
        }

        Vec3f& operator-=(const Vec3f& vec){
            this->x -= vec.x;
            this->y -= vec.y;
            this->z -= vec.z;
            return *this;
        }
    };

    struct Vec4f : Vec3f {
        f32 w;

        Vec4f operator+(const Vec4f& vec) { return Vec4f{x + vec.x, y + vec.y, z + vec.z, w + vec.w}; }
        Vec4f operator-(const Vec4f& vec) { return Vec4f{x - vec.x, y - vec.y, z - vec.z, w - vec.w}; }
        Vec4f operator*(const Vec4f& vec) { return Vec4f{x * vec.x, y * vec.y, z * vec.z, w * vec.w}; }
        Vec4f operator/(const Vec4f& vec) { return Vec4f{x / vec.x, y / vec.y, z / vec.z, w / vec.w}; }
    };

    struct Vec2i {
        i32 x;
        i32 y;

        Vec2i operator+(const Vec2i& vec) { return Vec2i{x + vec.x, y + vec.y }; }
        Vec2i operator-(const Vec2i& vec) { return Vec2i{x - vec.x, y - vec.y }; }
        Vec2i operator*(const Vec2i& vec) { return Vec2i{x * vec.x, y * vec.y }; }
        Vec2i operator/(const Vec2i& vec) { return Vec2i{x / vec.x, y / vec.y }; }
    };

    struct Vec3i : Vec2i {
        i32 z;

        Vec3i operator+(const Vec3i& vec) { return Vec3i{x + vec.x, y + vec.y, z + vec.z}; }
        Vec3i operator-(const Vec3i& vec) { return Vec3i{x - vec.x, y - vec.y, z - vec.z}; }
        Vec3i operator*(const Vec3i& vec) { return Vec3i{x * vec.x, y * vec.y, z * vec.z}; }
        Vec3i operator/(const Vec3i& vec) { return Vec3i{x / vec.x, y / vec.y, z / vec.z}; }
    };
}

#endif
