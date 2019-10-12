//
// Created by andrea on 4/17/19.
//

#ifndef SGE_ICOMPONENTCREATOR_HPP
#define SGE_ICOMPONENTCREATOR_HPP

#include "GameObject.hpp"
#include <string>

namespace sge {
    namespace core {

        class IComponentMemoryLayer;

/*!
 * \brief The un-specified interface for a ComponentCreator, allows for some
 */
        class IComponentCreator {
        public:
            virtual const std::string& get_id() = 0;
            /*!
             * \brief Pushes a new memory layer (aka a ComponentArray) on top of this object's stack
             */
            virtual IComponentMemoryLayer* push_new_layer() = 0;
            /*!
             * \brief Gets the topmost ComponentArray.
             * \return A pointer to the un-specified interface of the topmost ComponentArray.
             */
            virtual IComponentMemoryLayer* get_unspecified_top_layer() = 0;
            /*!
             * \brief Pops the topmost ComponentArray
             */
            virtual void pop_top_layer() = 0;

        };

    }
}


#endif //SGE_ICOMPONENTCREATOR_HPP
