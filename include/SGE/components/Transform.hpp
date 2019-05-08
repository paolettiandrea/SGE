#ifndef FACTORY_EXPERIMENTS_TRANSFORM_HPP
#define FACTORY_EXPERIMENTS_TRANSFORM_HPP


#include "Component.hpp"
#include <list>
#include "SGE/Vec2.hpp"
#include <string>

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
        void add_child(utils::Handle<Transform> new_child);
        void remove_child(utils::Handle<Transform> target_child);
        std::list<utils::Handle<Transform>> get_children_list();
        //endregion

        //region Spacial

        void set_local_position(double x, double y);
        Vec2<double> get_local_position();
        Vec2<double> get_world_position();

        void set_local_scale(double scale);
        double get_local_scale();
        double get_world_scale();

        void set_local_rotation(double rotation);
        double get_local_rotation();
        double get_world_rotation();

        Vec2<double> apply_transformation(Vec2<double> vector);


        Vec2<double> transform_local_to_world(Vec2<double> local_pos);
        Vec2<double> transform_world_to_local(Vec2<double> world_pos);
        //endregion


    private:
        utils::Handle<sge::cmp::Transform> m_parent;
        std::list<utils::Handle<sge::cmp::Transform>> m_children;

        Vec2<double> m_local_position;
        double m_local_rotation_angle;
        double m_local_scale;

    };

}



#endif //FACTORY_EXPERIMENTS_TRANSFORM_HPP



/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
