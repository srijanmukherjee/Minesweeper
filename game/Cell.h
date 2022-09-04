//
// Created by srijan on 9/3/22.
//

#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H

#include <SFML/Graphics.hpp>
#include <random>

#include "Asset.h"
#include "CellMeta.h"

class Cell {
public:
    Cell(float x, float y, float size, CellColorScheme scheme = CellColorScheme::Light);
    void Render(sf::RenderWindow &window);
    void Disable();
    void Reveal();
    bool IsRevealed() const;
    void SetType(CellType type);
    CellType GetType() const;
    int GetMineCount() const;
    void SetMineCount(int count);

private:
    void UpdateCellColor(sf::RenderWindow &window);

private:
    float m_X;
    float m_Y;
    float m_Size;
    int m_EnemyCount;
    bool m_Revealed = false;
    bool m_Disabled = false;

    CellType m_Type;
    CellColorScheme m_ColorScheme;
    sf::Color m_EnemyColor;
    sf::RectangleShape m_Rect;
    sf::CircleShape m_EnemyCircle;
    sf::Text m_Text;
};


#endif //MINESWEEPER_CELL_H
