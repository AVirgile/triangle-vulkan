#include "app.hpp"

Triangle::App::App(const int width, const int height, const std::string &title)
    : _width(width), _height(height), _title(title)
{
    this->_window = nullptr;
    this->initWindow();
    this->initVulkan();
}

void Triangle::App::run()
{
    this->mainLoop();
}

void Triangle::App::initWindow()
{
    ::glfwInit();

    ::glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    ::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->_window = ::glfwCreateWindow(this->_width, this->_height, this->_title.c_str(), nullptr, nullptr);
    if (this->_window == nullptr)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }
}

void Triangle::App::initVulkan()
{
    this->_vulkan = std::make_unique<Triangle::Vulkan>();
}

void Triangle::App::mainLoop()
{
    while (!glfwWindowShouldClose(this->_window))
    {
        glfwPollEvents();
    }
}

void Triangle::App::cleanup()
{
    ::glfwDestroyWindow(this->_window);
    ::glfwTerminate();
}

Triangle::App::~App()
{
    this->cleanup();
}
