#include "ComponentFactory.hpp"
#include "components/component_creators/IComponentCreator.hpp"
#include "IComponentMemoryLayer.hpp"

// Static variables initialization
IComponentCreator* ComponentFactory::creators[TOTAL_POSSIBLE_COMPONENTS];
std::map<std::string, unsigned int> ComponentFactory::id_index_map = {};
unsigned int ComponentFactory::registration_counter = 0;


void ComponentFactory::register_component_creator(IComponentCreator *new_component_creator) {
    std::string id = new_component_creator->get_id();

    if (ComponentFactory::id_index_map.count(id)>0) {
        std::cout << "ERROR: the id [" << id << "] was already registered at index " << id_index_map[id] << std::endl;
        exit(1);
    } else if (registration_counter==TOTAL_POSSIBLE_COMPONENTS) {
        std::cout << "ERROR: trying to register more components than the macro TOTAL_POSSIBLE_COMPONENTS allows, have you added a new Component type and forgot to increase it?" << std::endl;
        exit(1);
    }

    id_index_map[id] = registration_counter;
    creators[registration_counter] = new_component_creator;
    registration_counter++;

    std::cout << "Registered a new ComponentCreator with the id [" << new_component_creator->get_id()
              << "] and the index [" << registration_counter-1 << "]" << std::endl;
}

unsigned int ComponentFactory::id_to_index(const std::string &id) {
    return  id_index_map[id];
}

void ComponentFactory::push_new_component_memory_layer(IComponentMemoryLayer* componentarray_out[]) {
    for (int i = 0; i < TOTAL_POSSIBLE_COMPONENTS; ++i) {
        componentarray_out[i] = creators[i]->push_new_layer();
    }
}

void ComponentFactory::pop_top_component_memory_layer() {
    for (auto &creator : creators) {
        creator->pop_top_layer();
    }
}


