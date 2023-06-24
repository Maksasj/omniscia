#include "debug_info.h"

omniscia::core::DebugInfo::DebugMetrics& omniscia::core::DebugInfo::get_metrics() {
    return _metrics;
};

omniscia::core::DebugInfo& omniscia::core::DebugInfo::get_instance() {
    static DebugInfo instance;
    return instance;
}
