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
    template<typename T>
    struct Vec2 {
        T x;
        T y;

        Vec2 operator+(const Vec2& vec) { return Vec2{x + vec.x, y + vec.y }; }
        Vec2 operator-(const Vec2& vec) { return Vec2{x - vec.x, y - vec.y }; }
        Vec2 operator*(const Vec2& vec) { return Vec2{x * vec.x, y * vec.y }; }
        Vec2 operator/(const Vec2& vec) { return Vec2{x / vec.x, y / vec.y }; }
    };

    template<typename T>
    struct Vec3 : Vec2<T> {
        T z;

        Vec3 operator+(const Vec3& vec) { return Vec3{x + vec.x, y + vec.y, z + vec.z}; }
        Vec3 operator-(const Vec3& vec) { return Vec3{x - vec.x, y - vec.y, z - vec.z}; }
        Vec3 operator*(const Vec3& vec) { return Vec3{x * vec.x, y * vec.y, z * vec.z}; }
        Vec3 operator/(const Vec3& vec) { return Vec3{x / vec.x, y / vec.y, z / vec.z}; }

        Vec3& operator+=(const Vec3& vec){
            this->x += vec.x;
            this->y += vec.y;
            this->z += vec.z;
            return *this;
        }

        Vec3& operator-=(const Vec3& vec){
            this->x -= vec.x;
            this->y -= vec.y;
            this->z -= vec.z;
            return *this;
        }
    };

    template<typename T>
    struct Vec4 : Vec3<T> {
        f32 w;

        Vec4 operator+(const Vec4& vec) { return Vec4{x + vec.x, y + vec.y, z + vec.z, w + vec.w}; }
        Vec4 operator-(const Vec4& vec) { return Vec4{x - vec.x, y - vec.y, z - vec.z, w - vec.w}; }
        Vec4 operator*(const Vec4& vec) { return Vec4{x * vec.x, y * vec.y, z * vec.z, w * vec.w}; }
        Vec4 operator/(const Vec4& vec) { return Vec4{x / vec.x, y / vec.y, z / vec.z, w / vec.w}; }
    };


    template<typename T, u32 _width, u32 _heigth>
    struct Matrix {
        T e[_width * _heigth];

        static Matrix<f32, 2, 2> get_rotation_matrix(const f32 &rotationAngle) {
            return {{cos(rotationAngle), -sin(rotationAngle), sin(rotationAngle), cos(rotationAngle)}};
        }

        static Matrix<f32, 2, 2> get_zero_rotation_matrix() {
            return {{ 1, 0, 0, 1 }};
        }
    };

    using Vec2f = Vec2<f32>;
    using Vec3f = Vec3<f32>;
    using Vec4f = Vec4<f32>;

    using Vec2i = Vec2<i32>;
    using Vec3i = Vec3<i32>;
    using Vec4i = Vec4<i32>;
}

#endif
