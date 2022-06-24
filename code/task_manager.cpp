#include "task_manager.h"

#include <ui/main_menu.h>

TaskManager::TaskManager()
{
    _saves_manager = new savesManager::SavesManager;
    _main_window = new MainWindow(_saves_manager);
    _level_manager = new LevelManager(_main_window);
    _game_manager = new GameLevelsManager(_saves_manager, _level_manager);
}

bool TaskManager::GetDeveloperModeStatus()
{
    return isDeveloperMode;
}

void TaskManager::SetDeveloperModeStatus(bool value)
{
    isDeveloperMode = value;
}

void TaskManager::StartGame()
{
    _saves_manager->LoadSaves();
    _main_window->ShowWindow();
    _level_manager->Start();
}

MainWindow *TaskManager::GetMainWindow() {return _main_window;}

LevelManager *TaskManager::GetLevelManager() {return _level_manager;}

GameLevelsManager *TaskManager::GetGameManager() {return _game_manager;}

savesManager::SavesManager *TaskManager::GetSavesManager()
{
    return _saves_manager;
}


