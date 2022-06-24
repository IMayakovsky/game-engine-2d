#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <QGraphicsScene>

#include "utils/file_manager.h"
#include "arrow.h"

class KeyController;
class GameLevelsManager;
class GameObjectSetter;
class GameObjectManager;

class GameLevel : public QGraphicsScene
{
    Q_OBJECT

public:
    GameLevel(QString, GameLevelsManager*, QGraphicsScene *parent = nullptr);
    ~GameLevel();
    bool GetDeveloperModeStatus();
    void Start();
    void Stop();
    void SwitchScene(QString name);
    void SwitchOnNext();
    void SwitchOnPrev();
    void GameOver();

private:
    bool isStoryMode;
    bool isDeveloperMode;
    bool isUpdating = false;

    QString next_card;
    QString prev_card;

    KeyController *_key_controller;
    GameObjectManager *_obj_manager;
    GameObjectSetter *_obj_setter;
    GameLevelsManager *_game_manager;
    QString _data_link;

    QTimer *_main_timer;
    QTimer *_keys_timer;
    QGraphicsRectItem *_health_rect;

    void SetCard();

    bool isCurrentLevel = false;

    void SetTimer();
    void UpdateWithDeveloperMode();

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

public slots:
    void DrawNewArrow(arrow::Arrow *);

private slots:
    void Update();



};

#endif // GAME_LEVEL_H
