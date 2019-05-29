//
// Created by andrea on 4/30/19.
//

#ifndef FACTORY_EXPERIMENTS_SUBSYSTEM_HPP
#define FACTORY_EXPERIMENTS_SUBSYSTEM_HPP

#include "Loggable.hpp"
#include "ComponentCreator.hpp"

namespace sge {
    namespace core {
        /*!
 * \brief An object managing a specific aspect of the engine functionality
 */
        class Subsystem : public utils::log::Loggable {
        public:
            Subsystem (const std::string& subsystem_name);
        };
    }
}

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/




#endif //FACTORY_EXPERIMENTS_SUBSYSTEM_HPP


/*!
\file
\brief Header file.
*/
