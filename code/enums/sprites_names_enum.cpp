#include "sprites_names_enum.h"

namespace sprites
{

QString GetSpriteName(SpritesNames key)
{
    switch (key)
    {
    case Count:
        return "spritesAmount";
    case Shoot:
        return "Shoot";
    case Strike:
        return "Strike";
    case Jump:
        return "Jump";
    default:
        return "SP";
    }
}

}
