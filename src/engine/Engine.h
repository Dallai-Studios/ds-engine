#pragma once

#include <memory>
#include "ecs/ECS.h"
#include "pipelines/graphics/Graphics.h"

class Engine {
    private: 
        bool isRunning;
        std::unique_ptr<Graphics> graphics;
        std::unique_ptr<Registry> ecsRegistry;

    public:
        Engine();
        ~Engine();
        void Initialize(GraphicsAPI api, GraphicsConfig config);
        void Update();
        void ProcessInput();
        void Render();
        void Run();
        void Destroy();
};