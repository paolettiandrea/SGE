#include <SGE/components/Component.hpp>


Component::Component(Handle<GameObject> gameobject)
    : gameobject_handle(gameobject) {

}

const Handle<GameObject> &Component::gameobject() const {
    return gameobject_handle;
}
