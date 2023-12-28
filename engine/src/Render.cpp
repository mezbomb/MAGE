#include "Render.h"

namespace MAGE {

    void RenderLayer::OnUpdate() {
        auto end = std::chrono::high_resolution_clock::now();
        m_DeltaTime = end - m_Time;
        float time = m_DeltaTime.count();

        float color[] = { 0.5f * cosf(time) + 0.5f,
                            0.5f * sinf(time) + 0.5f,
                            1.0f };

        GfxBuffer vertex_buffer;
        GfxProgram program;
        GfxKernel kernel;

        auto mesh_entities = GameEngine::m_EntityManager.GetEntitysByComponent(Component::ComponentType::MESH);
        for (auto entity : mesh_entities) {
            auto meshComponent = std::dynamic_pointer_cast<ComponentMesh>(entity->GetComponent(Component::ComponentType::MESH));
            if (meshComponent) {
                //create the resources
                if (m_Buffers.empty()) {
                    vertex_buffer = gfxCreateBuffer(m_Context, sizeof(float) * meshComponent->m_verts.size(), meshComponent->m_verts.data());
                    m_Buffers[1] = vertex_buffer;
                    program = gfxCreateProgram(m_Context, meshComponent->m_program.c_str());
                    m_Programs[1] = program;
                    kernel = gfxCreateGraphicsKernel(m_Context, program);
                    m_Kernels[1] = kernel;
                }

                gfxProgramSetParameter(m_Context, m_Programs[1], "Color", color);
                gfxCommandBindKernel(m_Context, m_Kernels[1]);
                gfxCommandBindVertexBuffer(m_Context, m_Buffers[1]);
                gfxCommandDraw(m_Context, 3);
            }
        }
        gfxFrame(m_Context);
    }
}

