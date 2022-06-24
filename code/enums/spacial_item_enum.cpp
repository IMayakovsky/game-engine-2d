#include "spacial_item_enum.h"

namespace spacialItem
{

Types GetTypeFromString(QString type)
{
    if (type == "Checkpoint")
        return Types::Checkpoint;
    else if (type == "Arrow")
        return Types::Arrow;
    else if (type == "Potion")
        return Types::Potion;
    else
        return Types::None;
}

Functions GetFunctionFromString(QString type)
{
    if (type == "SwitchCard")
        return Functions::SwitchCard;
    else if (type == "ChangeLocation")
        return Functions::ChangeLocation;
    else
        return Functions::None;
}

}
