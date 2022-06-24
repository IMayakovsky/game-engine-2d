#include "colliders_types_enum.h"

namespace lineCollider {

CollidersTypes GetColliderType(QString name)
{
    if (name == "PERMEABLE_FOR_ARROW")
        return PERMEABLE_FOR_ARROW;
    if (name == "GROUND")
        return GROUND;
    else
        return OTHER;
}

}
