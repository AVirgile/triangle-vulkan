#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

namespace Triangle
{
    class Vulkan
    {
    public:
        Vulkan();
        ~Vulkan();

        Vulkan(const Vulkan &) = delete;
        Vulkan(Vulkan &&) = delete;
        Vulkan &operator=(const Vulkan &) = delete;

    private:
        void _createInstance();
        std::vector<const char *> _getValidationLayers();
        bool _checkValidationLayerSupport(const std::vector<const char *> &validationLayers);

        ::VkInstance _instance;
    };

}