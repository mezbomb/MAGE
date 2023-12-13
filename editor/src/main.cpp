#include "engine_header.h"
#include "events.h"

int main() {
    SAGE::SAGE_GAME_SETTINGS settings = {};
    settings.GameName = "SAGE Editor";
    settings.WindowWidth = 1920;
    settings.WindowHeight = 1080;

    SAGE::GameEngine game(settings);
    game.PushLayer(new SAGE::GameLayer(), SAGE::Layer::LayerType::GAME);
    game.PushLayer(new SAGE::RenderLayer(game.GetContext()), SAGE::Layer::LayerType::RENDER);

    while (!game.GameQuit()) {
        game.UpdateLayers();
    }
    SAGE::Event* e = new SAGE::Event(SAGE::Event::EventType::KEY);
    game.GetLayer(SAGE::Layer::LayerType::GAME)->GetEventQueue().push(e);
    game.UpdateLayers();

    return 0;
}