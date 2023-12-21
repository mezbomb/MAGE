#include "Component.h"

namespace MAGE {
    std::unordered_map<std::string, ComponentFactory::ComponentCreator> ComponentFactory::componentCreators;
}