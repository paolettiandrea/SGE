#include "Path.hpp"

using sge::cmp::Path;
using utils::Handle;

Path::Path(const Handle<GameObject> &gameobject) : Component(gameobject, "Path") {}
