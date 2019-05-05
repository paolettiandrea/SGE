#ifndef FACTORY_EXPERIMENTS_TRANSFORM_HPP
#define FACTORY_EXPERIMENTS_TRANSFORM_HPP


#include "Component.hpp"
#include <list>
#include "SGE/Vec2.hpp"

namespace sge::cmp {

    /*!
 * \brief The component that manages the spacial properties of a GameObject and organizes the object in a Scene
 * in a Transform hierarchy
 */
    class Transform : public Component<Transform> {
    public:
        Transform(const utils::Handle<GameObject> &gameobject);

        void set_parent(utils::Handle<Transform> new_parent);
        void add_child(utils::Handle<Transform> new_child);
        void remove_child(utils::Handle<Transform> target_child);

        void set_position(float x, float y);
        Vec2<float> get_local_position();
        Vec2<float> get_world_position();

        Vec2<float> transform_local_to_world(Vec2<float> local_pos);
        Vec2<float> transform_world_to_local(Vec2<float> world_pos);

    private:
        utils::Handle<sge::cmp::Transform> parent;
        std::list<utils::Handle<sge::cmp::Transform>> children;

        Vec2<float> local_position;
        float local_rotation;
        float local_scale;
    };

}



#endif //FACTORY_EXPERIMENTS_TRANSFORM_HPP



/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
