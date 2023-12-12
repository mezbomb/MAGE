#include "engine_header.h"

int main() {
    SAGE::SAGE_GAME_SETTINGS settings = {};
    settings.GameName = "SAGE Editor";
    settings.WindowWidth = 1920;
    settings.WindowHeight = 1080;

    SAGE::GameEngine game(settings);
    game.PushLayer(new SAGE::GameLayer(), SAGE::LAYER_TYPE::GAME);
    game.PushLayer(new SAGE::RenderLayer(), SAGE::LAYER_TYPE::RENDER);

    while (true) {
        game.UpdateLayers();
    }

    return 0;
}