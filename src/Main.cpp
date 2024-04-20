#include "engine/Engine.h"
#include <SDL2/SDL.h>
#include "tools/logger/Logger.h"

int main(int argc, char* argv[]) {
    bool isRunning = true;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    if (window == nullptr) {
        Logger::Error("Failed to create window" + std::string(SDL_GetError()));
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        Logger::Error("Failed to create renderer: " + std::string(SDL_GetError()));
        return 1;
    }

    SDL_Event gameEvent;

    while (isRunning) {
        if (SDL_PollEvent(&gameEvent)) {
            if (gameEvent.type == SDL_QUIT) isRunning = false;
            if (gameEvent.type == SDL_KEYDOWN) {
                if (gameEvent.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
            }
        }
    }

    SDL_RenderPresent(renderer);

    return 0;
}