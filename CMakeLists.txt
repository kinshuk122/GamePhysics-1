cmake_minimum_required(VERSION 3.20)

set(NAME "GamePhysics")
project(${NAME})

set(CMAKE_CXX_STANDARD 17)

# Include all files inside the scenes folder.
file(GLOB_RECURSE SCENES_SOURCES CONFIGURE_DEPENDS "src/scenes/**.cpp" "src/scenes/**.h")
# Create a filter in Visual Studio for all files in the scenes folder.
source_group("scenes" FILES ${SCENES_SOURCES})

# Set source files for executable.
add_executable(${NAME} "src/main.cpp" ${SCENES_SOURCES} "src/scenes/AssignmentTwo.h" "src/scenes/AssignmentTwo.cpp" "src/scenes/AssignmentFour.cpp" "src/scenes/AssignmentFour.h")

target_include_directories(${NAME} PRIVATE src)

# Set as the initial startup project.
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${NAME})

# Enable folders in Visual Studio.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Copy assets to the build directory.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(SDL_DLL_TARGET_DIR $<TARGET_FILE_DIR:${NAME}>)

# Include configuration for the core library.
add_subdirectory(src/core)

target_link_libraries(${NAME} PRIVATE core)
