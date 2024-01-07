#include "Render.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <gfx.h>
#include <iostream>

namespace MAGE {

    void RenderLayer::OnUpdate() {
        auto end = std::chrono::high_resolution_clock::now();
        m_DeltaTime = end - m_Time;
        float time = m_DeltaTime.count();

        float color[] = { 0.5f * cosf(time) + 0.5f,
                            0.5f * sinf(time) + 0.5f,
                            1.0f };

        float identity[] = { 1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 1.0f };

        GfxBuffer vertex_buffer;
        GfxProgram program;
        GfxKernel kernel;

        gfxCommandClearBackBuffer(m_Context);

        auto mesh_entities = GameEngine::m_EntityManager.GetEntitysByComponent(ComponentType::MESH);
        for (auto entity : mesh_entities) {
            auto meshComponent = entity->GetComponent<ComponentMesh>(ComponentType::MESH);
            auto transformComponent = entity->GetComponent<ComponentTransform>(ComponentType::TRANSFORM);
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
                if (transformComponent) {
                    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), transformComponent->position);
                    gfxProgramSetParameter(m_Context, m_Programs[1], "translationMatrix", translationMatrix);
                }
                else {
                    gfxProgramSetParameter(m_Context, m_Programs[1], "translationMatrix", identity);
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

