#include "engine_header.h"
#include "events.h"

void SAGE::GameLayer::HandleEvents()
{
    std::queue<Event*> q = GetEventQueue();
    while (!q.empty()) {
        Event* e = q.front();
        q.pop();

        switch (e->GetType()) {
        case Event::EventType::KEY: m_Input.HandleKeyInput(); break;
        default: break;
        }
        //TODO(mez) move to free list and manage event handles to avoid dynamic alloc/dealloc
        delete e;
    }
}

void SAGE::RenderLayer::OnUpdate() {
    GfxContext gfx = m_Context;
    auto end = std::chrono::high_resolution_clock::now();
    m_DeltaTime = end - m_Time;
    float time = m_DeltaTime.count();

    float color[] = { 0.5f * cosf(time) + 0.5f,
                        0.5f * sinf(time) + 0.5f,
                        1.0f };

    gfxProgramSetParameter(gfx, program, "Color", color);
    gfxCommandBindKernel(gfx, kernel);
    gfxCommandBindVertexBuffer(gfx, vertex_buffer);

    gfxCommandDraw(gfx, 3);

    gfxFrame(gfx);
}
