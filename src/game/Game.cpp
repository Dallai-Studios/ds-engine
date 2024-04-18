#include "Game.h"

Game::Game() {
    std::cout << "Game constructor" << std::endl;
}

Game::~Game() {
    std::cout << "Game destructor" << std::endl;
}

void Game::Run()
{
    std::cout << "Game running" << std::endl;
}
