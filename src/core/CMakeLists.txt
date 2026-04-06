# Core library
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS "**.cpp")
file(GLOB_RECURSE CORE_HEADERS CONFIGURE_DEPENDS "**.h")

add_library(core STATIC ${CORE_SOURCES} ${CORE_HEADERS})
target_include_directories(core PUBLIC ..)

# Dependencies
include(FetchContent)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(core PRIVATE ${OPENGL_gl_LIBRARY})

# glm
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(glm)
target_include_directories(core PUBLIC ${glm_SOURCE_DIR})
set_target_properties(glm PROPERTIES FOLDER "Dependencies")

# SDL3
set(SDL_TEST_LIBRARY OFF)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-3.4.4
    GIT_SHALLOW ON
    # First try to find the SDL3 package. If it is not found, build it from source.
    FIND_PACKAGE_ARGS COMPONENTS SDL3
)
FetchContent_MakeAvailable(SDL3)
# Move SDL3 libraries into dependencies folder when built from source.
if(TARGET SDL_uclibc)
    set_target_properties(SDL_uclibc PROPERTIES FOLDER "Dependencies")
endif()
if(TARGET SDL3-shared)
    set_target_properties(SDL3-shared PROPERTIES FOLDER "Dependencies")
endif()

target_link_libraries(core PRIVATE SDL3::SDL3)

if(WIN32)
    # Copy DLL files on Windows to the target app build folder.
    add_custom_command(TARGET core POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        ${SDL_DLL_TARGET_DIR}/SDL3.dll)
endif()

# Dear ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.92.7-docking
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(imgui)
set(IMGUI_INCLUDE_DIR ${imgui_SOURCE_DIR}/)
file(GLOB IMGUI_SOURCES ${imgui_SOURCE_DIR}/*.cpp)
file(GLOB IMGUI_HEADERS ${imgui_SOURCE_DIR}/*.h)
add_library(imgui STATIC
    ${IMGUI_SOURCES}
    ${IMGUI_HEADERS}
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.h ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC ${IMGUI_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
target_link_libraries(imgui PRIVATE ${OPENGL_LIBRARIES} SDL3::SDL3)
set_target_properties(imgui PROPERTIES FOLDER "Dependencies")

target_link_libraries(core PUBLIC imgui)

# ImGuizmo
FetchContent_Declare(
    imguizmo
    GIT_REPOSITORY https://github.com/CedricGuillemet/ImGuizmo.git
    GIT_TAG b10e91756d32395f5c1fefd417899b657ed7cb88
)
FetchContent_MakeAvailable(imguizmo)
set(imguizmo_INCLUDE_DIR ${imguizmo_SOURCE_DIR}/)
file(GLOB imguizmo_SOURCES ${imguizmo_SOURCE_DIR}/*.cpp)
file(GLOB imguizmo_HEADERS ${imguizmo_SOURCE_DIR}/*.h)
add_library(imguizmo STATIC
    ${imguizmo_SOURCES}
    ${imguizmo_HEADERS}
)

target_include_directories(imguizmo PUBLIC ${imguizmo_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
target_link_libraries(imguizmo PRIVATE imgui)
set_target_properties(imguizmo PROPERTIES FOLDER "Dependencies")

target_link_libraries(core PRIVATE imguizmo)
