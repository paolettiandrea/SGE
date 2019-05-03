#include "Path.hpp"

using sge::Path;
using utils::Handle;

Path::Path(const Handle<GameObject> &gameobject) : Component(gameobject, "Path") {}
