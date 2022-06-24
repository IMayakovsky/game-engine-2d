#ifndef PLAYER_LEVEL_INFO_H
#define PLAYER_LEVEL_INFO_H

#include <utils/file_manager.h>

class GameLevel;

namespace player {

struct PlayerInfo
{
    qreal start_x;
    qreal start_y;
    qreal end_x;
    qreal end_y;
    qreal width;
    qreal height;

    void SetSpatialInfo(file::FileManager file);
    void SetCommonInfo();
    void DrawCommonInfo(GameLevel *game_level);
    void ChangeHealthRect(int width);
    void ChangeArrowAmount(QString value);
    void ChangeWeapon(bool isArcher);

private:
    GameLevel *_game_level = nullptr;

    QGraphicsRectItem *_health_background_rect;
    QGraphicsRectItem *_health_rect;
    QGraphicsPixmapItem *_main_image;
    QGraphicsPixmapItem *_sword_image;
    QGraphicsPixmapItem *_bow_image;
    QGraphicsPixmapItem *_arrow_image;
    QGraphicsSimpleTextItem *_arrows_amount;
};

}

#endif // PLAYER_LEVEL_INFO_H
