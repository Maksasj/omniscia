#include "bo.h"

omni::types::u32 omniscia::gfx::BO::get_id() const {
    return _ID; 
}

omni::types::u32* omniscia::gfx::BO::get_id_ref() {
    return &_ID; 
}
