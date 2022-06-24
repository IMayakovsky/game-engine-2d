#include "arrow.h"
#include "game_level.h"
#include "player.h"
#include "player_info.h"

#include "saves_manager.h"
#include "task_manager.h"

namespace player {

/*!
 * \brief Player::Player
 * Constructor
 * \param dataLink link on file with class data
 */
Player::Player(QString dataLink)
    : PhysicsGameObject (file::FileManager(dataLink + "/main.txt"))
{
    _info = new PlayerInfo();
    _info->SetCommonInfo();
    connect(this, SIGNAL(WeaponWasChange(bool)), this, SLOT(CheckArcherStatus(bool)));
    connect(this, &Player::NewArrowWasCreated, this, [&](){ SetArrowsAmount(_arrow_count - 1); });
    setZValue(50);
    TaskManager::GetInstance().GetSavesManager()->
            LoadOptionsSaveValue(savesManager::OptionsSaves::GodMode, &isGodMode);
}

Player::~Player()
{

}

void Player::SetInitialLocationsOnScene(file::FileManager file)
{
    _info->SetSpatialInfo(file);
    if (right_representation)
        SetStartPositionOnScene();
    else
        SetEndPositionOnScene();
}

void Player::SetStartPositionOnScene()
{
    setPos(_info->start_x, _info->start_y);
}

void Player::SetEndPositionOnScene()
{
    setPos(_info->end_x, _info->end_y);
}

void Player::SetSizeOnScene()
{
    SetSize(_info->width, _info->height);
}

void Player::DrawCommonInfo(GameLevel *game_level)
{
    _info->DrawCommonInfo(game_level);
}

void Player::RightJump()
{
    Jump(speed);
}

void Player::LeftJump()
{
    Jump(-speed);
}

void Player::Shoot(qreal x, qreal y)
{
    if (_arrow_count > 0)
        PhysicsGameObject::Shoot(x, y);
}

bool Player::IsArcher()
{
    return isArcher;
}

void Player::SetHealth(int value)
{
    (value > 100) && (value = 100);
    _health = value;
    _info->ChangeHealthRect(value);
}

void Player::SetArrowsAmount(int value)
{
    QString string_value;
    if (isGodMode)
        string_value = "∞";
    else
    {
        _arrow_count = value;
        string_value = QString::number(value);
    }
    _info->ChangeArrowAmount(string_value);
}

int Player::GetArrowsAmount()
{
    return _arrow_count;
}

void Player::CheckArcherStatus(bool status)
{
    if (isArcher == status)
        return;
    isArcher = status;
    _info->ChangeWeapon(status);
}

}


