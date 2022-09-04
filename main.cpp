#include "game/Game.h"
#include "game/Asset.h"

int main()
{
    Asset::Load();
    Game game;
    game.Run();

    return 0;
}