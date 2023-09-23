#ifndef _CUTSCENE_DATA_POOL_TYPE_H_
#define _CUTSCENE_DATA_POOL_TYPE_H_

#include <unordered_map>
#include <memory>

namespace omniscia::core {
    using namespace omni::types;
    
    using CutsceneDataPoolType = std::unordered_map<std::string, std::shared_ptr<void>>;
}

#endif