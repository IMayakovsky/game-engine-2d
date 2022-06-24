#include "enemy_enum.h"

namespace enemy
{

EnemyTypes GetTypeFromString(QString string)
{
    if (string == "Archer")
        return EnemyTypes::Archer;
    else
        return EnemyTypes::Warrior;
}

}
