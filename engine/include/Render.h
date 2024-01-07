#pragma once
#include "Engine.h"
#include <glm/glm.hpp>
#include <iostream>


namespace MAGE {

    class RenderLayer : public Layer {
    public:
        RenderLayer(GameEngine& g) : m_Parent(g), m_Context(*g.GetContext()), m_Time(std::chrono::high_resolution_clock::now()), m_DeltaTime(0.0f) {
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


        void PrintMatrix(const glm::mat4& mat) {
            std::cout << "Checking the Matrix:\n";
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    std::cout << mat[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }

    };
}
