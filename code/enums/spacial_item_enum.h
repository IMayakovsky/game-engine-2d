#ifndef SPACIAL_ITEMS_TYPES_H
#define SPACIAL_ITEMS_TYPES_H

#include <QString>

namespace spacialItem
{
    enum class Types
    {
        Checkpoint,
        Arrow,
        Potion,
        None
    };

    Types GetTypeFromString(QString type);

    enum class Functions
    {
        SwitchCard,
        ChangeLocation,
        None
    };

    Functions GetFunctionFromString(QString type);
}



#endif // SPACIAL_ITEMS_TYPES_H
