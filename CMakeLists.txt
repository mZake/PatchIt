cmake_minimum_required(VERSION 3.15)
project(PatchIt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
    "Source/Core/Error.cpp"
    "Source/Core/IPS.cpp"
    "Source/Core/Debug.cpp"
)

set(INCLUDE_DIRS
    "Source/Core"
)

add_executable(App ${SOURCE_FILES})
target_include_directories(App PRIVATE ${INCLUDE_DIRS})
