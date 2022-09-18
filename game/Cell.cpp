//
// Created by srijan on 9/3/22.
//

#include "Cell.h"

Cell::Cell(float x, float y, float size, CellColorScheme scheme)
    : m_X(x), m_Y(y), m_Size(size), m_Rect(sf::Vector2f(size, size)), m_Type(CellType::Normal),
    m_EnemyCount(0), m_EnemyCircle(m_Size * 0.5 * 0.5)
{
    m_ColorScheme = scheme;
    m_Rect.setPosition(sf::Vector2f(x * m_Size, y * m_Size));
    m_EnemyCircle.setPosition(sf::Vector2f(x * m_Size + m_Size * 0.25, y * m_Size + m_Size * 0.25));
    m_Text.setFont(Asset::font_Roboto);
    m_Text.setCharacterSize(16);
    m_Text.setFillColor(sf::Color::Black);
    m_Text.setPosition(x * m_Size + m_Size * 0.5 - 8, y * m_Size + m_Size * 0.5 - 8);
}

void Cell::UpdateCellColor(sf::RenderWindow &window)
{
    if (m_Revealed) return;

    if (m_ColorScheme == CellColorScheme::Light)
        m_Rect.setFillColor(ColorSchemes::Light::background);
    else
        m_Rect.setFillColor(ColorSchemes::Dark::background);

    sf::Vector2i position = sf::Mouse::getPosition(window);
    int x = position.x,
        y = position.y;

    // handle mouse hover
    if (!m_Disabled && x >= m_X * m_Size && x < (m_X + 1) * m_Size &&
        y >= m_Y * m_Size && y < (m_Y + 1) * m_Size) {
        m_Rect.setFillColor(ColorSchemes::hover);
    }
}

void Cell::Render(sf::RenderWindow &window)
{
    UpdateCellColor(window);
    window.draw(m_Rect);

    if (m_Type == CellType::Normal && m_Revealed) {
        window.draw(m_Text);
    }

    if (m_Type == CellType::Mine && m_Revealed)
    {
        window.draw(m_EnemyCircle);
    }
}

void Cell::Reveal()
{
    m_Revealed = true;
    if (m_Type == CellType::Mine) {
        // choose a random color from the pool for the enemy
        long enemyColorIdx = random() % ColorSchemes::enemyColorCount;
        m_Rect.setFillColor(sf::Color(ColorSchemes::enemyColorPool[enemyColorIdx][0]));
        m_EnemyCircle.setFillColor(sf::Color(ColorSchemes::enemyColorPool[enemyColorIdx][1]));
        return;
    }

    if (m_Type == CellType::Normal) {
        if (m_ColorScheme == CellColorScheme::Light)
            m_Rect.setFillColor(ColorSchemes::Light::backgroundRevealed);
        else
            m_Rect.setFillColor(ColorSchemes::Dark::backgroundRevealed);
    }

    if (m_EnemyCount > 0)
        m_Text.setString(sf::String(std::to_string(m_EnemyCount)));
}

void Cell::Reset()
{
    m_Revealed = false;
    m_Type = CellType::Normal;
    m_Disabled = false;
    m_EnemyCount = 0;
    m_Text.setString("");
}

bool Cell::IsRevealed() const
{
    return m_Revealed;
}

void Cell::SetType(CellType type)
{
    m_Type = type;
}

CellType Cell::GetType() const
{
    return m_Type;
}

void Cell::SetMineCount(int count)
{
    m_EnemyCount = count;
}

int Cell::GetMineCount() const
{
    return m_EnemyCount;
}

void Cell::Disable()
{
    m_Disabled = true;
}