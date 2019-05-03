#include "ComponentFactory.hpp"
#include "IComponentCreator.hpp"
#include "IComponentMemoryLayer.hpp"

using sge::core::ComponentFactory;
using sge::core::IComponentCreator;
using sge::core::IComponentMemoryLayer;

// Static variables initialization
sge::core::IComponentCreator* ComponentFactory::creators[TOTAL_POSSIBLE_COMPONENTS];
std::map<std::string, unsigned int> ComponentFactory::id_index_map = {};
unsigned int ComponentFactory::registration_counter = 0;


void ComponentFactory::register_component_creator(IComponentCreator *new_component_creator) {
    std::string id = new_component_creator->get_id();

    if (ComponentFactory::id_index_map.count(id)>0) {
        std::cerr << "ERROR: the id [" << id << "] was already registered at index " << id_index_map[id] << std::endl;
        exit(1);
    } else if (registration_counter==TOTAL_POSSIBLE_COMPONENTS) {
        std::cerr << "ERROR: trying to register more components than the macro TOTAL_POSSIBLE_COMPONENTS allows, have you added a new Component type and forgot to increase it?" << std::endl;
        exit(1);
    }

    id_index_map[id] = registration_counter;
    creators[registration_counter] = new_component_creator;
    registration_counter++;
}

unsigned int ComponentFactory::id_to_index(const std::string &id) {
    return  id_index_map[id];
}

void ComponentFactory::push_new_component_memory_layer(IComponentMemoryLayer* componentarray_out[]) {
    LOG_DEBUG(17) << "Pushing a new ComponentMemoryLayer to every registered creator";
    for (int i = 0; i < TOTAL_POSSIBLE_COMPONENTS; ++i) {
        componentarray_out[i] = creators[i]->push_new_layer();
    }
}

void ComponentFactory::pop_top_component_memory_layer() {
    LOG_DEBUG(17) << "Popping the top component memory layer";
    for (auto &creator : creators) {
        creator->pop_top_layer();
    }
}

bool ComponentFactory::check_registration_status() {
    return (TOTAL_POSSIBLE_COMPONENTS == registration_counter);
}




