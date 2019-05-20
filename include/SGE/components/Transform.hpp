#ifndef FACTORY_EXPERIMENTS_TRANSFORM_HPP
#define FACTORY_EXPERIMENTS_TRANSFORM_HPP


#include "Component.hpp"
#include <list>
#include "SGE/Vec2.hpp"
#include <string>
#include "SGE/utils/Matrix2D.hpp"

namespace sge::cmp {

    /*!
 * \brief The component that manages the spacial properties of a GameObject and organizes the object in a Scene
 * in a Transform hierarchy
 */
    class Transform : public Component<Transform> {
    public:
        explicit Transform(const utils::Handle<GameObject> &gameobject);

        //region Hierarchy management

        void set_parent(utils::Handle<Transform> new_parent);
        utils::Handle<Transform> get_parent();

        void remove_child(utils::Handle<Transform> target_child);
        std::list<utils::Handle<Transform>> get_children_list();
        //endregion

        //region Spacial

        void set_local_position(double x, double y);
        Vec2<double> get_local_position();
        Vec2<double> get_world_position();

        void set_local_scale(double scale);
        Vec2<double> get_local_scale();
        Vec2<double> get_world_scale();

        void set_local_rotation(double rotation);
        double get_local_rotation();
        double get_local_rotation_euler();
        double get_world_rotation();
        double get_world_rotation_euler();


        Vec2<double> local_to_world_point(Vec2<double> point);
        Vec2<double> transform_world_to_local(Vec2<double> world_pos);
        //endregion


    private:
        utils::Handle<sge::cmp::Transform> m_parent;
        std::list<utils::Handle<sge::cmp::Transform>> m_children;

        sge::Vec2<double> m_local_position_vector;
        Matrix2D<double> m_local_rotation_matrix;
        Matrix2D<double> m_local_scale_matrix;

        sge::Vec2<double> m_world_position_vector;
        Matrix2D<double> m_world_rotation_matrix;
        Matrix2D<double> m_world_scale_matrix;
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
