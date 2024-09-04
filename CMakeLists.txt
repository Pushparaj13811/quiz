cmake_minimum_required(VERSION 3.10)

project(my_cpp_backend)

set(CMAKE_CXX_STANDARD 17)

# Specify the path to the CMake configuration files
set(cpprestsdk_DIR "/opt/homebrew/Cellar/cpprestsdk/2.10.19/lib/cmake/cpprestsdk")

# Find the cpprestsdk package
find_package(cpprestsdk REQUIRED)

# Find Boost
find_package(Boost REQUIRED COMPONENTS system thread chrono filesystem)

# Include directories
include_directories(${cpprestsdk_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

# Add your source files
add_executable(my_cpp_backend
    src/main.cpp
    src/routes.cpp
    src/models/user.cpp
    src/models/quiz.cpp
    src/utils/logger.cpp
    src/utils/database.cpp
    src/controllers/user_controller.cpp
    src/controllers/quiz_controller.cpp
)

# Link the cpprestsdk library and Boost components
target_link_libraries(my_cpp_backend
    cpprestsdk::cpprest
    ${Boost_LIBRARIES}
)
