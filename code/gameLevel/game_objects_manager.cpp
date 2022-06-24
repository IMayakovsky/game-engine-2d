#include "game_objects_manager.h"

#include <QPolygon>
#include <QDebug>
#include <QGraphicsItem>
#include <task_manager.h>
#include <QTimer>
#include <QLineF>
#include <QThread>

#include <saves_manager.h>
#include "line_collider.h"
#include "game_level.h"
#include "player.h"
#include "enemy.h"
#include "simple_game_object.h"
#include "game_objects_setter.h"
#include "spacial_item.h"

static const int HEALTH_POTION_EFFECT = 10;

/*!
 * \brief GameObjectManager::GameObjectManager
 * Constructor
 * \param game_level appropriate GameLevel
 * \param obj_setter appropriate GameObjectSetter
 */
GameObjectManager::GameObjectManager(GameLevel *game_level, GameObjectSetter *obj_setter)
{
    this->_game_level = game_level;
    this->_obj_setter = obj_setter;
    _player = _obj_setter->GetPlayer();
    SetSounds();
    _saves_manager = TaskManager::GetInstance().GetSavesManager();
}

/*!
 * \brief GameObjectManager::CheckPhysics
 * Checks all \param item collisions and his physics
 */
void GameObjectManager::CheckPhysics(PhysicsGameObject *item)
{
    for (SimpleGameObject *ground : _obj_setter->grounds)
    {
        if (item->collidesWithItem(ground))
        {
            bool p = false;
            if (!item->isGround && !item->isJumping)
                p = item->IsAppropriateGround(ground);
            if (!p)
                item->CheckItemCollision(ground);
        }
    }
    for (lineCollider::LineCollider *collider : _obj_setter->line_colliders)
    {
        if (item->collidesWithItem(collider))
        {
            bool p = false;
            if (collider->GetType() == lineCollider::GROUND
                    && !item->isGround && !item->isJumping)
            {
                p = item->IsAppropriateGround(collider);
            }
            if (!p)
            item->CheckItemCollision(collider);
        }
    }
    if (!item->isGround && !item->isJumping)
    {
        item->FallObject();
    }
}

void GameObjectManager::UpdateArrowsOfPlayer()
{
    int k = 0;
    for (arrow::Arrow * arrow : _player->GetArrows())
    {
        if (arrow->visible)
        {
            (!CheckCommonArrowCollision(arrow))
                    && (CheckArrowCollisionWithEnemy(arrow));
        }
        else
        {
            _game_level->removeItem(arrow);
            _player->RemoveArrow(k);
            k--;
        }
        k++;
    }
}

bool GameObjectManager::CheckArrowCollisionWithEnemy(arrow::Arrow *arrow)
{
    for (int i = 0; i < _obj_setter->enemies.size(); i++)
    {
        enemy::Enemy *enemy =  _obj_setter->enemies[i];
        if (enemy->collidesWithItem(arrow))
        {
            arrow->Stop();
            enemy->SetHealth(enemy->GetHealth() - arrow->GetDemage());
            enemy->PlayerWasDetected();
            if (enemy->GetHealth() <= 0)
                enemy->visible = false;
            return true;
        }
    }
    return false;
}

bool GameObjectManager::CheckCommonArrowCollision(arrow::Arrow *arrow)
{
    for (int i = 0; i < _obj_setter->grounds.size(); i++)
    {
        if (_obj_setter->grounds[i]->collidesWithItem(arrow))
        {
            arrow->Stop();
            return true;
        }
    }
    return false;
}

void GameObjectManager::UpdateEnemies()
{
    int k = 0;
    for (enemy::Enemy *enemy : _obj_setter->enemies)
    {
        if (enemy->visible)
        {
            CheckPhysics(enemy);
            if (enemy->IsAttacking())
                CheckEnemyAttack(enemy);
            if (enemy->GetType() == enemy::EnemyTypes::Archer)
            {
                UpdateArrowsOfEnemy(enemy);;
            }

        }
        else
        {
            _game_level->removeItem(enemy);
            enemy->deleteLater();
            _obj_setter->enemies.remove(k);
            k--;
        }
        k++;
    }
}

void GameObjectManager::UpdateArrowsOfEnemy(enemy::Enemy *enemy)
{
    int k = 0;
    for (arrow::Arrow *arrow : enemy->GetArrows())
    {
        if (arrow->visible)
        {
            CheckCommonArrowCollision(arrow);
            if (arrow->collidesWithItem(_player))
            {
                arrow->Stop();
                PlayerWasHitten(arrow->GetDemage());
            }
        }
        else
        {
            _game_level->removeItem(arrow);
            enemy->RemoveArrow(k);
            k--;
        }
        k++;
    }
}

bool GameObjectManager::IsEnemyAbleToSeePLayer(enemy::Enemy *enemy)
{
    QLineF vector(enemy->GetLeftX() + enemy->GetWidth()/2,
                             enemy->y() + enemy->GetHeight()/2,
                             _player->GetLeftX() + _player->GetWidth()/2,
                             _player->y() + _player->GetHeight()/2);

    for (lineCollider::LineCollider *coll : _obj_setter->line_colliders)
    {
        QPointF point;
        if (coll->GetType() == lineCollider::CollidersTypes::GROUND
                && vector.intersects(coll->GetLine(), &point) == 1)
        {
            return false;
        }
    }
    return true;
}

bool GameObjectManager::IsEnemyShotPossible(enemy::Enemy *enemy)
{
    QGraphicsLineItem vector(enemy->x(), enemy->y() + enemy->GetHeight()/4,
                             _player->x(), _player->y() + _player->GetHeight()/4);

    for (SimpleGameObject *ground : _obj_setter->grounds)
    {
        if (vector.collidesWithItem(ground))
        {
            return false;
        }
    }
    return true;
}


void GameObjectManager::CheckCollectedItemsCollision()
{
    for (int i = 0; i < _obj_setter->collectedItems.size(); i++)
    {
        spacialItem::SpacialItem *item = _obj_setter->collectedItems[i];
        if (_player->collidesWithItem(item))
        {
            gather_item_sound.Start();
            if (item->GetType() == spacialItem::Types::Potion)
            {
                PickUpPotion();
            }
            else if (item->GetType() == spacialItem::Types::Arrow)
            {
                PickUpArrow(1);
            }
            _game_level->removeItem(item);
            delete item;
            _obj_setter->collectedItems.remove(i);

        }
    }
}

void GameObjectManager::CheckCheckpointsCollision()
{
    bool isSameCheckpoint = false;
    for (int i = 0; i < _obj_setter->checkpoints.size(); i++)
    {
        spacialItem::Checkpoint *checkpoint = _obj_setter->checkpoints[i];
        if (_player->collidesWithItem(checkpoint))
        {
            if (_active_checkpoint == nullptr || _active_checkpoint == checkpoint)
                isSameCheckpoint = true;
            if (_active_checkpoint == nullptr)
            {
                _active_checkpoint = checkpoint;
                _game_level->addItem(_obj_setter->GetCheckpointText());
            }

        }
    }
    if (!isSameCheckpoint && _active_checkpoint != nullptr)
    {
        _active_checkpoint = nullptr;
        _game_level->removeItem(_obj_setter->GetCheckpointText());
    }
}

void GameObjectManager::CheckWindowBordersCollision(PhysicsGameObject *item)
{
    qreal max_x = TaskManager::GetInstance().GetMainWindow()->width();
    int w = item->boundingRect().width();
    if (item->right_representation && item->x() + w >= max_x)
    {
        item->setX(max_x - w);
        _game_level->SwitchOnNext();
    }
    else if (!item->right_representation && item->x() - w <= 0)
    {
        item->setX(0 + w);
         _game_level->SwitchOnPrev();
    }
}

void GameObjectManager::PlayerWasHitten(int enemy_demage)
{
    bool isGodMode;
    _saves_manager->LoadOptionsSaveValue(savesManager::OptionsSaves::GodMode, &isGodMode);
    if (isGodMode)
        return;
    int health = _player->GetHealth() - enemy_demage;
    _player->SetHealth(_player->GetHealth() - enemy_demage);
    if (health <= 0)
    {
        _game_level->GameOver();
    }
}

bool GameObjectManager::CheckEnemyMoving(enemy::Enemy *enemy)
{
    for (SimpleGameObject *ground : _obj_setter->grounds)
    {
        if (enemy->collidesWithItem(ground))
        {
            enemy->CheckItemCollision(ground);
            if (enemy->IsCollides())
                return false;
        }
    }
    for (lineCollider::LineCollider *collider : _obj_setter->line_colliders)
    {
        if (enemy->collidesWithItem((QGraphicsItem*)collider))
        {
            enemy->CheckItemCollision((QGraphicsItem*)collider);
            if (enemy->IsCollides())
                return false;
        }
    }
    return true;
}

void GameObjectManager::CheckEnemyAttack(enemy::Enemy *enemy)
{
    if (enemy->GetType() == enemy::EnemyTypes::Archer)
        enemy->SetShootPossibility(IsEnemyShotPossible(enemy));
    enemy->SetVisionPossibility(IsEnemyAbleToSeePLayer(enemy));
}

void GameObjectManager::PickUpPotion()
{
    int health = _player->GetHealth() + HEALTH_POTION_EFFECT;
    _player->SetHealth(health);
}

void GameObjectManager::PickUpArrow(int count)
{
    _player->SetArrowsAmount(_player->GetArrowsAmount() + count);

}

void GameObjectManager::DoCheckpointAction()
{
    if (_active_checkpoint == nullptr)
        return;
    if (_active_checkpoint->GetFunction() == spacialItem::Functions::ChangeLocation)
    {
        _player->setPos(_active_checkpoint->GetTransferPoint());
        _player->setZValue(_active_checkpoint->GetPlayerZValue());
    }
    else
    {
        _game_level->SwitchScene(_active_checkpoint->GetSwitchCard());
        _active_checkpoint = nullptr;
    }
}

void GameObjectManager::ConnectPlayerToEnemy()
{
    for (int i = 0; i < _obj_setter->enemies.size(); i++)
    {
        enemy::Enemy *enemy =  _obj_setter->enemies[i];
        enemy_connections.push_back(connect(enemy, &enemy::Enemy::AttackWas,
                this, &GameObjectManager::PlayerWasHitten));
        enemy_connections.push_back(connect(_player, &player::Player::LocationWasChanged,
                                            enemy, &enemy::Enemy::CheckPlayerLocation));
        enemy->SetObjectManager(this);
    }
}

void GameObjectManager::DisconnectPlayerFromEnemy()
{
    for (int i = 0; i < enemy_connections.size(); i++)
    {
        disconnect(enemy_connections[i]);
    }
    enemy_connections.clear();
}

void GameObjectManager::UpdateAfterPlayerMove()
{
    CheckCollectedItemsCollision();
    CheckCheckpointsCollision();
    CheckWindowBordersCollision(_player);
}

void GameObjectManager::Update()
{
    CheckPhysics(_player);
    UpdateEnemies();
    UpdateArrowsOfPlayer();
}

void GameObjectManager::CheckKeysStatus(QMap<Qt::Key, bool> keys_status)
{
    if (keys_status[Qt::Key_Space])
    {
        if (keys_status[Qt::Key_D])
            _player->RightJump();
        else if (keys_status[Qt::Key_A])
            _player->LeftJump();
        else
            _player->Jump();
    }
    else if (keys_status[Qt::Key_D])
    {
        _player->RightMove();
    }
    else if (keys_status[Qt::Key_A])
    {
        _player->LeftMove();
    }
    if (keys_status[Qt::Key_F])
    {
        _player->Strike();
        PlayerStrike();
    }
    if (keys_status[Qt::Key_1])
    {
        _player->SwitchOnSword();
    }
    if (keys_status[Qt::Key_2])
    {
        _player->SwitchOnBow();
    }
    if (keys_status[Qt::Key_E])
    {
        DoCheckpointAction();
    }
}

void GameObjectManager::PlayerStrike()
{
    strike_sound.Start();
    for (int i = 0; i < _obj_setter->enemies.size(); i++)
    {
        enemy::Enemy *enemy =  _obj_setter->enemies[i];
        if (_player->collidesWithItem(enemy))
        {
            enemy->visible = false;
            return;
        }
    }
}

void GameObjectManager::PlayerShoot(qreal target_x, qreal target_y)
{
    if (!_player->IsArcher())
        return;
    else
        _player->Shoot(target_x, target_y);
}

void GameObjectManager::SetSounds()
{
    strike_sound.SetMedia(audioManager::AudioNames::Strike);
    gather_item_sound.SetMedia(audioManager::AudioNames::Gather);
}
