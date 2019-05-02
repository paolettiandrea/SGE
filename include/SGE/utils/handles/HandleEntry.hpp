//
// Created by andrea on 4/10/19.
//

#ifndef PROJECT_HANDLEENTRY_HPP
#define PROJECT_HANDLEENTRY_HPP


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

/*!
 * \brief The object that contains the actual pointer that a corresponding handle can retrieve
 * \tparam T The type of pointer contained in this object
 */
template <class T>
class HandleEntry {
public:
    HandleEntry(   ) : pointer(nullptr) {}
    T* pointer = nullptr;
    int counter = 0;

};


#endif //PROJECT_HANDLEENTRY_HPP
