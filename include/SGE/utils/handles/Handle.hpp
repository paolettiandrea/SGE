#ifndef PROJECT_HANDLE_HPP
#define PROJECT_HANDLE_HPP

#ifndef MAXIMUM_HANDLES_PER_TYPE
#define MAXIMUM_HANDLES_PER_TYPE 32000
#endif


#include "HandleEntry.hpp"
#include <queue>
#include <iostream>

/*!
 * \brief A handle to an object, can be used to safely keep a reference to objects that could move in memory
 * \tparam T The type of object this handle needs to reference to
 */
template <class T>
struct Handle {
private:
    Handle(int _index, int _counter)
            : index(_index)
            , counter(_counter)
            {

            }

public:
    /*!
     * \brief Constructs a null handle
     */
    Handle()
    : index(MAXIMUM_HANDLES_PER_TYPE)
    , counter(0) {

    }

    /*!
     * Generates a new entry referencing to the given object and constructs an handle referencing to it
     * \param obj The object that needs to be referenced by the handle
     */
    explicit Handle(T& obj) {
        auto temp = Handle<T>::new_entry(&obj);
        index = temp.index;
        counter = temp.counter;
    }

    /*!
     * Generates a new entry referencing to the given object and constructs an handle referencing to it
     * \param obj The object that needs to be referenced by the handle
     */
    explicit Handle(T* obj) {
        auto temp = Handle<T>::new_entry(obj);
        index = temp.index;
        counter = temp.counter;
    }

    /*!
     * \retval *true* if this handle is not referencing to any object in this moment, equivalent to a nullptr for pointers
     * \retval *false* if this handle is referencing to an object, but the reference could be expired, use is_expired() or is_valid() to check that.
     */
    bool is_null() {
        return (index == MAXIMUM_HANDLES_PER_TYPE);
    }
    /*!
     * \brief Makes this handle null, like a nullptr it means that it isn't referencing to any particular object.
     */
    void make_null() {
        index = MAXIMUM_HANDLES_PER_TYPE;
    }

    /*!
     * \brief Checks if the handle is safe to use.
     * \retval *true* if this handle is valid, meaning that it references an object and it can be accessed safely
     * \retval *false* if this handle is invalid, could be simply beacuse is_null(), or beacuse the entry it was referencing is expired
     */
    bool is_valid() {
        if (is_null()) return false;
        else {
            return ((handle_entries[index].counter == counter));
        }
    }

    /*!
     * \brief Updates the value of the pointer to the object this handle is referencing to,
     * when an "handled" object is moved in memory it's pointer should be updated with this method accordingly.
     * \param pointer The new pointer to the object this handle needs to reference to.
     */
    void update_origin_pointer(T *pointer) {
        if (!this->is_valid()) {
            std::cerr << "Tried to update the value of a pointer from a handle that isn't valid anymore" << std::endl;
        } else {
            handle_entries[index].pointer = pointer;
        }
    }
    /*!
     * The operator used to access the object the handle is referencing as it was a pointer, BUT IT'S NOT!
     * \return A pointer to the object this handle is referencing.
     */
    T* operator->() {
#ifdef DEBUG
        if (!this->is_valid()) {
            std::cout << "ERROR: Tried to use the -> operator on an invalid handle" << std::endl;
            Handle<T>::print_entries_array_info();
            exit(1);
        }
#endif
        return this->get_pointer();
    }
    /*!
     * Frees the entry this handle points to, making this and every other handle referencing to it invalid.
     */
    void make_origin_expired() {
        Handle<T>::free_entry(*this);
    }

    /*!
     * \brief This is the method that should be used in order to access the object,
     * don't cache the pointer returned by this method, since could be left dangling
     * \return A pointer to the object this handle is referencing to
     */
    T* get_pointer() {
        if (!this->is_valid()) return nullptr;
        else return  handle_entries[index].pointer;
    }


    int get_index() const {
        return index;
    }

private:
    int index;
    int counter;


    // STATIC-------------------------------------------------------------------

private:
    static HandleEntry<T> handle_entries[];
    static int first_untouched_index;
    static std::queue<int> invalidated_indexes;

public:
    static Handle new_entry(T *pointer) {

        if (invalidated_indexes.empty()) {
            Handle handle(first_untouched_index, 0);
            handle_entries[first_untouched_index].pointer = pointer;
            first_untouched_index++;
            if (first_untouched_index>=MAXIMUM_HANDLES_PER_TYPE) {
                std::cerr << "An handle array is completely full, consider increasing the "
                             "MAXIMUM_HANDLES_PER_TYPE preprocessor variable" << std::endl;
                exit(1);
            }
            return handle;
        } else {
            int target_index = invalidated_indexes.front();
            Handle handle(target_index, handle_entries[target_index].counter);
            handle_entries[target_index].pointer = pointer;
            invalidated_indexes.pop();
            return handle;
        }
    }

    static const Handle get_handle_from_index(int index) {
        return  Handle(index, handle_entries[index].counter);
    }

    static void free_entry(Handle &handle) {
        if (handle.is_valid()) {
            handle_entries[handle.index].counter++;
            invalidated_indexes.push(handle.index);
        } else {
            std::cerr << "Tried to free an entry from an expired handle, "
                         "the entry this handle was referencing to was probably already freed" << std::endl;
            exit(1);
        }

    }

    static void print_entries_array_info() {
        std::cout << "Entry array of type [" << typeid(T).name() << "], size [" << MAXIMUM_HANDLES_PER_TYPE << "], occupying [" << sizeof(handle_entries) << "] bytes.\n"
                  << "\tThe first untouched entry is at index [" << first_untouched_index << "]\n"
                  << "\tThere are [" << invalidated_indexes.size() << "] invalidated entries\n\t\t";

        for (int i = 0; i < first_untouched_index ; ++i) {
            std::cout << "[" << handle_entries[i].pointer << ", " << handle_entries[i].counter << "]-";
        }
        std::cout << "[" << handle_entries[first_untouched_index].pointer << ", " << handle_entries[first_untouched_index].counter << "]-...\n";
    }
};

template<class T>
int Handle<T>::first_untouched_index = 0;
template<class T>
std::queue<int> Handle<T>::invalidated_indexes;
template<class T>
HandleEntry<T> Handle<T>::handle_entries[MAXIMUM_HANDLES_PER_TYPE];


#endif //PROJECT_HANDLE_HPP


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
