//
// Created by andrea on 5/14/19.
//

#ifndef FACTORY_EXPERIMENTS_DEBUGSHAPESMANAGER_HPP
#define FACTORY_EXPERIMENTS_DEBUGSHAPESMANAGER_HPP


#include <list>
#include "SGE/debug/DebugShape.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge {
    namespace core {
        /*!
         * \brief Manages the debug shapes
         */
        class DebugShapesManager : public sf::Drawable {
        public:
            void add_debug_shape(debug::DebugShape* new_shape);
            void remove_expired_shapes();

        protected:
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        private:
            std::list<debug::DebugShape*> debug_shapes_list;

            static bool is_discardable_check_and_delete(debug::DebugShape *shape);
        };
    }
}



#endif //FACTORY_EXPERIMENTS_DEBUGSHAPESMANAGER_HPP
