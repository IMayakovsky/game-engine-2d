#include "checkpoint.h"

#include "enums/file_keys_enum.h"

namespace spacialItem
{

/*!
 * \brief Checkpoint::Checkpoint
 * Constructor
 * \param file FileManager with checkpoint's data
 */
Checkpoint::Checkpoint(file::FileManager file) : SpacialItem(file)
{
    if (type == Types::Checkpoint)
        SetCheckpoint(file);
}

Functions Checkpoint::GetFunction()
{
    return _function;
}

QPointF Checkpoint::GetTransferPoint()
{
    return _transfer;
}

QString Checkpoint::GetSwitchCard()
{
    return _card;
}

int Checkpoint::GetPlayerZValue()
{
    return _player_z_value;
}

void Checkpoint::SetCheckpoint(file::FileManager file)
{
    QString function = file.GetStringValue(file::FileKeys::Function);
    _function = GetFunctionFromString(function);
    if (_function == Functions::SwitchCard)
    {
        _card = file.GetStringValue("card");
    }
    else if (_function == Functions::ChangeLocation)
    {
        _transfer.setX(file.GetByWidthRatio("x_transfer"));
        _transfer.setY(file.GetByHeightRatio("y_transfer"));
        _player_z_value = file.GetRealValue("playerZValue");
        (_player_z_value == 0) && (_player_z_value = 50);
    }
    else
    {
        type = Types::None;
    }
}


}
