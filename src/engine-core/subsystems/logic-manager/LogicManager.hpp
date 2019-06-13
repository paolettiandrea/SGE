#ifndef SGE_LOGICMANAGER_HPP
#define SGE_LOGICMANAGER_HPP

#include "Subsystem.hpp"
#include "LogicHub.hpp"

namespace sge {
    namespace  core {
        /*!
 * \brief The Subsystem that manages Logic
 */
        class LogicManager : public Subsystem {
        public:
            LogicManager();
            /*!
             * \brief Calls on_update on every Logic attached to every GameObject of the top Scene.
             */
            void on_update();
            /*!
             * \brief Calls on_fixed_update on every Logic attached to every GameObject of the top Scene.
             */
            void on_fixed_update();

        private:
            ComponentCreator<cmp::LogicHub> logichub_creator;
        };
    }
}

#endif //SGE_LOGICMANAGER_HPP


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
