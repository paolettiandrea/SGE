#ifndef SGE_TRANSFORM_HPP
#define SGE_TRANSFORM_HPP


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
        utils::event::Event world_transform_changed_event;
        utils::event::Event local_transform_changed_event;
        /*!
         * \brief Event called when the parent of this Transform is modified.
         */
        utils::event::Event parent_changed_event;

        explicit Transform(const utils::Handle<GameObject> &gameobject);

        void visual_debug_draw_transform();
        void visual_debug_draw_names();

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
        bool has_parent();

        const std::list<utils::Handle<sge::cmp::Transform>> &get_children();

        std::string get_debug_string() override;


        void reallocation_callback() override;


        std::list<utils::Handle<Transform>> get_children_list();
        //endregion

        //region Spacial

        void set_local_position(float x, float y);
        void set_local_position(const Vec2<float>& new_local_position);
        Vec2<float> get_local_position();
        Vec2<float> get_world_position();

        void set_local_scale(float scale);
        void set_local_scale(float x, float y);
        void set_local_scale(sge::Vec2<float> scale_vec);

        Vec2<float> get_local_scale();
        Vec2<float> get_world_scale();

        void set_local_rotation(float rotation);
        float get_local_rotation();
        float get_local_rotation_euler();
        float get_world_rotation();
        float get_world_rotation_euler();


        Vec2<float> local_to_world_point(Vec2<float> point);
        Vec2<float> world_to_local_point(Vec2<float> world_pos);

        static Vec2<float> change_reference_frame(utils::Handle<Transform> t_from, utils::Handle<Transform> t_to, sge::Vec2<float> point) {
            return t_to->world_to_local_point(t_from->local_to_world_point(point));
        }
        //endregion

        bool is_root();


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

        void recursive_change_pulse();
        void update_world_data();
        void compose_with_parent();
        void add_child(utils::Handle<Transform> new_child);

    };

}

#endif //SGE_TRANSFORM_HPP
