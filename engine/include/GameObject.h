#pragma once
#include <vector>
#include <memory>
#include "Component.h"

namespace SAGE {

    class GameObject {
    public:
        unsigned int tag;

        void AddComponent(std::shared_ptr<Component> component) {
            m_components.push_back(component);
        }

        std::vector<std::shared_ptr<Component>> m_components;
    private:
    };
}