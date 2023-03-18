#ifndef _TIME_SYSTEM_H_
#define _TIME_SYSTEM_H_

#include <functional>
#include <chrono>

#include "types.tpp"

namespace omniscia::core {
    using namespace std::chrono;
    struct Time {
        private:
            steady_clock::time_point _firstTime;
            steady_clock::time_point _secondTime;
            f32 _deltaTime;
        public:
            template<u32 _milliseconds>
            static void run_every_n_milliseconds(const std::function<void()> lambda) {
                using namespace std::chrono;
                static auto begin = high_resolution_clock::now();
                auto end = high_resolution_clock::now();

                f64 delta = duration_cast<nanoseconds>(end - begin).count() * 0.000001f;
                if(delta > _milliseconds) {
                    lambda();
                    begin = high_resolution_clock::now();
                }
            }

            f32 get_delta_time() {
                return _deltaTime;
            }

            void start_delta_time_clock() {
                _firstTime = high_resolution_clock::now();
            }

            void stop_delta_time_clock() {
                _secondTime = high_resolution_clock::now();
                _deltaTime = duration_cast<nanoseconds>(_secondTime - _firstTime).count() * 0.000001f;
            }

            static Time& get_instance() {
                static Time instace;
                return instace;
            }
    };
}

#endif