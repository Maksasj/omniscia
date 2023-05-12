/**
 * @file 
 * types.tpp
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _OMMNISCIA_TYPES_H_
#define _OMMNISCIA_TYPES_H_

#include <cstdint>
#include <sstream>
#include <iostream>

namespace omni::types {
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

    /**
     * @brief Type that used as 2d geometrical vector
     * 
     * @tparam _T type of the vector
    */
    template<typename _T>
    struct Vec2 {
        /**
         * @brief Raw vector values
        */
        _T x;
        _T y;

        /**
         * @brief Some overoaded operators
        */
        Vec2 operator+(const Vec2& vec) { return Vec2{x + vec.x, y + vec.y }; }
        Vec2 operator-(const Vec2& vec) { return Vec2{x - vec.x, y - vec.y }; }

        Vec2 operator*(const _T& value) const { return Vec2{x * value, y * value }; }
        Vec2 operator/(const _T& value) const {
            if(value == 0) throw std::overflow_error("Divide by zero exception");

            return Vec2{x / value, y / value }; 
        }

        /* Vector x= Vector */
        Vec2<_T>& operator+=(const Vec2<_T>& other) { this->x += other.x; this->y += other.y; return *this; }
        Vec2<_T>& operator-=(const Vec2<_T>& other) { this->x -= other.x; this->y -= other.y; return *this; }
        Vec2<_T>& operator*=(const Vec2<_T>& other) { this->x *= other.x; this->y *= other.y; return *this; }
        Vec2<_T>& operator/=(const Vec2<_T>& other) { this->x /= other.x; this->y /= other.y; return *this; }

        /* Vector x= arbirary values */
        Vec2<_T>& operator+=(const _T& other) { this->x += other; this->y += other; return *this; }
        Vec2<_T>& operator-=(const _T& other) { this->x -= other; this->y -= other; return *this; }
        Vec2<_T>& operator*=(const _T& other) { this->x *= other; this->y *= other; return *this; }
        Vec2<_T>& operator/=(const _T& other) { this->x /= other; this->y /= other; return *this; }

        bool operator==(const Vec2<_T> other) { return this->x == other.x && this->y == other.y; }
        bool operator!=(const Vec2<_T> other) { return !this == other; }

        /**
         * @brief Puts string representation of the object to the out stream
         * 
         * @param os - reference to the out stream
         * @param vec - reference to the object instance
         * 
         * @return std::ostream& reference to the stream instance 
        */
        friend std::ostream& operator<<(std::ostream& os, const Vec2<_T>& vec) {
            os << vec.x << " " << vec.y;
            return os;
        }

        /**
         * @brief Constructs object from it string representation
         * 
         * @param os - reference to the in stream
         * @param vec - reference to the object instance
         * 
         * @return std::istream& reference to the stream instance 
        */
        friend std::istream& operator>>(std::istream& os, const Vec2<_T>& vec) {
            os >> vec.x >> vec.y;

            return os;
        } 

        /**
         * @brief Method used to get string representation of object instance
         * 
         * @return std::string string representation 
        */
        std::string to_string() const {
            std::stringstream ss;
            ss << x << ' ' << y;
            return ss.str();
        }
        
        /**
         * @brief Converts all values of the vector to their absolute values
         * 
         * @return Vec2<_T>& reference to vector instance
        */
        Vec2<_T>& abs() {
            if(this->x < 0) this->x = -this->x;
            if(this->y < 0) this->y = -this->y;
            return *this;
        }

        /**
         * @brief Calculates length of the vector
         * 
         * @return f32 length of the vector
        */
        f32 length() const {
            return sqrtf(this->x * this->x + this->y * this->y);
        }
    };

    /**
     * @brief Type that used as 3d geometrical vector
     * 
     * @tparam _T type of the vector
    */
    template<typename _T>
    struct Vec3 : Vec2<_T> {
        /**
         * @brief Raw vector values
        */
        _T z;

        /**
         * @brief Some overoaded operators
        */
        Vec3 operator+(const Vec3& vec) const { return Vec3{this->x + vec.x, this->y + vec.y, z + vec.z}; }
        Vec3 operator-(const Vec3& vec) const { return Vec3{this->x - vec.x, this->y - vec.y, z - vec.z}; }
        Vec3 operator*(const Vec3& vec) const { return Vec3{this->x * vec.x, this->y * vec.y, z * vec.z}; }
        Vec3 operator/(const Vec3& vec) const { return Vec3{this->x / vec.x, this->y / vec.y, z / vec.z}; }

        Vec3 operator*(const _T& value) const { return Vec3{this->x * value, this->y * value, this->z * value }; }
        Vec3 operator/(const _T& value) const { 
            if(value == 0) throw std::overflow_error("Divide by zero exception");

            return Vec3{this->x / value, this->y / value, this->z / value }; 
        }

        /* Vector x= Vector */
        Vec3<_T>& operator+=(const Vec3<_T>& other) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
        Vec3<_T>& operator-=(const Vec3<_T>& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
        Vec3<_T>& operator*=(const Vec3<_T>& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
        Vec3<_T>& operator/=(const Vec3<_T>& other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }
        
        /* Vector x= arbirary values */
        Vec3<_T>& operator+=(const _T& other) { this->x += other; this->y += other; this->z += other; return *this; }
        Vec3<_T>& operator-=(const _T& other) { this->x -= other; this->y -= other; this->z -= other; return *this; }
        Vec3<_T>& operator*=(const _T& other) { this->x *= other; this->y *= other; this->z *= other; return *this; }
        Vec3<_T>& operator/=(const _T& other) { this->x /= other; this->y /= other; this->z /= other; return *this; }

        operator Vec2<_T>() const { return Ve2<_T{this->x, this->y}; }

        bool operator==(const Vec3<_T> other) { return this->x == other.x && this->y == other.y && this->z == other.z; }
        bool operator!=(const Vec3<_T> other) { return !this == other; }

        /**
         * @brief Puts string representation of the object to the out stream
         * 
         * @param os - reference to the out stream
         * @param vec - reference to the object instance
         * 
         * @return std::ostream& reference to the stream instance 
        */
        friend std::ostream& operator<<(std::ostream& os, const Vec3<_T>& vec) {
            os << vec.x << " " << vec.y << " " << vec.z;
            return os;
        }

        /**
         * @brief Constructs object from it string representation
         * 
         * @param os - reference to the in stream
         * @param vec - reference to the object instance
         * 
         * @return std::istream& reference to the stream instance 
        */
        friend std::istream& operator>>(std::istream& os, const Vec3<_T>& vec) {
            os >> vec.x >> vec.y >> vec.z;

            return os;
        } 

        /**
         * @brief Method used to get string representation of object instance
         * 
         * @return std::string string representation 
        */
        std::string to_string() const {
            std::stringstream ss;
            ss << this->x << ' ' << this->y << ' ' << z;
            return ss.str();
        }

        /**
         * @brief Converts all values of the vector to their absolute values
         * 
         * @return Vec2<_T>& reference to vector instance
        */
        Vec3<_T>& abs() {
            if(this->x < 0) this->x = -this->x;
            if(this->y < 0) this->y = -this->y;
            if(this->z < 0) this->z = -this->z;
            return *this;
        }

        /**
         * @brief Calculates length of the vector
         * 
         * @return f32 length of the vector
        */
        _T length() const {
            return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
        }
    };

    /**
     * @brief Type that used as 4d geometrical vector
     * 
     * @tparam _T type of the vector
    */
    template<typename _T>
    struct Vec4 : Vec3<_T> {
        /**
         * @brief Raw vector values
        */
        _T w;

        /**
         * @brief Some overoaded operators
        */
        Vec4 operator+(const Vec4& vec) { return Vec4{this->x + vec.x, this->y + vec.y, this->z + vec.z, w + vec.w}; }
        Vec4 operator-(const Vec4& vec) { return Vec4{this->x - vec.x, this->y - vec.y, this->z - vec.z, w - vec.w}; }
        Vec4 operator*(const Vec4& vec) { return Vec4{this->x * vec.x, this->y * vec.y, this->z * vec.z, w * vec.w}; }
        Vec4 operator/(const Vec4& vec) { return Vec4{this->x / vec.x, this->y / vec.y, this->z / vec.z, w / vec.w}; }

        Vec4 operator*(const _T& value) { return Vec4{this->x * value, this->y * value, this->z * value, this->w * value }; }
        Vec4 operator/(const _T& value) { 
            if(value == 0) throw std::overflow_error("Divide by zero exception");

            return Vec4{ this->x / value, this->y / value, this->z / value, this->w / value }; 
        }

        /* Vector x= Vector */
        Vec4<_T>& operator+=(const Vec4<_T>& other) { this->x += other.x; this->y += other.y; this->z += other.z; this->w += other.w; return *this; }
        Vec4<_T>& operator-=(const Vec4<_T>& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; this->w -= other.w; return *this; }
        Vec4<_T>& operator*=(const Vec4<_T>& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; this->w *= other.w; return *this; }
        Vec4<_T>& operator/=(const Vec4<_T>& other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; this->w /= other.w; return *this; }

        /* Vector x= arbirary values */
        Vec4<_T>& operator+=(const _T& other) { this->x += other; this->y += other; this->z += other; this->w += other; return *this; }
        Vec4<_T>& operator-=(const _T& other) { this->x -= other; this->y -= other; this->z -= other; this->w -= other; return *this; }
        Vec4<_T>& operator*=(const _T& other) { this->x *= other; this->y *= other; this->z *= other; this->w *= other; return *this; }
        Vec4<_T>& operator/=(const _T& other) { this->x /= other; this->y /= other; this->z /= other; this->w /= other; return *this; }

        bool operator==(const Vec4<_T> other) { return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w; }
        bool operator!=(const Vec4<_T> other) { return !this == other; }

        /**
         * @brief Puts string representation of the object to the out stream
         * 
         * @param os - reference to the out stream
         * @param vec - reference to the object instance
         * 
         * @return std::ostream& reference to the stream instance 
        */
        friend std::ostream& operator<<(std::ostream& os, const Vec4<_T>& vec) {
            os << vec.x << " " << vec.y << " " << vec.z << " " << vec.w; 
            return os;
        } 

        /**
         * @brief Constructs object from it string representation
         * 
         * @param os - reference to the in stream
         * @param vec - reference to the object instance
         * 
         * @return std::istream& reference to the stream instance 
        */
        friend std::istream& operator>>(std::istream& os, const Vec4<_T>& vec) {
            os >> vec.x >> vec.y >> vec.z >> vec.w;

            return os;
        } 

        /**
         * @brief Method used to get string representation of object instance
         * 
         * @return std::string string representation 
        */
        std::string to_string() const {
            std::stringstream ss;
            ss << this->x << ' ' << this->y << ' ' << this->z << ' ' << w; 
            return ss.str();
        }

        /**
         * @brief Converts all values of the vector to their absolute values
         * 
         * @return Vec2<_T>& reference to vector instance
        */
        Vec4<_T>& abs() {
            if(this->x < 0) this->x = -this->x;
            if(this->y < 0) this->y = -this->y;
            if(this->z < 0) this->z = -this->z;
            if(this->w < 0) this->z = -this->w;
            return *this;
        }

        /**
         * @brief Calculates length of the vector
         * 
         * @return f32 length of the vector
        */
        f32 length() const {
            return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z,  + this->w * this->w);
        }
    };


    /**
     * @brief Type that used as mathematical matrix
     * 
     * @tparam _T type of the matrix
     * @tparam _width width of the matrix
     * @tparam _heigth height of the matrix
    */
    template<typename _T, u32 _width, u32 _heigth>
    struct Matrix {
        /**
         * @brief Raw matrix values
        */
        _T e[_width * _heigth];

        /**
         * @brief Static method that returns rotation matrix by angle
         * 
         * @param rotationAngle rotation angle
         * @return Matrix<f32, 2, 2> new matrix instance 
        */
        static Matrix<f32, 2, 2> get_rotation_matrix(const f32 &rotationAngle) {
            return {{(f32)cos(rotationAngle), -(f32)sin(rotationAngle), (f32)sin(rotationAngle), (f32)cos(rotationAngle)}};
        }

        /**
         * @brief Static method that returns zero rotation matrix by angle
         * 
         * @return Matrix<f32, 2, 2> new matrix instance 
        */
        static Matrix<f32, 2, 2> get_zero_rotation_matrix() {
            return {{ 1, 0, 0, 1 }};
        }

        /**
         * @brief Puts string representation of the object to the out stream
         * 
         * @param os - reference to the out stream
         * @param mat - reference to the object instance
         * 
         * @return std::ostream& reference to the stream instance 
        */
        friend std::ostream& operator<<(std::ostream& os, const Matrix<_T, _width, _heigth>& mat) {
            for(i32 i = 0; i < _width * _heigth; ++i)
                os << mat.e[i] << " ";

            return os;
        } 

        /**
         * @brief Constructs object from it string representation
         * 
         * @param os - reference to the in stream
         * @param mat - reference to the object instance
         * 
         * @return std::istream& reference to the stream instance 
        */
        friend std::istream& operator>>(std::istream& os, const Matrix<_T, _width, _heigth>& mat) {
            for(i32 i = 0; i < _width * _heigth; ++i)
                os >> mat.e[i];

            return os;
        } 

        /**
         * @brief Method used to get string representation of object instance
         * 
         * @return std::string string representation 
        */
        std::string to_string() const {
            std::stringstream ss;

            for(i32 i = 0; i < _width * _heigth; ++i)
                ss << e[i] << " ";
            
            return ss.str();
        }
    };

    template<typename T>
    inline T lerp(const T& start, const T& finish, const f32& t) {
        return (finish * t) + start * (1.0f - t);
    }

    template<typename T>
    inline T smoothstep(const T& start, const T& finish, const f32& t) {
        const f32 v1 = t * t;
        const f32 v2 = 1.0f - (1.0f - t) * (1.0f - t);
        const f32 newT = lerp(v1, v2, t);

        return lerp(start, finish, newT);
    }

    using Vec2f = Vec2<f32>;
    using Vec3f = Vec3<f32>;
    using Vec4f = Vec4<f32>;

    using Vec2i = Vec2<i32>;
    using Vec3i = Vec3<i32>;
    using Vec4i = Vec4<i32>;
}

#endif
