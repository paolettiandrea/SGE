#ifndef FACTORY_EXPERIMENTS_LOGIC_HUB_HPP
#define FACTORY_EXPERIMENTS_LOGIC_HUB_HPP

#include <list>
#include "SGE/components/Component.hpp"
#include "SGE/logic/ILogicCallbacks.hpp"

namespace sge {

    class Logic;

/*!
 * \brief The Component that manages the Logic attached to a GameObject
 */
    class LogicHub : public Component, public ILogicCallbacks {
    public:
        LogicHub(const utils::Handle<GameObject> &gameobject);


        virtual ~LogicHub();
        /*!
         * \brief Attaches a new Logic object to this LogicHub, making it the owner of the Logic
         * \param new_logic A pointer to the new Logic object
         */
        void attach_logic(Logic* new_logic);
        /*!
         * \brief Checks if this object has at least one Logic attached of the given type
         * \param logic_type_id The id that identifies the Logic type
         * \return true if this object as at least one corresponding Logic attached, false otherwise
         */
        bool has_logic(const std::string& logic_type_id);

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

        void destruction_callback() override;

        //endregion


    private:
        std::list<Logic*> attached_logic_list;
        Logic* get_unspecificed_logic(const std::string& logic_id); // Used internally to allow forward declaration of Logic
    };


    template<class T>
    T* LogicHub::get_logic(const std::string &logic_id) {
        return (T*)get_unspecificed_logic(logic_id);
    }

}



#endif //FACTORY_EXPERIMENTS_LOGIC_HUB_HPP


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
