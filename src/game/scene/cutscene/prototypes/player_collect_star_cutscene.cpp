#include "player_collect_star_cutscene.h"

omniscia::core::PlayerCollectStarCutscene::PlayerCollectStarCutscene(Shader* transitionStageShader) 
    : Cutscene({
        CE_Step {
            new CE_FindStaticEntityEvent<Player>((CE_FindStaticEntityProp){
                ._entityTmpName = "Player",
            }),
        },
        CE_Step {
            new CE_EntityCollectEvent((CE_EntityCollectProp){
                ._entityTmpName = "Player",
                ._amount = 1,
            }),
        },
}) {}
