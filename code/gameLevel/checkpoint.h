#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "spacial_item.h"

#include <QVector2D>

#include "utils/file_manager.h"

namespace spacialItem
{

class Checkpoint : public SpacialItem
{

public:
    Checkpoint(file::FileManager file);
    Functions GetFunction();
    QPointF GetTransferPoint();
    QString GetSwitchCard();
    int GetPlayerZValue();

private:
    Functions _function;
    QPointF _transfer;
    QString _card;
    int _player_z_value = 50;
    void SetCheckpoint(file::FileManager file);
};

}

#endif // CHECKPOINT_H
