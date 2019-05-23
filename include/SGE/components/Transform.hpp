#ifndef FACTORY_EXPERIMENTS_TRANSFORM_HPP
#define FACTORY_EXPERIMENTS_TRANSFORM_HPP


#include "Component.hpp"
#include <list>
#include <string>
#include "SGE/Vec2.hpp"
#include "SGE/utils/Matrix2D.hpp"

namespace sge::cmp {

    /*!
 * \brief The component that manages the spacial properties of a GameObject and organizes the object in a Scene
 * in a Transform hierarchy
 */
    class Transform : public Component<Transform> {
    public:
        /*!
         * \brief Event that is called when this transform is made dirty.
         */
        utils::event::Event transform_changed_event;

        explicit Transform(const utils::Handle<GameObject> &gameobject);

        //region Hierarchy management
        /*!
         * \brief Sets the parent of this Transform
         * \param new_parent An Handle to the new parent.
         */
        void set_parent(utils::Handle<Transform> new_parent);
        /*!
         * \brief Gets an handle to the parent of this object, null handle if base
         */
        utils::Handle<Transform> get_parent();

        void remove_child(utils::Handle<Transform> target_child);
        std::list<utils::Handle<Transform>> get_children_list();
        //endregion

        //region Spacial

        void set_local_position(float x, float y);
        Vec2<float> get_local_position();
        Vec2<float> get_world_position();

        void set_local_scale(float scale);
        Vec2<float> get_local_scale();
        Vec2<float> get_world_scale();

        void set_local_rotation(float rotation);
        float get_local_rotation();
        float get_local_rotation_euler();
        float get_world_rotation();
        float get_world_rotation_euler();


        Vec2<float> local_to_world_point(Vec2<float> point);
        Vec2<float> transform_world_to_local(Vec2<float> world_pos);
        //endregion


    private:
        utils::Handle<sge::cmp::Transform> m_parent;
        std::list<utils::Handle<sge::cmp::Transform>> m_children;

        sge::Vec2<float> m_local_position_vector;
        Matrix2D<float> m_local_rotation_matrix;
        Matrix2D<float> m_local_scale_matrix;

        sge::Vec2<float> m_world_position_vector;
        Matrix2D<float> m_world_rotation_matrix;
        Matrix2D<float> m_world_scale_matrix;
        bool is_dirty = true;

        void make_dirty();
        void update_world_data();
        void compose_with_parent();
        void add_child(utils::Handle<Transform> new_child);

    };

}



#endif //FACTORY_EXPERIMENTS_TRANSFORM_HPP



/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
