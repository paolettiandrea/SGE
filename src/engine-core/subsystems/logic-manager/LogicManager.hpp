#ifndef FACTORY_EXPERIMENTS_LOGICMANAGER_HPP
#define FACTORY_EXPERIMENTS_LOGICMANAGER_HPP

#include "Subsystem.hpp"
#include "ComponentCreator.hpp"
#include "LogicHub.hpp"

namespace sge {
    namespace  core {
        /*!
 * \brief The Subsystem that manages Logic
 */
        class LogicManager : public Subsystem {
        public:
            LogicManager();

            void on_update();
            void on_fixed_update();

        private:
            ComponentCreator<LogicHub> logichub_creator;
        };
    }
}

#endif //FACTORY_EXPERIMENTS_LOGICMANAGER_HPP


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
