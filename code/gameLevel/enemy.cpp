#include "enemy.h"

#include <QTimer>
#include <QGraphicsItem>
#include <QtMath>
#include <task_manager.h>

#include "game_level.h"
#include "utils/file_manager.h"
#include "enums/file_keys_enum.h"
#include "game_objects_manager.h"

namespace enemy {

static const qreal ATTACK_INTERVAL = 900;

/*!
 * \brief Enemy::Enemy
 * Constructor
 * \param file FileManager with data about enemy
 * \param player pointer on player
 */
Enemy::Enemy(file::FileManager file, PhysicsGameObject* player) : PhysicsGameObject(file)
{
    type = GetTypeFromString(file.GetStringValue(file::FileKeys::Type));
    SetTimers();
    connect(this, &Enemy::InCollision, this, &Enemy::StopMoving);
    _player = player;
    _vision = (40 * TaskManager::GetInstance().GetMainWindow()->width()) / 100;
}

/*!
 * \brief Enemy::Enemy
 * Copy constructor
 * \param enemy
 */
Enemy::Enemy(const Enemy &enemy) : PhysicsGameObject(enemy._level_file)
{
    Enemy(enemy._level_file, enemy._player);
    CheckRepresentation(enemy.right_representation);
    setPos(enemy.pos());
}

Enemy::~Enemy()
{

}

int Enemy::GetDemage()
{
    return _demage;
}

bool Enemy::IsAttackPossible()
{
    if (isAttackPossible)
    {
        isAttackPossible = false;
        QTimer::singleShot(ATTACK_INTERVAL, this, [&](){isAttackPossible = true;});
        return true;
    }
    return false;
}

EnemyTypes Enemy::GetType()
{
    return type;
}

void Enemy::CheckItemCollision(QGraphicsItem *item)
{
    Enemy enemy_copy(*this);
    PhysicsGameObject::CheckItemCollision(item);

    if (_right_collision || _left_collision)
    {
        if (_right_collision)
        {
            enemy_copy.moveBy(_speed/2, -_jump_height);
            if (!enemy_copy.collidesWithItem(item))
            {
                this->Jump(_speed/2);
                _right_collision = false;
            }
        }
        else
        {
            enemy_copy.moveBy(-_speed/2, -_jump_height);
            if (!item->collidesWithItem(&enemy_copy))
            {
                this->Jump(-_speed/2);
                _left_collision = false;
            }
        }

    }
}

/*!
 * \brief Enemy::Shoot
 * Arrow shot
 * \param x x shot coord
 * \param y y shot coord
 */
void Enemy::Shoot(qreal x, qreal y)
{
    SwitchOnBow();
    PhysicsGameObject::Shoot(x, y);
}

/*!
 * \brief Enemy::PlayerWasDetected
 * is called when enemy detects the player
 */
void Enemy::PlayerWasDetected()
{
    _attack_timer->start();
}

void Enemy::SetObjectManager(GameObjectManager *manager)
{
    _obj_manager = manager;
}

/*!
 * \brief Enemy::IsCollides
 * \return true if enemy is left or right collides
 * false otherwise
 */
bool Enemy::IsCollides()
{
    return _left_collision || _right_collision;
}

/*!
 * \brief Enemy::IsAttacking
 * \return true if enemy has an attacking position right now
 * false otherwise
 */
bool Enemy::IsAttacking()
{
    return _attack_timer->isActive();
}

void Enemy::SetShootPossibility(bool status)
{
    isShootPossible = status;
}

void Enemy::SetVisionPossibility(bool status)
{
    if (status)
        isPlayerInVision = true;
    else
    {
        if (_moving_timer->isActive())
            _moving_timer->stop();
        isPlayerInVision = false;
    }
}

void Enemy::SetTimers()
{
    _moving_timer = new QTimer(this);
    _moving_timer->setInterval(20);
    connect(_moving_timer, &QTimer::timeout, this, [&](){
        if (isActive())
            FollowPlayer();
    });

    _attack_timer = new QTimer(this);
    _attack_timer->setInterval(10);
    connect(_attack_timer, &QTimer::timeout, this, [&](){
        if (isPlayerInVision && isActive())
            ToAttack();
    });
}

void Enemy::FollowPlayer()
{
    if ((type == EnemyTypes::Warrior && this->collidesWithItem(_player))
            || (type == EnemyTypes::Archer && !this->collidesWithItem(_player)))
        _moving_timer->stop();
    else if (isActive())
    {
        Enemy enemy_copy(*this);
        enemy_copy.moveBy(x_move, y_move);
        if (!_obj_manager->CheckEnemyMoving(&enemy_copy))
            return;
        MoveBy(x_move, y_move);
    }
}

void Enemy::ToAttack()
{

    if (!isPlayerInVision)
        return;

    qreal player_mid = _player->GetLeftX() + _player->GetWidth()/2;
    qreal this_mid = this->GetLeftX() + this->GetWidth()/2;

    CheckRepresentation(player_mid >= GetRightX());

    if (type == EnemyTypes::Warrior && !this->collidesWithItem(_player))
    {
        x_move = player_mid - this_mid > 0 ? _speed : -_speed;
        if (!_moving_timer->isActive())
            _moving_timer->start();
    }
    else if (type == EnemyTypes::Archer && !this->collidesWithItem(_player)
             && isShootPossible && IsAttackPossible())
    {
        Shoot(player_mid, _player->y() + _player->GetHeight()/4);
    }
    if (collidesWithItem(_player))
    {
        if (_moving_timer->isActive())
            _moving_timer->stop();
        if (IsAttackPossible())
        {
            Strike();
            AttackWas(_demage);
        }
    }
}

void Enemy::CheckPlayerLocation()
{
    qreal dist = qSqrt(qPow(_player->pos().x() - this->pos().x(), 2)
                       + qPow(_player->pos().y() - this->pos().y(), 2));
    if ((_player->x() < x() && right_representation)
            || (_player->x() > x() && !right_representation))
    {
        dist = dist*2;
    }
    if (!_attack_timer->isActive() && dist < _vision)
        PlayerWasDetected();
}

void Enemy::StopMoving()
{
    _moving_timer->stop();
}

}
