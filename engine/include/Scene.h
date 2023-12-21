#pragma once
#include <string>
#include <vector>
#include "Entity.h"

namespace SAGE {

    class Scene {
    public:
        Scene() : m_Name("empty"), m_Extension(""), m_Path("") {}
        Scene(std::string n, std::string e, std::string p) :
            m_Name(n),
            m_Extension(e),
            m_Path(p) {}

        bool m_Loaded = false;

        std::string m_Name;
        std::string m_Extension;
        std::string m_Path;
        std::vector<std::shared_ptr<Entity>> m_Entities;
    };
}