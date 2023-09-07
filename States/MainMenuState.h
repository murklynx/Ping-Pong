#pragma once
#include <SFML/Audio.hpp>
#include "../Updatable.h"
#include "../GameObjects/Button.h"
#include "../GameObjects/Ball.h"
#include "../GameObjects/Paddle.h"

class MainMenuState : public Updatable {
public:
    MainMenuState();
    virtual void update(const sf::Time& deltaTime) override;
private:
    Button playButton;
    Button exitButton;

    sf::Text title;
    sf::Music music;

    Paddle backgroundPaddleLeft;
    Paddle backgroundPaddleRight;
    Ball backgroundBall;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};