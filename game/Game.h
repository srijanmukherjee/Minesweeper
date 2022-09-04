//
// Created by srijan on 9/3/22.
//

#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "Board.h"
#include "Asset.h"

class Game {
public:
    Game();
    void Run();

private:
    void RenderGameOver(sf::RenderWindow &window);
    void ProcessBoardEvents(sf::Event &event);
    void ProcessEvents();
    void Render();
    void Update();

private:
    sf::RenderWindow m_Window;
    std::shared_ptr<Board> m_Board;
    sf::RectangleShape m_OverlayRect;
    sf::Text m_GameOverText;
    sf::Text m_RestartText;
    sf::Text m_GameWonText;
};


#endif //MINESWEEPER_GAME_H
