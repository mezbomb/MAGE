#pragma once
#include "Engine.h"

namespace MAGE {

    class RenderLayer : public Layer {
    public:
        RenderLayer(GameEngine& g, GfxContext& c) : m_Parent(g), m_Context(c), m_Time(std::chrono::high_resolution_clock::now()), m_DeltaTime(0.0f) {
            m_Type = LayerType::RENDER;
        }
        void OnUpdate() override;
        GameEngine& GetParent() { return m_Parent; }
        // Renderer
    private:
        GameEngine m_Parent;

        GfxContext m_Context;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_Time;
        std::chrono::duration<float> m_DeltaTime;
        std::unordered_map<unsigned int, GfxBuffer>  m_Buffers;
        std::unordered_map<unsigned int, GfxProgram> m_Programs;
        std::unordered_map<unsigned int, GfxKernel>  m_Kernels;
        std::unordered_map<unsigned int, GfxTexture> m_Textures;
    };
}
