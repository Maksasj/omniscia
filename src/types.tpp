#ifndef _OMMNISCIA_TYPES_H_
#define _OMMNISCIA_TYPES_H_

#include <cstdint>
#include <sstream>
#include <iostream>

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using i8 = signed char;
using i16 = signed short;
using i32 = signed int;
using i64 = signed long long;

using f32 = float;
using f64 = double;

namespace omniscia::core {
    template<typename T>
    struct Vec2 {
        T x;
        T y;

        Vec2 operator+(const Vec2& vec) { return Vec2{x + vec.x, y + vec.y }; }
        Vec2 operator-(const Vec2& vec) { return Vec2{x - vec.x, y - vec.y }; }

        Vec2 operator*(const T& value) { return Vec2{x * value, y * value }; }
        Vec2 operator/(const T& value) { return Vec2{x / value, y / value }; }

        /* Vector x= Vector */
        Vec2<T>& operator+=(const Vec2<T>& other) { this->x += other.x; this->y += other.y; return *this; }
        Vec2<T>& operator-=(const Vec2<T>& other) { this->x -= other.x; this->y -= other.y; return *this; }
        Vec2<T>& operator*=(const Vec2<T>& other) { this->x *= other.x; this->y *= other.y; return *this; }
        Vec2<T>& operator/=(const Vec2<T>& other) { this->x /= other.x; this->y /= other.y; return *this; }

        /* Vector x= arbirary values */
        Vec2<T>& operator+=(const T& other) { this->x += other; this->y += other; return *this; }
        Vec2<T>& operator-=(const T& other) { this->x -= other; this->y -= other; return *this; }
        Vec2<T>& operator*=(const T& other) { this->x *= other; this->y *= other; return *this; }
        Vec2<T>& operator/=(const T& other) { this->x /= other; this->y /= other; return *this; }

        bool operator==(const Vec2<T> other) { return this->x == other.x && this->y == other.y; }
        bool operator!=(const Vec2<T> other) { return !this == other; }

        friend std::ostream& operator<<(std::ostream& os, const Vec2<T>& vec) {
            os << vec.x << " " << vec.y;
            return os;
        }

        std::string to_string() const {
            std::stringstream ss;
            ss << x << ' ' << y;
            return ss.str();
        }
        
        Vec2<T>& abs() {
            if(this->x < 0) this->x = -this->x;
            if(this->y < 0) this->y = -this->y;
            return *this;
        }

        f32 length() {
            return sqrtf(this->x * this->x + this->y);
        }
    };

    template<typename T>
    struct Vec3 : Vec2<T> {
        T z;

        Vec3 operator+(const Vec3& vec) { return Vec3{this->x + vec.x, this->y + vec.y, z + vec.z}; }
        Vec3 operator-(const Vec3& vec) { return Vec3{this->x - vec.x, this->y - vec.y, z - vec.z}; }
        Vec3 operator*(const Vec3& vec) { return Vec3{this->x * vec.x, this->y * vec.y, z * vec.z}; }
        Vec3 operator/(const Vec3& vec) { return Vec3{this->x / vec.x, this->y / vec.y, z / vec.z}; }

        Vec3 operator*(const T& value) { return Vec3{this->x * value, this->y * value, this->z * value }; }
        Vec3 operator/(const T& value) { return Vec3{this->x / value, this->y / value, this->z / value }; }

        /* Vector x= Vector */
        Vec3<T>& operator+=(const Vec3<T>& other) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
        Vec3<T>& operator-=(const Vec3<T>& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
        Vec3<T>& operator*=(const Vec3<T>& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
        Vec3<T>& operator/=(const Vec3<T>& other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }
        
        /* Vector x= arbirary values */
        Vec3<T>& operator+=(const T& other) { this->x += other; this->y += other; this->z += other; return *this; }
        Vec3<T>& operator-=(const T& other) { this->x -= other; this->y -= other; this->z -= other; return *this; }
        Vec3<T>& operator*=(const T& other) { this->x *= other; this->y *= other; this->z *= other; return *this; }
        Vec3<T>& operator/=(const T& other) { this->x /= other; this->y /= other; this->z /= other; return *this; }

        bool operator==(const Vec3<T> other) { return this->x == other.x && this->y == other.y && this->z == other.z; }
        bool operator!=(const Vec3<T> other) { return !this == other; }

        friend std::ostream& operator<<(std::ostream& os, const Vec3<T>& vec) {
            os << vec.x << " " << vec.y << " " << vec.z;
            return os;
        }

        std::string to_string() const {
            std::stringstream ss;
            ss << this->x << ' ' << this->y << ' ' << z;
            return ss.str();
        }

        Vec3<T>& abs() {
            if(this->x < 0) this->x = -this->x;
            if(this->y < 0) this->y = -this->y;
            if(this->z < 0) this->z = -this->z;
            return *this;
        }

        T length() {
            return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
        }
    };

    template<typename T>
    struct Vec4 : Vec3<T> {
        T w;

        Vec4 operator+(const Vec4& vec) { return Vec4{this->x + vec.x, this->y + vec.y, this->z + vec.z, w + vec.w}; }
        Vec4 operator-(const Vec4& vec) { return Vec4{this->x - vec.x, this->y - vec.y, this->z - vec.z, w - vec.w}; }
        Vec4 operator*(const Vec4& vec) { return Vec4{this->x * vec.x, this->y * vec.y, this->z * vec.z, w * vec.w}; }
        Vec4 operator/(const Vec4& vec) { return Vec4{this->x / vec.x, this->y / vec.y, this->z / vec.z, w / vec.w}; }

        Vec4 operator*(const T& value) { return Vec4{this->x * value, this->y * value, this->z * value, this->w * value }; }
        Vec4 operator/(const T& value) { return Vec4{this->x / value, this->y / value, this->z / value, this->w / value }; }

        /* Vector x= Vector */
        Vec4<T>& operator+=(const Vec4<T>& other) { this->x += other.x; this->y += other.y; this->z += other.z; this->w += other.w; return *this; }
        Vec4<T>& operator-=(const Vec4<T>& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; this->w -= other.w; return *this; }
        Vec4<T>& operator*=(const Vec4<T>& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; this->w *= other.w; return *this; }
        Vec4<T>& operator/=(const Vec4<T>& other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; this->w /= other.w; return *this; }

        /* Vector x= arbirary values */
        Vec4<T>& operator+=(const T& other) { this->x += other; this->y += other; this->z += other; this->w += other; return *this; }
        Vec4<T>& operator-=(const T& other) { this->x -= other; this->y -= other; this->z -= other; this->w -= other; return *this; }
        Vec4<T>& operator*=(const T& other) { this->x *= other; this->y *= other; this->z *= other; this->w *= other; return *this; }
        Vec4<T>& operator/=(const T& other) { this->x /= other; this->y /= other; this->z /= other; this->w /= other; return *this; }

        bool operator==(const Vec4<T> other) { return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w; }
        bool operator!=(const Vec4<T> other) { return !this == other; }

        friend std::ostream& operator<<(std::ostream& os, const Vec4<T>& vec) {
            os << vec.x << " " << vec.y << " " << vec.z << " " << vec.w; 
            return os;
        }

        std::string to_string() const {
            std::stringstream ss;
            ss << this->x << ' ' << this->y << ' ' << this->z << ' ' << w; 
            return ss.str();
        }

        Vec4<T>& abs() {
            if(this->x < 0) this->x = -this->x;
            if(this->y < 0) this->y = -this->y;
            if(this->z < 0) this->z = -this->z;
            if(this->w < 0) this->z = -this->w;
            return *this;
        }

        f32 length() {
            return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z,  + this->w * this->w);
        }
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
