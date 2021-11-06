include_directories(${engine_SOURCE_DIR}/Engine/include)
include_directories(${engine_SOURCE_DIR}/External/include)

add_library(
        Engine

        STATIC

        src/Input/SDLInputHandler.cpp
        src/Input/InputContext.cpp
        src/Input/InputManager.cpp
        src/Input/InputContextParser.cpp

        src/Physics/Integration.cpp

        src/Rendering/Renderable.cpp
        src/Rendering/Shader.cpp
        src/Rendering/SpriteRendering.cpp

        src/Windowing/Window.cpp

        src/GUI/SystemInterface.cpp
        src/GUI/RenderInterface.cpp
        src/GUI/GuiManager.cpp

        src/Resources/ResourceHandler.cpp

        include/Collision/CollisionComponents.hpp
        include/Collision/CollisionSystem.hpp

        include/GLHelpers/GlHelper.hpp

        include/Global/Time/Time.hpp
        include/Global/Utilities/Logger.hpp
        include/Global/Utilities/RGBA.hpp
        include/Global/Components.hpp
        include/Global/Game.hpp
        include/Global/glPortableHeaders.hpp

        include/GUI/GuiManager.hpp
        include/GUI/RenderInterface.hpp
        include/GUI/SystemInterface.hpp

        include/Input/InputContext.hpp
        include/Input/InputContextParser.hpp
        include/Input/InputManager.hpp
        include/Input/InputStructures.hpp
        include/Input/SDLInputHandler.hpp

        include/Physics/Integration.hpp
        include/Physics/PhysicsComponents.hpp

        include/Rendering/Renderable.hpp
        include/Rendering/RenderingComponents.hpp
        include/Rendering/RenderingStructures.hpp
        include/Rendering/Shader.hpp
        include/Rendering/SpriteRendering.hpp

        include/Resources/ResourceHandler.hpp

        include/Scene/Scene.hpp

        include/Windowing/Window.hpp

        include/Camera/Camera2D.hpp)

#target_include_directories(Engine PUBLIC ${engine_SOURCE_DIR}/Engine/src)
target_include_directories(Engine PUBLIC ${engine_SOURCE_DIR}/Engine/include)
target_include_directories(Engine PUBLIC ${engine_SOURCE_DIR}/External/include)

target_link_libraries(Engine PUBLIC SDL2::SDL2)
target_link_libraries(Engine PUBLIC SDL2::SDL2_image)
target_link_libraries(Engine PUBLIC RmlCore RmlDebugger)
target_link_libraries(Engine PUBLIC External)
target_link_libraries(Engine PRIVATE tinyxml2::tinyxml2)