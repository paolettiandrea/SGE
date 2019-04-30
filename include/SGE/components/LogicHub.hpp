#ifndef FACTORY_EXPERIMENTS_LOGIC_HUB_HPP
#define FACTORY_EXPERIMENTS_LOGIC_HUB_HPP

#include <list>
#include "SGE/components/Component.hpp"
#include "SGE/logic/ILogicCallbacks.hpp"

class Logic;


class LogicHub : public Component, public ILogicCallbacks {
public:
    LogicHub(const Handle<GameObject> &gameobject);

    virtual ~LogicHub();

    void attach_logic(Logic* new_logic);
    bool has_logic(const std::string& logic_id);
    bool has_logic(Logic* target_logic);
    /*!
     * \brief Returns the first occurrence of a Logic object identified with the given id
     * \tparam T The type associated with the id (the logic will be downcasted to this type)
     * \param logic_id The unique logic id that identifies the type of Logic object
     * \return a pointer to the first Logic object having the given id if at least one is present, nullptr otherwise
     */
    template <class T>
    T* get_logic(const std::string& logic_id);
    void remove_logic(Logic* target_logic);

    // TODO: get_logics and remove_logics (multiple logics with same id)


    //region Callback propagation methods

    void on_start() override;

    void on_destruction() override;

    void on_update() override;

    void on_fixed_update() override;

    //endregion


private:
    std::list<Logic*> attached_logic_list;
    Logic* get_unspecificed_logic(const std::string& logic_id); // Used internally to allow forward declaration of Logic
};


template<class T>
T* LogicHub::get_logic(const std::string &logic_id) {
    return (T*)get_unspecificed_logic(logic_id);
}

#endif //FACTORY_EXPERIMENTS_LOGIC_HUB_HPP


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
