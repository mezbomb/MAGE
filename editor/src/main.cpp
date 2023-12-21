#include "Engine.h"
#include "Events.h"

int main() {
    MAGE::MAGE_GAME_SETTINGS settings = {};
    settings.GameName = "MAGE Editor";
    settings.WindowWidth = 1920;
    settings.WindowHeight = 1080;

    MAGE::GameEngine game(settings);

    while (!game.GameQuit()) {
        game.Run();
    }

    return 0;
}