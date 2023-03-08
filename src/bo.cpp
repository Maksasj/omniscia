#include "bo.h"

u32 omniscia::renderer::BO::get_id() const {
    return _ID; 
}

u32* omniscia::renderer::BO::get_id_ref() {
    return &_ID; 
}

