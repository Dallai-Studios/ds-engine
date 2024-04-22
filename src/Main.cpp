#include "engine/Engine.h"
#include <SDL2/SDL.h>
#include "tools/logger/Logger.h"
#include <glm/glm.hpp>

#define WIDTH 800
#define HEIGTH 600

int main(int argc, char* argv[]) {

    bool is_running = true;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* game_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGTH, 0);

    if (game_window == nullptr) {
        Logger::Error("Failed to create window" + std::string(SDL_GetError()));
        return 1;
    }

    SDL_Renderer* game_renderer = SDL_CreateRenderer(game_window, -1, SDL_RENDERER_ACCELERATED);

    if (game_renderer == nullptr) {
        Logger::Error("Failed to create renderer: " + std::string(SDL_GetError()));
        return 1;
    }

    SDL_Event game_event;

    while (is_running) {
        if (SDL_PollEvent(&game_event)) {
            if (game_event.type == SDL_QUIT) is_running = false;
            if (game_event.type == SDL_KEYDOWN) {
                if (game_event.key.keysym.sym == SDLK_ESCAPE) is_running = false;
            }
        }
    }

    SDL_RenderPresent(game_renderer);

    return 0;
}