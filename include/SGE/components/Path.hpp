//
// Created by andrea on 4/30/19.
//

#ifndef FACTORY_EXPERIMENTS_PATH_HPP
#define FACTORY_EXPERIMENTS_PATH_HPP

#include "SGE/components/Component.hpp"

namespace sge::cmp {
    /*!
     * \brief Probably Shape would be a better name (?)
     */
    class Path : public Component {
    public:
        Path(const utils::Handle<GameObject>& gameobject);
    };
}


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/




#endif //FACTORY_EXPERIMENTS_PATH_HPP
