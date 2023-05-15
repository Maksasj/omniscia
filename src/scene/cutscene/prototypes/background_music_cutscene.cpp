#include "background_music_cutscene.h"

omniscia::core::BackgroundMusicCutscene::BackgroundMusicCutscene() 
    : EndlessCutscene({
        CE_Step {
            new CE_SoundLoopCutsceneEvent((CE_SoundLoopCutsceneProp) {
                ._soundId = "d264", 
            }),
        },
}) {}
