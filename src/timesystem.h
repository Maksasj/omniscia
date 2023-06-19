/**
 * @file 
 * timesystem.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _TIME_SYSTEM_H_
#define _TIME_SYSTEM_H_

#include <functional>

#include "boost_includes.h"
#include "gfx.h"
#include "omni_types.tpp"

namespace omniscia::core {
    using namespace omni::types;

    /**
     * @brief Class used managin time
    */
    struct Time {
        private:
            /**
             * @brief Temprory value used for calculating delta time
            */
            f64 _firstTime;
            
            /**
             * @brief Temprory value used for calculating delta time
            */
            f64 _secondTime;

            /**
             * @brief Temprory value used for calculating delta time
            */
            f64 _deltaTime;

        public:
            /**
             * @brief Method that manages it run time, 
             * will run labda expression only ever 
             * n milliseconds
             * 
             * @tparam _milliseconds value of the n 
             * @param lambda expression to be runned everu n milliseconds
            */
            template <unsigned int _milliseconds>
            static void run_every_n_milliseconds(const std::function<void()>& lambda) {
                using namespace boost::chrono;
                static auto begin = high_resolution_clock::now();
                auto end = high_resolution_clock::now();

                double delta = duration_cast<nanoseconds>(end - begin).count() * 0.000001;
                if (delta > _milliseconds) {
                    lambda();
                    begin = high_resolution_clock::now();
                }
            }

            inline static f64 get_time() {
                return glfwGetTime();
            }

            /**
             * @brief Get the delta time
             * 
             * @return f32 delta time
            */
            f32 get_delta_time();
            
            /**
             * @brief Update delta time
            */
            void update_delta_time_clock();

            /**
             * @brief Get singleton instance of the time class
             * 
             * @return Time& reference to the time single ton instance
            */
            static Time& get_instance();
    };
}

#endif