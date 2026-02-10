cmake_minimum_required(VERSION 3.10)
project(game)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable compile_commands.json generation for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add compiler definition
add_compile_definitions(_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH)

# --------------------------------------------------
# Sources
# --------------------------------------------------
file(GLOB SOURCES "src/*.cpp")

# ImGui core sources
set(IMGUI_SOURCES
    include/rlImGui/imgui/imgui.cpp
    include/rlImGui/imgui/imgui_draw.cpp
    include/rlImGui/imgui/imgui_widgets.cpp
    include/rlImGui/imgui/imgui_tables.cpp
)

# rlImGui source
set(RLIMGUI_SOURCES
    include/rlImGui/rlImGui.cpp
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${IMGUI_SOURCES}
    ${RLIMGUI_SOURCES}
)

# --------------------------------------------------
# Include directories
# --------------------------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include/raylib/include
    ${CMAKE_SOURCE_DIR}/include/rlImGui
    ${CMAKE_SOURCE_DIR}/include/rlImGui/imgui
)

# --------------------------------------------------
# Link raylib
# --------------------------------------------------
target_link_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include/raylib/lib
)

target_link_libraries(${PROJECT_NAME} raylib)

# Windows system libs required by raylib
if (WIN32)
    target_link_libraries(${PROJECT_NAME} winmm)
endif()

# --------------------------------------------------
# Copy raylib DLL next to the executable
# --------------------------------------------------
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/include/raylib/lib/raylib.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# --------------------------------------------------
# Copy compile_commands.json for clangd
# --------------------------------------------------
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
)
