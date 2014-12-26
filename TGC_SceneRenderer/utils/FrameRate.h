#pragma once
#include <array>

namespace utils {
    class FrameRate {
        private:
            static FrameRate *framerateInstance;
            static int const NUM_FPS_SAMPLES = 32;
            std::array<double, NUM_FPS_SAMPLES> fpsSamples;
            int currentSample;
            double currentFramerate;
            double timeSum;
        public:
            double getCurrentFramerate() { return currentFramerate; };
            static FrameRate *Instance();
            // Calculates the average framerate based on NUM_FPS_SAMPLES
            void calculate(const double &deltaTime);
        protected:
            FrameRate(void);
    };
}