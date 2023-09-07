#include "Game.h"
#include "States/MainMenuState.h"

int main() {
    auto& game = Game::getInstance();
    auto clock = sf::Clock();

    game.pushState(std::make_unique<MainMenuState>());
    while (game.isRunning()) {
        game.handleEvent();
        game.update(clock.restart());
        game.draw();
    }
}