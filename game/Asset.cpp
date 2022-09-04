//
// Created by srijan on 9/4/22.
//

#include "Asset.h"

sf::Font Asset::font_Roboto;

void Asset::Load()
{
    Asset::font_Roboto.loadFromFile("../assets/Roboto-Bold.ttf");
}