#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include "../vulkan/vulkan.hpp"

namespace Triangle
{
    class App
    {
    public:
        App(const int width, const int height, const std::string &title);
        ~App();

        App(const App &) = delete;
        App(App &&) = delete;
        App &operator=(const App &) = delete;
        void run();

    private:
        void initVulkan();
        void mainLoop();
        void cleanup();
        void initWindow();

        int _width = 800;
        int _height = 600;
        std::string _title = "Triangle";

        ::GLFWwindow *_window;
        std::unique_ptr<Vulkan> _vulkan;
    };
};
