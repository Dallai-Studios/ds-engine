#include "Graphics.h"
#include <SDL2/SDL.h>

bool Graphics::ConfigureSDL2(GraphicsConfig config)
{
    if (!SDL_Init(SDL_INIT_EVERYTHING)) {
        this->lastErrorMessage = "Error trying to initialize SDL2: " + std::string(SDL_GetError());
        return false;
    }

    this->sdlWindow = SDL_CreateWindow(
        config.windowTitle,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        config.width,
        config.height,
        SDL_WINDOW_FULLSCREEN
    );

    if (!this->sdlWindow) {
        this->lastErrorMessage = "Error trying to create SDL Window: " + std::string(SDL_GetError());
        return false;
    }

    this->sdlRenderer = SDL_CreateRenderer(this->sdlWindow, -1, SDL_RENDERER_ACCELERATED);

    if (!this->sdlRenderer) {
        this->lastErrorMessage = "Error trying to create SDL Renderer" + std::string(SDL_GetError());
        return false;
    }

    return true;
}

Graphics::~Graphics() {
    if (this->selectedAPI == GraphicsAPI::SDL2) {
        SDL_DestroyRenderer(this->sdlRenderer);
        SDL_DestroyWindow(this->sdlWindow);
        SDL_Quit();
    }
}

bool Graphics::Initialize(GraphicsAPI api, GraphicsConfig config)
{
    this->selectedAPI = api;

    bool result = false;

    if (this->selectedAPI == GraphicsAPI::SDL2) {
        result = this->ConfigureSDL2(config);
    }

    return result;
}

void Graphics::Render() {
    SDL_SetRenderDrawColor(this->sdlRenderer, 0, 0, 0, 255);
    SDL_RenderClear(this->sdlRenderer);
    SDL_RenderPresent(this->sdlRenderer);
}