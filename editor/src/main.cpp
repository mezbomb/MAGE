#include "engine_header.h"
#include "events.h"

int main() {
    SAGE::SAGE_GAME_SETTINGS settings = {};
    settings.GameName = "SAGE Editor";
    settings.WindowWidth = 1920;
    settings.WindowHeight = 1080;

    SAGE::GameEngine game(settings);

    while (!game.GameQuit()) {
        game.Run();
    }

    return 0;
}