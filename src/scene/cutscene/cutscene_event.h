#ifndef _CUTSCENE_EVENT_H_
#define _CUTSCENE_EVENT_H_

namespace omniscia::core {
    struct CE_Prop {
        /** @brief Is Cutscene event will last for one game update */
        bool _is_continues = false;

        bool _pause_after_finishing = false;
        f32 _pause_time_after_finishing = 0.0f;

        bool _pause_before_start = false;
        f32 _pause_time_before_start = 0.0f;

        u64 _times_to_repeat = 1u;
    };

    struct CE_Event : public CE_Prop {
        CE_Event(const CE_Prop& data = CE_Prop{}) : CE_Prop(data) {

        }

        virtual void run() {}
    };

}

#endif