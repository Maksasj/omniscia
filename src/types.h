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
    };

    struct Vec3f : Vec2f {
        f32 z;
    };

    struct Vec4f : Vec3f {
        f32 w;
    };

    struct Vec2i {
        i32 x;
        i32 y;
    };

    struct Vec3i : Vec2i {
        i32 z;
    };
}

#endif
