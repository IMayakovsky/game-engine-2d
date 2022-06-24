#ifndef ENEMY_H
#define ENEMY_H

#include "physics_game_object.h"
#include "enums/enemy_enum.h"

class GameObjectManager;

namespace enemy
{

class Enemy : public PhysicsGameObject
{
    Q_OBJECT

public:
    Enemy(file::FileManager, PhysicsGameObject*);
    Enemy(const Enemy &enemy);
    ~Enemy();
    int GetDemage();
    EnemyTypes GetType();
    void CheckItemCollision(QGraphicsItem *item) override;
    bool IsJumpPossible(QGraphicsItem *item);
    void Shoot(qreal x, qreal y) override;
    void PlayerWasDetected();
    void SetObjectManager(GameObjectManager*);
    bool IsCollides();
    bool IsAttacking();
    void SetShootPossibility(bool status);
    void SetVisionPossibility(bool status);

public slots:
     void CheckPlayerLocation();

private:
    QString _main_link;
    int _demage = 5;
    int _vision = 800;
    bool isAttackStatus = false;
    bool isPlayerInVision = false;
    bool isAttackPossible = true;
    bool isShootPossible = false;
    QVector<arrow::Arrow *> _arrows;
    EnemyTypes type;
    QTimer *_moving_timer;
    QTimer *_attack_timer;
    qreal x_move = 0;
    qreal y_move = 0;
    PhysicsGameObject *_player;
    GameObjectManager *_obj_manager;

    void SetTimers();
    void FollowPlayer();
    void ToAttack();
    bool IsAttackPossible();

private slots:
     void StopMoving();

signals:
     void AttackWas(int demage);
};

}

#endif // ENEMY_H
