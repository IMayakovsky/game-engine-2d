#ifndef ENEMY_ENUM_H
#define ENEMY_ENUM_H

#include <QString>

namespace enemy
{
    enum class EnemyTypes
    {
        Archer,
        Warrior
    };

    EnemyTypes GetTypeFromString(QString string);
}

#endif // ENEMY_ENUM_H
