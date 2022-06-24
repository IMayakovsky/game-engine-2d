#include "player_info.h"

#include "game_level.h"
#include "enums/file_keys_enum.h"

namespace player {

void PlayerInfo::SetSpatialInfo(file::FileManager file)
{
    start_x = file.GetByWidthRatio("start_x");
    start_y = file.GetByHeightRatio("start_y");
    end_x = file.GetByWidthRatio("end_x");
    end_y = file.GetByHeightRatio("end_y");
    width = file.GetByWidthRatio(file::FileKeys::Width);
    height = file.GetByHeightRatio(file::FileKeys::Height);
}

void PlayerInfo::SetCommonInfo()
{
    file::FileManager file("../src/assets/player/infoPanel.txt");

    qreal x1 = file.GetByWidthRatio("rect_x1");
    qreal y1 = file.GetByHeightRatio("rect_y1");
    qreal y2 = file.GetByHeightRatio("rect_y2");

    _health_background_rect = new QGraphicsRectItem(x1, y1, 300, y2);
    _health_background_rect->setBrush(QBrush(Qt::darkGray));

    _health_rect = new QGraphicsRectItem(x1, y1, 300, y2);
    _health_rect->setBrush(QBrush(Qt::darkRed));

    _main_image = new QGraphicsPixmapItem();
    x1 = file.GetByWidthRatio("infoPanel_width");
    y1 = file.GetByHeightRatio("infoPanel_height");
    _main_image->setPixmap(QPixmap(file.GetStringValue("infoPanelLink")).scaled(x1, y1));
    _main_image->moveBy(file.GetByWidthRatio("infoPanel_x"), file.GetByHeightRatio("infoPanel_y"));

    _sword_image = new QGraphicsPixmapItem();
    x1 = file.GetByWidthRatio("sword_width");
    y1 = file.GetByHeightRatio("sword_height");
    _sword_image->setPixmap(QPixmap(file.GetStringValue("swordLink")).scaled(x1, y1));
    _sword_image->moveBy(file.GetByWidthRatio("sword_x"), file.GetByHeightRatio("sword_y"));

    _bow_image = new QGraphicsPixmapItem();
    x1 = file.GetByWidthRatio("bow_width");
    y1 = file.GetByHeightRatio("bow_height");
    _bow_image->setPixmap(QPixmap(file.GetStringValue("bowLink")).scaled(x1, y1));
    _bow_image->moveBy(file.GetByWidthRatio("bow_x"), file.GetByHeightRatio("bow_y"));

    _arrow_image = new QGraphicsPixmapItem();
    x1 = file.GetByWidthRatio("arrow_width");
    y1 = file.GetByHeightRatio("arrow_height");
    _arrow_image->setPixmap(QPixmap(file.GetStringValue("arrowLink")).scaled(x1, y1));
    _arrow_image->moveBy(file.GetByWidthRatio("arrow_x"), file.GetByHeightRatio("arrow_y"));

    _arrows_amount = new QGraphicsSimpleTextItem();
    _arrows_amount->setBrush(QBrush(Qt::black));
    _arrows_amount->setFont(QFont("Helvetica", 18, QFont::Bold));
    _arrows_amount->setPen(QPen(Qt::white));
    _arrows_amount->setPos(file.GetByWidthRatio("amount_arrows_x"),
                           file.GetByHeightRatio("amount_arrows_y"));
}

void PlayerInfo::DrawCommonInfo(GameLevel *game_level)
{
    _game_level = game_level;
    game_level->addItem(_health_background_rect);
    game_level->addItem(_health_rect);
    game_level->addItem(_main_image);
    game_level->addItem(_sword_image);
    game_level->addItem(_arrow_image);
    game_level->addItem(_arrows_amount);
}

void PlayerInfo::ChangeHealthRect(int width)
{
    QRectF rect = _health_rect->rect();
    rect.setWidth(width*3);
    _health_rect->setRect(rect);
}

void PlayerInfo::ChangeArrowAmount(QString value)
{
    _arrows_amount->setText(value);
}

void PlayerInfo::ChangeWeapon(bool isArcher)
{
    if (_game_level == nullptr)
        return;
    if (isArcher)
    {
        _game_level->removeItem(_sword_image);
        _game_level->addItem(_bow_image);
    }
    else
    {
        _game_level->removeItem(_bow_image);
        _game_level->addItem(_sword_image);
    }
}

}
