//
// Created by andrea on 4/30/19.
//

#ifndef FACTORY_EXPERIMENTS_SUBSYSTEM_HPP
#define FACTORY_EXPERIMENTS_SUBSYSTEM_HPP

#include "Loggable.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

/*!
 * \brief An object managing a specific aspect of the engine functionality
 */
class Subsystem : public utils::log::Loggable {
public:
    Subsystem (const std::string& subsystem_name);
};


#endif //FACTORY_EXPERIMENTS_SUBSYSTEM_HPP


/*!
\file
\brief Header file.
*/
