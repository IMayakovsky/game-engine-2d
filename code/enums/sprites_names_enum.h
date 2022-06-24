#ifndef SPRITES_NAMES_ENUM_H
#define SPRITES_NAMES_ENUM_H

#include <QString>

namespace sprites
{
    enum SpritesNames
    {
        Count,
        Simple,
        Shoot,
        Strike,
        Jump
    };

    QString GetSpriteName(SpritesNames key);
}

#endif // SPRITES_NAMES_ENUM_H
