//
// Created by andrea on 4/10/19.
//

#ifndef PROJECT_HANDLEENTRY_HPP
#define PROJECT_HANDLEENTRY_HPP


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/


template <class T>
class HandleEntry {
public:
    HandleEntry(   ) : pointer(nullptr) {}
    T* pointer = nullptr;
    int counter = 0;

};


#endif //PROJECT_HANDLEENTRY_HPP
