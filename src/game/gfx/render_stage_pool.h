#ifndef _RENDER_STAGE_POOL_H_
#define _RENDER_STAGE_POOL_H_

#include <vector>

#include "render_stage.h"

namespace omniscia::gfx {
    using namespace omni::types;
    using namespace omniscia::gfx::sprite;
    using namespace omniscia::gfx::texture;

    class RenderStagePool {
        private:
            std::vector<RenderStage*> _renderingStages;
            std::unordered_map<std::string, RenderStage*> _slowReferences;
            
            RenderStagePool() {};
            RenderStagePool(const RenderStagePool&) {};
            void operator=(RenderStagePool const&) {};

        public:
            RenderStage& add_stage(const std::string& _renderingStageName) {
                RenderStage* renderStage = new RenderStage(_renderingStages.size());
                _renderingStages.push_back(renderStage);
                
                _slowReferences[_renderingStageName] = renderStage; 

                return *renderStage;
            }

            std::unordered_map<std::string, RenderStage*>& get_stages() {
                return _slowReferences;
            }

            i32 rendering_stage_count() const {
                return _renderingStages.size();
            }

            RenderStage* get_stage_by_name(const std::string& _stageName) {
                return _slowReferences[_stageName];
            }

            static RenderStagePool& get_instance() {
                static RenderStagePool pool;
                return pool;
            }
    };
}

#endif