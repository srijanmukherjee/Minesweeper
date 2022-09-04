//
// Created by srijan on 9/3/22.
//

#include "Board.h"

#include <iostream>

Board::Board(int width, int height, int size)
    : m_Width(width), m_Height(height), m_Size(size)
{
    m_Rows = m_Height / m_Size;
    m_Cols = m_Width / m_Size;
    InitializeCells();
}

void Board::InitializeCells()
{
    CellColorScheme colorscheme = CellColorScheme::Light;
    m_Cells.clear();
    for (int i = 0; i < m_Rows; i++)
    {
        for (int j = 0; j < m_Cols; j++)
        {
            m_Cells.emplace_back(j, i, m_Size, colorscheme);
            colorscheme = colorscheme == CellColorScheme::Light ? CellColorScheme::Dark : CellColorScheme::Light;
        }
    }
}

void Board::Click(sf::Vector2i &position)
{
    if (!IsWithinBounds(position)) return;

    int x = position.x / m_Size;
    int y = position.y / m_Size;
    int idx = y * m_Cols + x;

    if (!m_Loaded)
    {
        LoadMines(idx);
        m_Loaded = true;
    }

    if (m_Cells[idx].GetType() == CellType::Mine)
    {
        Die();
        return;
    }

    if (!m_Cells[idx].IsRevealed())
    {
        Explode(x, y);
    }
}

void Board::Explode(int start_x, int start_y)
{
    std::stack<std::pair<int, int>> st;
    st.emplace(start_x, start_y);
    bool initial = true;

    while (!st.empty())
    {
        auto pos = st.top();
        int x = pos.first, y = pos.second;
        st.pop();

        if (x < 0 || x >= m_Cols || y < 0 || y >= m_Rows) continue;
        int idx = CoordsToIndex(x, y);
        if (m_Cells[idx].IsRevealed() || m_Cells[idx].GetType() == CellType::Mine) continue;

        m_Cells[idx].Reveal();

        if (!initial && m_Cells[idx].GetMineCount() > 0) continue;

        st.emplace(x - 1, y);
        st.emplace(x + 1, y);
        st.emplace(x, y - 1);
        st.emplace(x, y + 1);
        initial = false;
    }
}

void Board::Die()
{
    for (auto & cell : m_Cells) {
        if (cell.GetType() == CellType::Mine)
            cell.Reveal();
        cell.Disable();
    }
}

std::vector<int> Board::GetRandomIndices(int exclude)
{
    std::vector<int> indices;
    for (int i = 0; i < m_Cells.size(); i++) {
        if (i == exclude) continue;
        indices.push_back(i);
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(indices.begin(), indices.end(), std::default_random_engine(seed));
    return indices;
}

void Board::LoadMines(int exclude)
{
    std::vector<int> indices = GetRandomIndices(exclude);
    int mineCount = m_MinePercentage * m_Cells.size();
    for (int i = 0; i < mineCount; i++) {
        m_Cells[indices[i]].SetType(CellType::Mine);

        // precompute the enemy count of the neighbours of the mine
        UpdateMineNeighbours(indices[i]);
    }
}

void Board::IncrementCellEnemyCount(int x, int y)
{
    if (x < 0 || x >= m_Cols || y < 0 || y > m_Rows) return;
    int idx = CoordsToIndex(x, y);
    m_Cells[idx].SetMineCount(m_Cells[idx].GetMineCount() + 1);
}

void Board::UpdateMineNeighbours(int idx)
{
    int x = idx % m_Cols;
    int y = idx / m_Rows;

    IncrementCellEnemyCount(x - 1, y);
    IncrementCellEnemyCount(x + 1, y);
    IncrementCellEnemyCount(x - 1, y - 1);
    IncrementCellEnemyCount(x, y - 1);
    IncrementCellEnemyCount(x + 1, y - 1);
    IncrementCellEnemyCount(x + 1, y + 1);
    IncrementCellEnemyCount(x, y + 1);
    IncrementCellEnemyCount(x - 1, y + 1);
}

bool Board::IsWithinBounds(sf::Vector2i &position) const
{
    int x = position.x;
    int y = position.y;
    return x >= 0 && y >= 0 && y <= m_Height && x <= m_Width;
}

void Board::Render(sf::RenderWindow &window)
{
    for (auto & m_Cell : m_Cells)
    {
        m_Cell.Render(window);
    }
}

constexpr int Board::CoordsToIndex(int x, int y) const
{
    return y * m_Cols + x;
}
