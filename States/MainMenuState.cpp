#define _USE_MATH_DEFINES

#include "MainMenuState.h"
#include "SpacebarState.h"
#include "TwoPlayerState.h"
#include "../Game.h"
#include "../Collision.h"
#include <iostream>
#include <cmath>

MainMenuState::MainMenuState() {
    auto windowSize = Game::getInstance().getWindow().getSize();
    auto xPos = windowSize.x / 2.0f;
    auto yPos = windowSize.y / 2.0f;

    title.setFont(Game::getInstance().getFont());
    title.setCharacterSize(64);
    title.setString("Ping Pong");
    title.setOrigin(std::round(title.getLocalBounds().width / 2.0f), std::round(title.getLocalBounds().height / 2.0f));
    title.setPosition(xPos, yPos - 150.0f);

    playButton.setText("Play");
    playButton.onClick([&]() {
        music.stop();
        auto twoPlayerState = std::make_unique<TwoPlayerState>();
        auto spacebarState = std::make_unique<SpacebarState>(std::move(twoPlayerState));
        Game::getInstance().pushState(std::move(spacebarState));
        });
    playButton.setPosition(xPos, yPos);

    exitButton.setText("Quit");
    exitButton.onClick([]() { Game::getInstance().stop(); });
    exitButton.setPosition(xPos, yPos + 50.0f);

    backgroundPaddleLeft = Paddle{ sf::Vector2f{15, yPos}, Paddle::PaddleOrientation::LEFT };
    backgroundPaddleRight = Paddle{ sf::Vector2f{windowSize.x - 15.0f, yPos}, Paddle::PaddleOrientation::RIGHT };

    backgroundBall.setAngle(45);
    backgroundBall.setPosition(100, yPos);

    if (!music.openFromFile("assets/artblock.ogg")) {
        std::cout << "could not load assets/artblock.ogg";
        Game::getInstance().stop();
    }

    music.setLoop(true);
    music.play();
}

void MainMenuState::update(const sf::Time& deltaTime) {
    backgroundBall.update(deltaTime);
    playButton.update(deltaTime);
    exitButton.update(deltaTime);

    auto windowSize = Game::getInstance().getWindow().getSize();
    float ballTop = backgroundBall.getPosition().y - backgroundBall.getRadius();
    float ballBottom = backgroundBall.getPosition().y + backgroundBall.getRadius();
    int ballDirectionX = std::cos(backgroundBall.getAngle() * M_PI / 180) > 0 ? 1 : -1;

    float paddleLeftTop = backgroundPaddleLeft.getPosition().y - backgroundPaddleLeft.getLocalBounds().height / 2.0f;
    float paddleLeftBottom = backgroundPaddleLeft.getPosition().y + backgroundPaddleLeft.getLocalBounds().height / 2.0f;

    if (paddleLeftTop > ballTop && paddleLeftTop > 0.0f && ballDirectionX == -1) {
        backgroundPaddleLeft.moveUp(deltaTime);
    }

    if (paddleLeftBottom < ballBottom && paddleLeftBottom < windowSize.y && ballDirectionX == -1) {
        backgroundPaddleLeft.moveDown(deltaTime);
    }

    float paddleRightTop = backgroundPaddleRight.getPosition().y - backgroundPaddleRight.getLocalBounds().height / 2.0f;
    float paddleRightBottom = backgroundPaddleRight.getPosition().y + backgroundPaddleRight.getLocalBounds().height / 2.0f;

    if (paddleRightTop > ballTop && paddleRightTop > 0.0f && ballDirectionX == 1) {
        backgroundPaddleRight.moveUp(deltaTime);
    }
    else if (paddleRightBottom < ballBottom && paddleRightBottom < windowSize.y && ballDirectionX == 1) {
        backgroundPaddleRight.moveDown(deltaTime);
    }

    if (Collision::paddleCollidingWithBall(backgroundPaddleLeft, backgroundBall) ||
        Collision::paddleCollidingWithBall(backgroundPaddleRight, backgroundBall)) {

        Collision::applyCollisionOffset(backgroundBall, Ball::VectorComponent::X);
        backgroundBall.invert(Ball::VectorComponent::X);
    }

    if (Collision::ballCollidingWithWindow(backgroundBall, Collision::WindowBorder::TOP) ||
        Collision::ballCollidingWithWindow(backgroundBall, Collision::WindowBorder::BOTTOM)) {

        Collision::applyCollisionOffset(backgroundBall, Ball::VectorComponent::Y);
        backgroundBall.invert(Ball::VectorComponent::Y);
    }
}

void MainMenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(backgroundPaddleLeft, states);
    target.draw(backgroundPaddleRight, states);
    target.draw(backgroundBall, states);

    target.draw(playButton, states);
    target.draw(exitButton, states);
    target.draw(title, states);
}