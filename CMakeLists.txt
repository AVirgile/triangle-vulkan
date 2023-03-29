cmake_minimum_required(VERSION 3.2)
project(TriangleVulkan)

set(GLM_DIR ./deps/glm)

find_package(GLM REQUIRED)
find_package(glfw3 3.3.8 REQUIRED)
find_package(Vulkan REQUIRED)


set(CMAKE_CXX_STANDARD 17)
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "G++ detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror --std=c++17")
endif(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE SRC_FILES src/*.cpp)
include_directories(${CURL_INCLUDE_DIRS})
add_executable(TriangleVulkan ${SRC_FILES})
target_link_libraries(TriangleVulkan PRIVATE glm::glm glfw)
target_include_directories(TriangleVulkan PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(TriangleVulkan PRIVATE ${Vulkan_LIBRARIES})
target_include_directories(TriangleVulkan PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
