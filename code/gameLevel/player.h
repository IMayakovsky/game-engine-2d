#ifndef PLAYER_H
#define PLAYER_H

#include "physics_game_object.h"

class GameLevel;

namespace player {

class PlayerInfo;

class Player : public PhysicsGameObject
{
    Q_OBJECT

public:
    Player(QString dataLink);
    ~Player();

    void SetInitialLocationsOnScene(file::FileManager file);
    void SetStartPositionOnScene();
    void SetEndPositionOnScene();
    void SetSizeOnScene();
    void DrawCommonInfo(GameLevel *game_level);
    void SetHealth(int value) override;
    void SetArrowsAmount(int value);
    int GetArrowsAmount();
    void RightJump();
    void LeftJump();
    void Shoot(qreal x, qreal y) override;
    bool IsArcher();
    bool isGodMode;

private:
    PlayerInfo *_info;
    qreal speed = 20;
    bool isArcher = false;
    int _arrow_count = 25;

public slots:
    void CheckArcherStatus(bool);

signals:
    void HealthWasChanged(int);


};

}

#endif // PLAYER_H
