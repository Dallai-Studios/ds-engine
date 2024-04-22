#pragma once

#include <SDL2/SDL.h>
#include <string>

enum WindowDisplayMode {
    WINDOWED,
    FULLSCREEN,
    BORDERLESS
};

struct GraphicsConfig {
    int width;
    int height;
    const char* windowTitle;
    WindowDisplayMode displayMode;
};  

enum GraphicsAPI {
    SDL2
};

class Graphics {
    private:
        // This variable will store the last error message that occurred during 
        // the initialization of the graphics pipeline or maybe any other time to be honest.
        // this propertie cam be used to store any error message.
        std::string lastErrorMessage;

        // Define the selected graphics API of the engine. At the moment, only SDL2 is supported.
        // But in the future, we can add more APIs like OpenGL, Vulkan, DirectX, etc.
        GraphicsAPI selectedAPI;

        // this is the SDL2 window and renderer that will be used to render the game.
        SDL_Window* sdlWindow;
        SDL_Renderer* sdlRenderer;

        // This method will configure the SDL2 API to be used by the engine.
        bool ConfigureSDL2(GraphicsConfig config);

    public:
        Graphics() = default;
        ~Graphics();

        const std::string GetError() const { return this->lastErrorMessage; }

        bool Initialize(GraphicsAPI api, GraphicsConfig config);
        void Update();
        void Render();
};