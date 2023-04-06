#ifndef _IMAGE_LOADING_H_
#define _IMAGE_LOADING_H_

#include "gfx.h"
#include "types.h"

bool load_texture_from_file(const char* filename, GLuint* out_texture, i32* out_width, i32* out_height);

#endif