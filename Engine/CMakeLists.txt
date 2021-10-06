file(   GLOB_RECURSE
        HEADER_LIST
        LIST_DIRECTORIES true
        CONFIGURE_DEPENDS
        "${engine_SOURCE_DIR}/Engine/include/*.hpp")

add_library(
        Engine

        STATIC

        src/Input/InputHandler.cpp
        src/Physics/IntegrationSystem.cpp
        src/Rendering/Renderable.cpp
        src/Rendering/Shader.cpp
        src/Rendering/ShaderManager.cpp
        src/Rendering/SpriteRender.cpp
        src/Windowing/Window.cpp

        ${HEADER_LIST})

target_include_directories(Engine PUBLIC ${engine_SOURCE_DIR})
target_include_directories(Engine PUBLIC ${HEADER_LIST})

target_link_libraries(Engine PUBLIC SDL2::SDL2)
target_link_libraries(Engine PUBLIC SDL2::SDL2_image)
target_link_libraries(Engine PUBLIC External)