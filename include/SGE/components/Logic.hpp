#ifndef FACTORY_EXPERIMENTS_LOGIC_HPP
#define FACTORY_EXPERIMENTS_LOGIC_HPP


#include "Component.hpp"



class Logic : public Component {
public:
    explicit Logic(const Handle<GameObject> &gameobject);
};


#endif //FACTORY_EXPERIMENTS_LOGIC_HPP


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
