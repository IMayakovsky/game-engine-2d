#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "simple_game_object.h"

#include "utils/file_manager.h"
#include "arrow.h"

class TaskManager;

class PhysicsGameObject : public QObject, public SimpleGameObject
{
    Q_OBJECT

public:
    PhysicsGameObject(file::FileManager);
    ~PhysicsGameObject();
    void Jump(qreal x = 0);
    void Strike();
    void FallObject();
    void MoveBy(qreal x, qreal y);
    virtual void Shoot(qreal x, qreal y);
    int GetHealth();
    int GetArrowsAmount();
    virtual void SetHealth(int value);

    void CheckRepresentation(bool condition);

    qreal GetLeftX() const;
    qreal GetRightX() const;

    bool isGround = false;
    bool isMoveAllowed = true;
    bool isJumping = false;
    bool IsAppropriateGround(QGraphicsItem * item);

    virtual void CheckItemCollision(QGraphicsItem *item);

    void SwitchOnSword();
    void SwitchOnBow();

    void RightMove();
    void LeftMove();

    QVector<arrow::Arrow *> GetArrows();
    void RemoveArrow(int idx);

protected:
    QVector2D *size;
    QPixmap *image;
    QVector<QString> _simple_sprites;
    qreal _jump_height = 150;
    QVector<arrow::Arrow *> _arrows;
    int _health;
    bool _right_collision = false;
    bool _left_collision = false;
    bool _in_collision = false;
    qreal _speed = 5;
    file::FileManager _level_file;
    void MoveBySimple(qreal x, qreal y);
    void NextSimpleSprite();
    void PrevSimpleSprite();

private:
    void SetAllSprites();
    void SetAllCollision();
    QString _main_link;
    QString shoot_sprite;
    QString jump_sprite;
    QString strike_sprite;
    int _sprites_count;
    int cur_sprite;


signals:
    void LocationWasChanged();
    void NewArrowWasCreated(arrow::Arrow *);
    void WeaponWasChange(bool);
    void InCollision();
};

#endif // GAME_OBJECT_H
