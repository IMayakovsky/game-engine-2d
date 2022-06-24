#include "game_levels_manager.h"

#include <QDir>
#include <QDirIterator>

#include "task_manager.h"
#include "utils/level_name_converter.h"
#include "gameLevel/game_level.h"
#include "level_manager.h"
#include "ui/panel.h"

/*!
 * \brief GameLevelsManager::GameLevelsManager
 * Constructor
 * \param saves_manager
 */
GameLevelsManager::GameLevelsManager(savesManager::SavesManager *saves_manager, LevelManager *level_manager)
{
    _saves_manager = saves_manager;
    _level_manager = level_manager;
}

/*!
 * \brief GameLevelsManager::ClearAll
 * Removes all game levels scenes
 */
void GameLevelsManager::ClearAll()
{
     ClearGameLevels();
    _player = nullptr;
    current_level = 0;
    current_scene = 0;
}

/*!
 * \brief GameLevelsManager::LoadGameLevels
 * Loads all game levels from the level with
 * \param level_name
 * \return  true if loading was success, false otherwise
 */
bool GameLevelsManager::LoadGameLevels(QString level_name)
{
    bool isLevel = false;

    LevelNameConverter converter(level_name);

    QString link = "../src/GameLevels/Level_";
    QString scene_name = "gameLevel_" + converter.GetStringLevel() + "_";

    if (converter.LevelExists())
    {
        if (_gameLevels.size() != 0 && converter.GetIntLevel() <= current_level)
        {
            return false;
        }
        link += converter.GetStringLevel();
        QDirIterator it(link, QDir::NoDotAndDotDot | QDir::Dirs);
        while (it.hasNext())
        {
            it.next();
            if (it.fileName().toInt() < converter.GetIntScene())
                continue;
            if (!isLevel)
            {
                isLevel = true;
                ClearGameLevels();
            }
            _gameLevels.insert(scene_name + it.fileName(), new GameLevel(it.filePath(), this));
        }
    }

    if (isLevel)
    {
        current_level = converter.GetIntLevel();
        current_scene = 0;
        SwitchScene(level_name);
        return true;
    }
    else if (_gameLevels.size() == 0)
    {
        delete _player;
        _player = nullptr;
    }
    return false;
}

void GameLevelsManager::ClearGameLevels()
{
    for (GameLevel *game_level : _gameLevels)
       game_level->deleteLater();
   _gameLevels.clear();
}

/*!
 * \brief GameLevelsManager::SwitchScene
 * Switches the current active scene on the scene
 * with a name \param name
 * \return true if switch was success, false otherwise
 */
bool GameLevelsManager::SwitchScene(QString name)
{
    if (name == "mainMenu")
    {
        _level_manager->LoadMainMenu();
        return false;
    }

    if (!_gameLevels.contains(name))
    {
        return LoadGameLevels(name);
    }

    int new_scene = LevelNameConverter(name).GetIntScene();
    bool is_next_level = current_scene < new_scene;

    if (is_next_level)
    {
        _player->CheckRepresentation(true);
        _saves_manager->UpdateMainSaves(savesManager::MainSaves::LevelName, name);
        _saves_manager->UpdateMainSaves(savesManager::MainSaves::Health,
                                        QString::number(_player->GetHealth()));
        _saves_manager->UpdateMainSaves(savesManager::MainSaves::ArrowsCount,
                                        QString::number(_player->GetArrowsAmount()));
        _saves_manager->SaveMainSaves();
    }
    else
        _player->CheckRepresentation(false);

    current_scene = new_scene;

    _level_manager->SwitchGameScene(_gameLevels[name]);

    if (is_next_level)
    {
        QString story_panel_link = STORY_PANEL_LINK + QString::number(current_level)
                + "/" +  QString::number(current_scene) + "/";
        if (IsStoryPanel(story_panel_link))
        {
            _level_manager->AddPanel(
                        new Panel(story_panel_link));
        }
    }
    _gameLevels[name]->Start();
    return true;
}

/*!
 * \brief GameLevelsManager::LoadGame
 * Loads the game with a \param level_name name
 */
void GameLevelsManager::LoadGame(QString level_name)
{
    LoadPlayer();
    LoadGameLevels(level_name);
}

void GameLevelsManager::LoadPlayer()
{
    _player = new player::Player("../src/assets/player");
    SetInitialPlayer();
}

void GameLevelsManager::GameOver()
{
    TaskManager::GetInstance().GetLevelManager()->AddPanel(new Panel(GAMEOVER_PANEL_LINK));
    SetInitialPlayer();
}

player::Player *GameLevelsManager::GetPlayer()
{
    return _player;
}

bool GameLevelsManager::GetDeveloperModeStatus()
{
    return TaskManager::GetInstance().GetDeveloperModeStatus();
}

bool GameLevelsManager::IsStoryPanel(QString link)
{
    bool status;
    link = "../src/panels/" + link;
    _saves_manager->LoadOptionsSaveValue(savesManager::OptionsSaves::StoryMode, &status);
    if (!status)
        return false;
    QDirIterator it(link, QDir::NoDotAndDotDot | QDir::Files);
    if (!it.hasNext())
        return false;
    return true;
}

void GameLevelsManager::SetInitialPlayer()
{
    QString health = _saves_manager->GetMainSaveValue(savesManager::MainSaves::Health);
    int arrow_count = _saves_manager->GetMainSaveValue(savesManager::MainSaves::ArrowsCount).toInt();
    _player->SetHealth(health.toInt());
    _player->SetArrowsAmount(arrow_count);
}
