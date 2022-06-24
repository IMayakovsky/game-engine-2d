#ifndef GAME_OBJECTS_SETTER_H
#define GAME_OBJECTS_SETTER_H

#include "player_info.h"
#include "checkpoint.h"
#include "physics_game_object.h"
#include "spacial_item.h"
#include "enemy.h"
#include "player.h"
#include "line_collider.h"

#include <memory>

class GameLevel;
class SimpleGameObject;
class SpacialItem;

#include <QString>
#include <QPixmap>
#include <QObject>

class GameObjectSetter : public QObject
{
    Q_OBJECT

public:
    GameObjectSetter(GameLevel *game_level, player::Player *player, QString data_link);
    ~GameObjectSetter();
    void RestartAfterGameOver();
    player::Player* GetPlayer();
    QGraphicsSimpleTextItem * GetCheckpointText();

    QVector<SimpleGameObject*> grounds;
    QVector<SimpleGameObject*> terrains_objects;
    QVector<lineCollider::LineCollider*> line_colliders;
    QVector<spacialItem::SpacialItem *> collectedItems;
    QVector<spacialItem::Checkpoint *> checkpoints;
    QVector<enemy::Enemy *> enemies;
    QGraphicsSimpleTextItem * checkpoint_text;
    void SetPlayer();

private:
    QString _data_link;
    GameLevel *_game_level;
    player::Player* _player;
    QPixmap *_background;
    void SetGround();
    void SetEnemies();
    void SetPlayerInfo();
    void AddColliders();
    void SetTerrainObjects();
    void SetCollectedItems();
    void SetCheckpoints();
    void SetCheckpointText();
    void SetSimpleObjects(QString link, QVector<SimpleGameObject *> *list, bool set_col = false);
    void SetBackground();
    void SetCollider(SimpleGameObject *);
    QSize _window_size;

protected:



};

#endif // GAME_OBJECTS_SETTER_H
