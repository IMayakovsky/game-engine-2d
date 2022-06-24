#include "game_level.h"

#include <QTimer>
#include <QGraphicsSceneMouseEvent>

#include "game_objects_manager.h"
#include "game_objects_setter.h"
#include "key_controller.h"
#include "game_levels_manager.h"
#include "enums/file_keys_enum.h"

/*!
 * \brief GameLevel::GameLevel
 * \param data_link link on level's data
 * \param game_manager appropriate GameLevelsManager
 * \param parent
 */
GameLevel::GameLevel(QString data_link, GameLevelsManager *game_manager,
                     QGraphicsScene *parent) : QGraphicsScene(parent)
{
    _data_link = data_link;
    _game_manager = game_manager;
    this->isDeveloperMode = game_manager->GetDeveloperModeStatus();
    _obj_setter = new GameObjectSetter(this, game_manager->GetPlayer(), _data_link);
    _obj_manager = new GameObjectManager(this, _obj_setter);
    _key_controller = new KeyController(this, _obj_manager);
    SetTimer();
    SetCard();
}

GameLevel::~GameLevel()
{
    _main_timer->deleteLater();
    _keys_timer->deleteLater();
    _obj_setter->deleteLater();
    _obj_manager->deleteLater();
    delete _key_controller;
    clear();
}

bool GameLevel::GetDeveloperModeStatus()
{
    return isDeveloperMode;
}

/*!
 * \brief GameLevel::Start
 * is called, when GameLevel is active
 */
void GameLevel::Start()
{
    _obj_setter->SetPlayer();
    _main_timer->start();
    if (isDeveloperMode)
        return;
    connect(_obj_setter->GetPlayer(), &player::Player::NewArrowWasCreated,
            this, &GameLevel::DrawNewArrow);
    connect(_obj_setter->GetPlayer(), &player::Player::LocationWasChanged, _obj_manager,
            &GameObjectManager::UpdateAfterPlayerMove);
    _keys_timer->start();
    _obj_manager->ConnectPlayerToEnemy();
}

/*!
 * \brief GameLevel::Stop
 * is called, when GameLevel isn't active
 */
void GameLevel::Stop()
{
    _main_timer->stop();
    _keys_timer->stop();
    disconnect(_obj_setter->GetPlayer(), &player::Player::NewArrowWasCreated,
               this, &GameLevel::DrawNewArrow);
    disconnect(_obj_setter->GetPlayer(), &player::Player::LocationWasChanged,
               _obj_manager, &GameObjectManager::UpdateAfterPlayerMove);
    _key_controller->SetKeysStatus();
    _obj_manager->DisconnectPlayerFromEnemy();
}

/*!
 * \brief GameLevel::SwitchScene
 * Switches current scene on scene with name
 * \param name
 */
void GameLevel::SwitchScene(QString name)
{
    if (_game_manager->SwitchScene(name))
        Stop();
}

/*!
 * \brief GameLevel::SwitchOnNext
 * Switches current scene on the next scene in the queue
 */
void GameLevel::SwitchOnNext()
{
    if (next_card == "none")
        return;
    SwitchScene(next_card);
}

/*!
 * \brief GameLevel::SwitchOnPrev
 * Switches current scene on the previous scene in the queue
 */
void GameLevel::SwitchOnPrev()
{
    if (prev_card == "none")
        return;
    SwitchScene(prev_card);
}

void GameLevel::GameOver()
{
    _main_timer->stop();
    _keys_timer->stop();
    _obj_manager->DisconnectPlayerFromEnemy();

    _obj_setter->RestartAfterGameOver();
    _game_manager->GameOver();

    _key_controller->SetKeysStatus();
    _obj_manager->ConnectPlayerToEnemy();
    _main_timer->start();
    _keys_timer->start();
}

void GameLevel::SetCard()
{
    file::FileManager file(_data_link + "/main.txt");
    next_card = file.GetStringValue(file::NextCard);
    prev_card = file.GetStringValue(file::FileKeys::PrevCard);
}

void GameLevel::SetTimer()
{
    _main_timer = new QTimer(this);
    _main_timer->setInterval(1);
    _keys_timer = new QTimer(this);
    _keys_timer->setInterval(20);
    connect(_main_timer, SIGNAL(timeout()), this, SLOT(Update()));
    connect(_keys_timer, &QTimer::timeout, [&](){
        if (isActive())
            _obj_manager->CheckKeysStatus(_key_controller->GetKeysStatus());
    });
}

/*!
 * \brief GameLevel::UpdateWithDeveloperMode
 * Updates the current scene, when developer mode is active
 */
void GameLevel::UpdateWithDeveloperMode()
{
    this->clear();
    _obj_setter->deleteLater();
    _obj_manager->deleteLater();
    _game_manager->LoadPlayer();
    _obj_setter = new GameObjectSetter(this, _game_manager->GetPlayer(), _data_link);
    _obj_manager = new GameObjectManager(this, _obj_setter);
    _obj_setter->SetPlayer();
}

void GameLevel::keyPressEvent(QKeyEvent *event)
{
    _key_controller->KeyPressEvent(event);
}

void GameLevel::keyReleaseEvent(QKeyEvent *event)
{
    _key_controller->KeyReleaseEvent(event);
}

void GameLevel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qreal x = event->scenePos().x();
    qreal y = event->scenePos().y();
    _obj_manager->PlayerShoot(x, y);
}

/*!
 * \brief GameLevel::Update
 * Updates the scene
 */
void GameLevel::Update()
{
    if (isDeveloperMode)
        UpdateWithDeveloperMode();
    else if (isActive() && _obj_manager != nullptr)
    {
        _obj_manager->Update();
    }
}

void GameLevel::DrawNewArrow(arrow::Arrow *arrow)
{
    addItem(arrow);
}

