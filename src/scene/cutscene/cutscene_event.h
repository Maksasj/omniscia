#ifndef _CUTSCENE_EVENT_H_
#define _CUTSCENE_EVENT_H_

#include "timesystem.h"

#include "cutscene_datapool_type.h"
#include "types.tpp"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_Prop {
        bool _pauseBeforeStart = false;
        f32 _pauseTimeBeforeStart = 0.0f;

        bool _pauseAfterFinishing = false;
        f32 _pauseTimeAfterFinishing = 0.0f;

        bool _pauseBetweenRepeats = false;
        f32 _pauseTimeBetweenRepeats = 0.0f;
        u64 _timesToRepeat = 1u;

        f32 _durationTime = 0.0f;
    };

    class CE_Event : public CE_Prop {
        private:
            bool _isStarted = false;

            u64 _reapetCounter = 0;
            f32 _pauseRepeatTime = -1.0f;
            f32 _pauseRepeatTimeCounter = 0.0f;

            f32 _startRequestTime = -1.0f;
            f32 _startTimeCounter = 0.0f;

            f32 _stopRequestTime = -1.0f;
            f32 _stopTimeCounter = 0.0f;

            f32 _durationRequestTime = -1.0f;
            f32 _durationTimeCounter = 0.0f;

            bool _isDone = false;

            CutsceneDataPoolType* _parrentCutsceneDataPool;
            
            bool try_start_internal() {
                if(_pauseBeforeStart) {
                    if(_startRequestTime < 0.0f)
                        _startRequestTime = Time::get_time();

                    // Calculate delta time from first try_start call
                    _startTimeCounter = Time::get_time() - _startRequestTime;

                    if(_startTimeCounter < _pauseTimeBeforeStart)
                        return false;
                }

                if(_pauseBetweenRepeats && _reapetCounter > 0) {
                    if(_pauseRepeatTime < 0.0f)
                        _pauseRepeatTime = Time::get_time();

                    _pauseRepeatTimeCounter = Time::get_time() - _pauseRepeatTime;

                    if(_pauseRepeatTimeCounter < _pauseTimeBetweenRepeats)
                        return false;
                }

                return true;
            }


        public:
            virtual ~CE_Event() = default;

            CE_Event(const CE_Prop& data = CE_Prop{}) : CE_Prop(data) {

            }

            CutsceneDataPoolType* get_cutscene_data_pool() {
                return _parrentCutsceneDataPool;
            }

            virtual void execute() {}

            void bind_cutscene_data_pool(CutsceneDataPoolType& cutsceneDataPool) {
                _parrentCutsceneDataPool = &cutsceneDataPool;
            }

            void increment_reapet_counter() { 
                _pauseRepeatTime = -1.0f;
                _pauseRepeatTimeCounter = 0.0f;

                ++_reapetCounter;
            }

            virtual void reset() = 0;

            void reset_base() {
                _isStarted = false;
                _reapetCounter = 0;
                _pauseRepeatTime = -1.0f;
                _pauseRepeatTimeCounter = 0.0f;

                _startRequestTime = -1.0f;
                _startTimeCounter = 0.0f;

                _stopRequestTime = -1.0f;
                _stopTimeCounter = 0.0f;

                _durationRequestTime = -1.0f;
                _durationTimeCounter = 0.0f;

                _isDone = false;
            }

            u64 get_reapet_counter() const { return _reapetCounter; }
            bool is_done_repeating() const { return _reapetCounter >= this->_timesToRepeat; }

            void done() {
                _isDone = true;
            }

            f32 get_current_duration() const {
                return _durationTimeCounter;
            }

            bool is_done() {
                if(_isDone)
                    return true;

                if(_reapetCounter < _timesToRepeat)
                    return false;

                if(_durationTime != 0.0f) {
                    if(_durationRequestTime < 0.0f) 
                        _durationRequestTime = Time::get_time();
                
                    _durationTimeCounter = Time::get_time() - _durationRequestTime;

                    if(_durationTimeCounter < _durationTime)
                        return false;
                }

                return true;
            }

            bool finishing() {
                if(!_pauseAfterFinishing)
                    return true;

                if(_stopRequestTime < 0.0f) 
                    _stopRequestTime = Time::get_time();

                _stopTimeCounter = Time::get_time() - _stopRequestTime;

                if(_stopTimeCounter < _pauseTimeAfterFinishing)
                    return false;

                return true;
            }

            void try_start() {
                _isStarted = try_start_internal();
            }

            bool is_started() const {
                return _isStarted;
            }
    };

}

#endif