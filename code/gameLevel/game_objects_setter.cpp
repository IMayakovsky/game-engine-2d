#include "game_objects_setter.h"

#include <QLine>
#include <QColor>
#include <QGraphicsItem>

#include "player.h"
#include "arrow.h"
#include "enemy.h"
#include "game_level.h"
#include "enums/file_keys_enum.h"
#include "task_manager.h"
#include "utils/file_manager.h"

/*!
 * \brief GameObjectSetter::GameObjectSetter
 * Constructor
 * \param game_level appropriate GameLevel
 * \param player appropriate GameLevel
 * \param data_link
 */
GameObjectSetter::GameObjectSetter(GameLevel *game_level, player::Player *player, QString data_link)
{
    this->_data_link = data_link;
    _game_level = game_level;
    _player = player;
    MainWindow *window = TaskManager::GetInstance().GetMainWindow();
    _window_size.setWidth(window->width());
    _window_size.setHeight(window->height());
    SetBackground();
    SetEnemies();
    SetTerrainObjects();
    SetGround();
    SetCheckpoints();
    SetCollectedItems();
    SetCheckpointText();
    AddColliders();
}

GameObjectSetter::~GameObjectSetter()
{
    enemies.clear();
    grounds.clear();
    terrains_objects.clear();
    line_colliders.clear();
    collectedItems.clear();
    checkpoints.clear();
}

void GameObjectSetter::RestartAfterGameOver()
{
    for (enemy::Enemy *enemy : enemies)
    {
        _game_level->removeItem(enemy);
        enemy->deleteLater();
    }
    for (spacialItem::SpacialItem *item : collectedItems)
    {
        _game_level->removeItem(item);
        delete item;
    }
    enemies.clear();
    collectedItems.clear();
    SetCollectedItems();
    SetEnemies();
    _player->CheckRepresentation(true);
    SetPlayer();
}

void GameObjectSetter::SetGround()
{
    SetSimpleObjects(_data_link + "/ground.txt", &grounds,
                     _game_level->GetDeveloperModeStatus());
}

void GameObjectSetter::SetPlayer()
{

    _player->SetInitialLocationsOnScene(file::FileManager(_data_link + "/playerInfo.txt"));

    _player->SetSizeOnScene();

    _game_level->addItem(_player);

    _player->DrawCommonInfo(_game_level);

    if (_game_level->GetDeveloperModeStatus())
    {
        SetCollider(_player);
    }
    _player->isGround = false;
}

void GameObjectSetter::SetEnemies()
{
    using enemy::Enemy;
    file::FileManager file(_data_link + "/enemies.txt");
    while (file.SwitchOnNextData())
    {
        Enemy *enemy = new Enemy(file, _player);
        enemies.push_back(enemy);
        connect(enemy, &Enemy::NewArrowWasCreated, _game_level, &GameLevel::DrawNewArrow);
        _game_level->addItem((QGraphicsPixmapItem *)enemy);

        if (_game_level->GetDeveloperModeStatus())
        {
            SetCollider(enemy);
        }
    }
}

void GameObjectSetter::SetPlayerInfo()
{
    _player->SetInitialLocationsOnScene(file::FileManager(_data_link + "/playerInfo.txt"));
}

void GameObjectSetter::AddColliders()
{
    file::FileManager file(_data_link + "/lineColliders.txt");
    line_colliders.append(file.GetColliders());
    if (_game_level->GetDeveloperModeStatus())
    {
        for (lineCollider::LineCollider *coll : line_colliders)
        {
            coll->setZValue(1000);
             coll->setPen(QPen(Qt::green));
             _game_level->addItem(coll);
        }
    }
}

void GameObjectSetter::SetTerrainObjects()
{
    SetSimpleObjects(_data_link + "/terrainObjects.txt", &terrains_objects);
}

void GameObjectSetter::SetCollectedItems()
{
    using spacialItem::SpacialItem;
    file::FileManager file(_data_link + "/collectedItems.txt");
    while (file.SwitchOnNextData())
    {
        SpacialItem *item = new SpacialItem(file);
        if (item->GetType() == spacialItem::Types::None)
        {
            delete item;
            continue;
        }

        collectedItems.push_back(item);
        _game_level->addItem(item);

        if (_game_level->GetDeveloperModeStatus())
        {
            SetCollider(item);
        }
    }
}

void GameObjectSetter::SetCheckpoints()
{
    using spacialItem::Checkpoint;
    file::FileManager file(_data_link + "/checkpoints.txt");
    while (file.SwitchOnNextData())
    {
        Checkpoint *item = new Checkpoint(file);
        if (item->GetType() == spacialItem::Types::None)
        {
            delete item;
            continue;
        }
        checkpoints.push_back(item);
        _game_level->addItem(item);

        if (_game_level->GetDeveloperModeStatus())
        {
            SetCollider(item);
        }
    }
}

void GameObjectSetter::SetCheckpointText()
{
    checkpoint_text = new QGraphicsSimpleTextItem("Push E for Enter");
    checkpoint_text->setBrush(QBrush(Qt::white));
    checkpoint_text->setFont(QFont("Arial", 16));
    checkpoint_text->setPen(QPen(Qt::black));
    checkpoint_text->moveBy(95*_window_size.width()/100 - checkpoint_text->boundingRect().width(),
                            1 * _window_size.width()/100);
}


void GameObjectSetter::SetSimpleObjects(QString link, QVector<SimpleGameObject *> *vector, bool set_col)
{
    file::FileManager file(link);
    while (file.SwitchOnNextData())
    {
        SimpleGameObject *obj = new SimpleGameObject(file);
        vector->push_back(obj);
        _game_level->addItem(obj);
        if (set_col)
            SetCollider(obj);
    }
}

void GameObjectSetter::SetBackground()
{
    file::FileManager file(_data_link + "/main.txt");
    _background = new QPixmap("../" + file.GetStringValue(file::FileKeys::BackgroundImage));
    _game_level->addPixmap(_background->scaled(_window_size.width(), _window_size.height()));
}

void GameObjectSetter::SetCollider(SimpleGameObject *item)
{
    if (!item->right_representation)
        return;
    QPolygonF polygon = item->shape().toFillPolygon();
    polygon.translate(item->x(), item->y());
    _game_level->addPolygon(polygon, QPen(Qt::green));
}

player::Player* GameObjectSetter::GetPlayer()
{
    return _player;
}

QGraphicsSimpleTextItem  *GameObjectSetter::GetCheckpointText()
{
    return checkpoint_text;
}


