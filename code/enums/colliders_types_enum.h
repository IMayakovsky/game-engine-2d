#ifndef COLLIDERS_TYPES_ENUM_H
#define COLLIDERS_TYPES_ENUM_H

#include <QString>

namespace lineCollider
{
    enum CollidersTypes
    {
        PERMEABLE_FOR_ARROW,
        GROUND,
        OTHER
    };

    CollidersTypes GetColliderType(QString name);
}

#endif // COLLIDERS_TYPES_ENUM_H
