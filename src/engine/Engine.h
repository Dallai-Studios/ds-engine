#pragma once

#include <iostream>

class Engine {
public:
    Engine();
    ~Engine();
    void Initialize();
    void Update();
    void ProcessInput();
    void Render();
    void Run();
    void Destroy();
};