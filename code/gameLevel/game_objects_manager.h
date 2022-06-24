#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include <audio_manager.h>
#include <saves_manager.h>

class GameLevel;
class GameObjectSetter;
class PhysicsGameObject;
class SimpleGameObject;

#include "checkpoint.h"
#include "enemy.h"
#include "player.h"
#include "arrow.h"

class GameObjectManager : public QObject
{
    Q_OBJECT

public:
    GameObjectManager(GameLevel *game_level, GameObjectSetter *obj_setter);

    void Update();

    void CheckKeysStatus(QMap<Qt::Key, bool>);
    void PlayerStrike();
    void PlayerShoot(qreal target_x, qreal target_y);
    void ConnectPlayerToEnemy();
    void DisconnectPlayerFromEnemy();

private:
    GameLevel *_game_level;
    GameObjectSetter *_obj_setter;
    player::Player *_player;
    spacialItem::Checkpoint *_active_checkpoint = nullptr;

    audioManager::AudioManager shot_sound;
    audioManager::AudioManager strike_sound;
    audioManager::AudioManager gather_item_sound;
    savesManager::SavesManager *_saves_manager;

    void UpdateEnemies();
    void UpdateArrowsOfEnemy(enemy::Enemy *enemy);
    bool IsEnemyAbleToSeePLayer(enemy::Enemy *enemy);
    bool IsEnemyShotPossible(enemy::Enemy *enemy);
    void SetSounds();
    void CheckPhysics(PhysicsGameObject*);
    void UpdateArrowsOfPlayer();

    bool CheckArrowCollisionWithEnemy(arrow::Arrow *);
    bool CheckCommonArrowCollision(arrow::Arrow *);
    void CheckCollectedItemsCollision();
    void CheckCheckpointsCollision();
    void CheckWindowBordersCollision(PhysicsGameObject*);
    void IsPlayerMove();


    void CheckEnemyAttack(enemy::Enemy *enemy);
    void PickUpPotion();
    void PickUpArrow(int count);
    void DoCheckpointAction();

    QVector<QMetaObject::Connection> enemy_connections;

public slots:
    void UpdateAfterPlayerMove();
    void PlayerWasHitten(int enemy_demage);
    bool CheckEnemyMoving(enemy::Enemy*);

};




#endif // GAME_OBJECT_MANAGER_H
