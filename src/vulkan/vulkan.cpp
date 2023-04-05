#include "vulkan.hpp"

Triangle::Vulkan::Vulkan()
{
    _createInstance();
}

Triangle::Vulkan::~Vulkan()
{
    ::vkDestroyInstance(this->_instance, nullptr);
}

bool Triangle::Vulkan::_checkValidationLayerSupport(const std::vector<const char *> &validationLayers)
{
    uint32_t layerCount = 0;
    ::vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<::VkLayerProperties> availableLayers(layerCount);
    ::vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    for (const char *layerName : validationLayers)
    {
        bool layerFound = false;
        for (const auto &layerProperties : availableLayers)
        {
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }
        if (!layerFound)
        {
            return false;
        }
    }
    return true;
}

std::vector<const char *> Triangle::Vulkan::_getValidationLayers()
{
    static std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation",
    };

    if (!_checkValidationLayerSupport(validationLayers))
    {
        throw std::runtime_error("Validation layers requested, but not available!");
    }
    return validationLayers;
}

void Triangle::Vulkan::_createInstance()
{
#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    ::VkApplicationInfo appInfo = {};
    ::VkInstanceCreateInfo createInfo = {};
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions = nullptr;
    std::vector<const char *> requiredExtensions;

    appInfo.sType = ::VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    createInfo.sType = ::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    if (glfwExtensions == nullptr)
    {
        throw std::runtime_error("Failed to get required GLFW extensions");
    }

    for (uint32_t i = 0; i < glfwExtensionCount; i++)
    {
        requiredExtensions.push_back(glfwExtensions[i]);
    }
    requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    createInfo.flags |= ::VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

    if (enableValidationLayers)
    {
        std::vector<const char *> validationLayers = this->_getValidationLayers();

        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else
    {
        createInfo.enabledLayerCount = 0;
    }

    if (::vkCreateInstance(&createInfo, nullptr, &this->_instance) != ::VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create Vulkan instance");
    }
}