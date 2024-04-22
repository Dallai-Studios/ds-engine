#include "Engine.h"
#include "../tools/logger/Logger.h"

Engine::Engine() {
    Logger::Info("Engine constructor called. Configuring engine dependencies");
    this->ecsRegistry = std::make_unique<Registry>();
    Logger::Info("ECS Registry instantiated successfully");
    this->graphics = std::make_unique<Graphics>();
    Logger::Info("Graphics pipeline instantiated successfully");
}

Engine::~Engine() {
    Logger::Info("Engine is about to shut down. No process found to perform before shutting down.");
}

void Engine::Initialize(GraphicsAPI api, GraphicsConfig config) {
    if (!this->graphics->Initialize(api, config)) {
        Logger::Error(this->graphics->GetError());
        return;
    }

    Logger::Info("Graphics pipeline initialized successfully");

    this->isRunning = true;
}

void Engine::Update() {
    while(this->isRunning) {
        this->ProcessInput();
        this->Render();
    }
}

void Engine::ProcessInput() {

}

void Engine::Render() {
    this->graphics->Render();
}

void Engine::Run() {
    this->Render();
}

void Engine::Destroy() {

}
