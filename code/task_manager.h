#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "level_manager.h"
#include "main_window.h"
#include "game_levels_manager.h"
#include "saves_manager.h"

class TaskManager
{
    TaskManager();
    MainWindow *_main_window;
    LevelManager *_level_manager;
    GameLevelsManager *_game_manager;
    savesManager::SavesManager *_saves_manager;
    bool isDeveloperMode = false;

public:

    static TaskManager &GetInstance() {
       static TaskManager instance;
       return instance;
    }

    void StartGame();

    MainWindow* GetMainWindow();
    LevelManager* GetLevelManager();
    GameLevelsManager* GetGameManager();
    savesManager::SavesManager *GetSavesManager();
    bool GetDeveloperModeStatus();
    void SetDeveloperModeStatus(bool value);
};

#endif // TASK_MANAGER_H
