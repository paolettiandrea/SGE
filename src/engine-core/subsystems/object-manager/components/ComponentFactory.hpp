#ifndef FACTORY_EXPERIMENTS_COMPONENTFACTORY_HPP
#define FACTORY_EXPERIMENTS_COMPONENTFACTORY_HPP

#include <map>
#include "SGE/Macros.hpp"
#include "Loggable.hpp"

namespace sge {
    namespace core {

        class IComponentCreator;
        class IComponentMemoryLayer;

        /*!
         * \brief The (decentralized) factory responsable for the fabrication of new components.
         */
        class ComponentFactory : public utils::log::Loggable {
        public:
            ComponentFactory() : utils::log::Loggable("COMPONENT FACTORY") {}
            static void register_component_creator(IComponentCreator* new_component_creator);
            /*!
             * \brief Method that allows the conversion of the string id to the array index correspondyng to that component type.
             * \return the index at which the type (given by id) is expected to be found in all the internal arrays mapping to all the possible component types.
             */
            static unsigned int id_to_index(const std::string &id);
            /*!
             * \brief Given the index that identfies univocally a Component type it returns its unique id string
             */
            static std::string index_to_id(unsigned int index);
            /*!
             * \brief Pushed a new full set of ComponentArrays to the top of the stack (each at the top of its corresponding creator)
             * \param componentarray_out The array that is filled with the pointers to the new ComponentArrays.
             */
            void push_new_component_memory_layer(IComponentMemoryLayer* componentarray_out[]);
            /*!
             * \brief Pops the topmost full set of ComponentArrays, one for every creator.
             */
            void pop_top_component_memory_layer();

            bool check_registration_status();


        private:
            static std::map<std::string, unsigned int> id_to_index_map;
            static std::string index_to_id_array[TOTAL_POSSIBLE_COMPONENTS];
            static IComponentCreator* creators[];

            static unsigned int registration_counter;
        };
    }
}


#endif //FACTORY_EXPERIMENTS_COMPONENTFACTORY_HPP





/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
