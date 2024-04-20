#include "Engine.h"
#include "../tools/logger/Logger.h"

Engine::Engine() {
    Logger::Info("Engine constructor called. Waiting for initialization to begin");
}

Engine::~Engine() {
    Logger::Info("Engine is about to shut down. No process found to perform before shutting down.");
}

void Engine::Run()
{
    
}