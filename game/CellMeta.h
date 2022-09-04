//
// Created by srijan on 9/4/22.
//

#ifndef MINESWEEPER_CELLMETA_H
#define MINESWEEPER_CELLMETA_H

#include <SFML/Graphics.hpp>

enum CellType { Mine, Normal };
enum CellColorScheme { Light, Dark };

namespace ColorSchemes {
    const sf::Color hover(0xD1FF76FF);

    const int enemyColorCount = 5;
    const sf::Uint32 enemyColorPool[enemyColorCount][2] = {
            { 0xdb3236ff, 0x8e2123ff },
            { 0xf4840dff, 0x9f5608ff },
            { 0x48e6f1ff, 0x2f969dff },
            { 0xed44b5ff, 0x9a2c76ff },
            { 0x4885edff, 0x2f569aff }
    };

    namespace Light
    {
        const sf::Color background(0xaad751ff);
        const sf::Color backgroundRevealed(0xe5c29fff);
    };

    namespace Dark
    {
        const sf::Color background(0xa2d149ff);
        const sf::Color backgroundRevealed(0xd7b899ff);

    };
}; // namespace ColorSchemes

#endif //MINESWEEPER_CELLMETA_H
