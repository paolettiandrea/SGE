//
// Created by andrea on 4/30/19.
//

#ifndef SGE_SUBSYSTEM_HPP
#define SGE_SUBSYSTEM_HPP

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

            virtual void visual_debug_pass() {}

            virtual void memory_buffer_pass() = 0;
        };
    }
}

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/




#endif //SGE_SUBSYSTEM_HPP


/*!
\file
\brief Header file.
*/
