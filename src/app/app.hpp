#pragma once

namespace Triangle
{
    class App
    {
    public:
        void run();

    private:
        void initVulkan();
        void mainLoop();
        void cleanup();
    };
};
