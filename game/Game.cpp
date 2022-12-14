//
// Created by srijan on 9/3/22.
//

#include "Game.h"

Game::Game()
    : m_Window(sf::VideoMode(544, 544), "Sweep the mine", sf::Style::Titlebar | sf::Style::Close),
      m_OverlayRect(sf::Vector2f(544.0f, 544.0f))
{
    int width = m_Window.getSize().x;
    int height = m_Window.getSize().y;

    m_Board = std::make_shared<Board>(width, height, 32);
    m_OverlayRect.setFillColor(sf::Color(0x000000bb));

    // game over text
    m_GameOverText.setFont(Asset::font_Roboto);
    m_GameOverText.setString("Game Over");
    m_GameOverText.setCharacterSize(32);
    m_GameOverText.setStyle(sf::Text::Bold);
    m_GameOverText.setPosition(sf::Vector2f(width / 2.0 - 5 * 16, height / 3.0));

    // game win text
    m_GameWonText.setFont(Asset::font_Roboto);
    m_GameWonText.setString("You Won");
    m_GameWonText.setCharacterSize(36);
    m_GameWonText.setStyle(sf::Text::Bold);
    m_GameWonText.setPosition(sf::Vector2f(width / 2.0 - 4 * 18, height / 3.0));

    // game restart hint text
    m_RestartText.setFont(Asset::font_Roboto);
    m_RestartText.setString("Click anywhere to restart");
    m_RestartText.setCharacterSize(22);
    m_RestartText.setStyle(sf::Text::Italic);
    m_RestartText.setPosition(sf::Vector2f(width / 2.0 - 12 * 11, height / 3.0 + 50));
}

void Game::Run()
{
    while (m_Window.isOpen())
    {
        ProcessEvents();
        Update();
        Render();
    }
}

void Game::ProcessBoardEvents(sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        if (m_Board->IsGameOver()) {
            m_Board->Reset();
            return;
        }

        sf::Vector2i position = sf::Mouse::getPosition(m_Window);
        m_Board->Click(position);
    }
}

void Game::ProcessEvents()
{
    sf::Event event{};
    while (m_Window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_Window.close();

        ProcessBoardEvents(event);
    }
}

void Game::Update()
{
}

void Game::Render()
{
    m_Window.clear();
    m_Board->Render(m_Window);
    if (m_Board->IsGameOver()) {
        RenderGameOver(m_Window);
    }
    m_Window.display();
}

void Game::RenderGameOver(sf::RenderWindow &window)
{
    window.draw(m_OverlayRect);
    if (m_Board->IsComplete()) {
        window.draw(m_GameWonText);
    } else {
        window.draw(m_GameOverText);
    }
    window.draw(m_RestartText);
}