#include "engine/Engine.h"
#include "engine/pipelines/graphics/Graphics.h"
#include <SDL2/SDL.h>
#include "tools/logger/Logger.h"
#include <glm/glm.hpp>

#define WIDTH 800
#define HEIGTH 600

int main(int argc, char* argv[]) {
    GraphicsConfig config;
    config.width = WIDTH;
    config.height = HEIGTH;
    config.windowTitle = "Game";

    std::unique_ptr<Engine> engine = std::make_unique<Engine>();

    engine->Initialize(GraphicsAPI::SDL2, config);

    engine->Run();

    return 0;
}