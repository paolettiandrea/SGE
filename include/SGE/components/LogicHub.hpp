#ifndef SGE_LOGIC_HUB_HPP
#define SGE_LOGIC_HUB_HPP

#include <list>
#include "SGE/components/Component.hpp"
#include "SGE/logic/ILogicCallbacks.hpp"

namespace sge {

    class Logic;

    namespace cmp {

        /*!
         * \brief The Component that manages the Logic attached to a GameObject
         */
        class LogicHub : public Component<LogicHub>, public ILogicCallbacks {
        public:
            explicit LogicHub(const utils::Handle<GameObject> &gameobject);

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

            template <class T>
            T* get_logic();

            /*!
             * \brief Returns the first occurrence of a Logic object identified with the given id
             * \tparam T The type associated with the id (the logic will be downcasted to this type)
             * \param logic_id The unique logic id that identifies the type of Logic object
             * \return a pointer to the first Logic object having the given id if at least one is present, nullptr otherwise
             */
            template <class T>
            T* get_logic_by_id(const std::string& logic_id);
            void remove_logic(Logic* target_logic);

            // TODO: get_logics and remove_logics (multiple logics with same id)


            //region Callback propagation methods

            void on_start() override;

            void on_destruction() override;

            void on_update() override;

            void on_fixed_update() override;

            void destruction_callback() override;

            void on_collision_begin(CollisionInfo &collision_info) override;

            void on_collision_end(CollisionInfo &collision_info) override;

            void pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const CollisionInfo &info) override;

            void post_solve(b2Contact *contact, const b2ContactImpulse *impulse, const CollisionInfo &info) override;

            std::string get_debug_string() override;



            //endregion









        private:
            std::vector<Logic*> attached_logic_list;
        public:
            const std::vector<Logic *> &get_attached_logic_list() const;

        private:


            Logic* get_unspecificed_logic(const std::string& logic_id); // Used internally to allow forward declaration of Logic
        };


        template<class T>
        T* LogicHub::get_logic_by_id(const std::string &logic_id) {
            return (T*)get_unspecificed_logic(logic_id);
        }

        template<class T>
        T *sge::cmp::LogicHub::get_logic() {
            for (Logic *attached_logic : attached_logic_list) {
                auto cast = dynamic_cast<T*>(attached_logic);
                if (cast) return cast;
            }
            return nullptr;
        }

    }


}

typedef utils::Handle<sge::cmp::LogicHub> LogicHub_H;

#endif //SGE_LOGIC_HUB_HPP


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
