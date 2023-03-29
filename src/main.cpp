#include <iostream>
#include "app/app.hpp"

int main(void)
{
    Triangle::App app;

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}