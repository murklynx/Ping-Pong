#pragma once
#include "../Updatable.h"
#include "TwoPlayerState.h"
#include "../GameObjects/Paddle.h"
#include "../GameObjects/Ball.h"

class TwoPlayerState : public Updatable {
public:
    TwoPlayerState();
    void update(const sf::Time& deltaTime) override;

private:
    Paddle paddleLeft;
    Paddle paddleRight;
    Ball ball;

    sf::Text paddleLeftScoreText;
    int paddleLeftScore;

    sf::Text paddleRightScoreText;
    int paddleRightScore;

    sf::Text gameOverText;
    bool gameOver;

    sf::RectangleShape net;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};