//
// Created by srijan on 9/3/22.
//

#include "Game.h"

Game::Game()
    : m_Window(sf::VideoMode(544, 544), "Sweep the mine", sf::Style::Titlebar | sf::Style::Close)
{
    m_Board = std::make_shared<Board>(544, 544, 32);
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
    m_Window.display();
}