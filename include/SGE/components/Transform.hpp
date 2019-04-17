//
// Created by andrea on 4/17/19.
//

#ifndef FACTORY_EXPERIMENTS_TRANSFORM_HPP
#define FACTORY_EXPERIMENTS_TRANSFORM_HPP


#include "Component.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

class Transform : public Component {
public:
    explicit Transform(const Handle<GameObject> &gameobject);
};


#endif //FACTORY_EXPERIMENTS_TRANSFORM_HPP
