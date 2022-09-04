//
// Created by srijan on 9/3/22.
//

#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <stack>

#include "Cell.h"

class Board {
public:
    Board(int width, int height, int size);
    void Render(sf::RenderWindow &window);
    void Click(sf::Vector2i &position);
    bool IsGameOver() const;
    bool IsComplete() const;
    void Reset();

private:
    void Die();
    void InitializeCells();
    void LoadMines(int exclude);
    void UpdateMineNeighbours(int idx);
    void Explode(int start_x, int start_y);
    std::vector<int> GetRandomIndices(int exclude);
    void IncrementCellEnemyCount(int x, int y);
    constexpr int CoordsToIndex(int x, int y) const;
    bool IsWithinBounds(sf::Vector2i &position) const;
    void CheckWin();

private:
    int m_Width;
    int m_Height;
    int m_Size;
    int m_Rows;
    int m_Cols;
    int m_CellsRevealed = 0;
    float m_MinePercentage = .1;
    bool m_Loaded = false;
    bool m_GameOver = false;
    bool m_Complete = false;
    std::vector<Cell> m_Cells;
};


#endif //MINESWEEPER_BOARD_H
