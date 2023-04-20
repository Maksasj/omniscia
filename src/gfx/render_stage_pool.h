#ifndef _RENDER_STAGE_POOL_H_
#define _RENDER_STAGE_POOL_H_

#include <vector>

#include "render_stage.h"

namespace omniscia::gfx {
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
            RenderStage& add_stage(const RenderStageProp& prop = {}) {
                RenderStage* renderStage = new RenderStage(prop, _renderingStages.size());

                if(prop._textureBuffer != nullptr)
                    renderStage->bind_target_texture_buffer(prop._textureBuffer);

                _renderingStages.push_back(renderStage);
                _slowReferences[prop._stageName] = renderStage; 

                return *renderStage;
            }

            RenderStage& add_stage(const std::string& _renderingStageName) {
                RenderStage* renderStage = new RenderStage((RenderStageProp){}, _renderingStages.size());
                _renderingStages.push_back(renderStage);
                
                _slowReferences[_renderingStageName] = renderStage; 

                return *renderStage;
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