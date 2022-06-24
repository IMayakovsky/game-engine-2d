#include "level_manager.h"

#include <QTimer>
#include <QVector>

#include <gameLevel/game_level.h>
#include "ui/panel.h"
#include "enums/audio_names_enum.h"
#include "task_manager.h"

#include <ui/main_menu.h>

/*!
 * \brief LevelManager::LevelManager
 * Constructor
 * \param main_window the Main Window of the app
 */
LevelManager::LevelManager(MainWindow *main_window)
{
    this->main_window = main_window;
}

/*!
 * \brief LevelManager::Start
 * Starts a game
 */
void LevelManager::Start()
{
    audio_manager = new audioManager::AudioManager();
    LoadMainMenu();
}

void LevelManager::AddPanel(Panel *panel)
{
    main_window->setScene(panel);
    _scenes.push_back(panel);
}

void LevelManager::RemovePanel()
{
    if (_scenes.size() > 1)
    {
        main_window->setScene(_scenes[_scenes.size() - 2]);
        _scenes[_scenes.size() - 1]->deleteLater();
        _scenes.remove(_scenes.size() - 1);
    }
}

/*!
 * \brief LevelManager::LeaveMainMenu
 * Removes Main menu from the scenes container
 */
void LevelManager::LeaveMainMenu()
{
    _scenes[0]->deleteLater();
    _scenes.clear();
}

/*!
 * \brief LevelManager::LoadGameLevel
 * Loads Game Level with \param level_name name
 */
void LevelManager::LoadGameLevel(QString level_name)
{
    LeaveMainMenu();
    TaskManager::GetInstance().GetGameManager()->LoadGame(level_name);
    audio_manager->SetMedia(audioManager::AudioNames::GameLevel);
    audio_manager->Start();

}

/*!
 * \brief LevelManager::LoadMainMenu
 * Loads Main Menu to scenes container
 */
void LevelManager::LoadMainMenu()
{
    RemoveAllScenes();
    audio_manager->SetMedia(audioManager::AudioNames::MainMenu);
    audio_manager->Start();
    TaskManager::GetInstance().GetGameManager()->ClearAll();
    Panel *p = (Panel*) new MainMenu();
    main_window->setScene(p);
    _scenes.push_back(p);
}

/*!
 * \brief LevelManager::RemoveAllScenes
 * Removes all scenes from scenes container
 */
void LevelManager::RemoveAllScenes()
{
    _scenes.clear();
}

/*!
 * \brief LevelManager::SwitchGameScene
 * Sets \param scene like the active scene
 */
void LevelManager::SwitchGameScene(QGraphicsScene *scene)
{
    _scenes.clear();
    _scenes.push_back(scene);
    main_window->setScene(scene);
}



