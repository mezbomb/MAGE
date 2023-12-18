#include "Component.h"

namespace SAGE {
    std::unordered_map<std::string, ComponentFactory::ComponentCreator> ComponentFactory::componentCreators;
}