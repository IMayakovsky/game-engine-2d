#ifndef GAME_LEVELS_MANAGER_H
#define GAME_LEVELS_MANAGER_H

#include "gameLevel/player.h"
#include "saves_manager.h"

class GameLevel;
class LevelManager;

class GameLevelsManager
{
public:
    GameLevelsManager(savesManager::SavesManager *saves_manager, LevelManager *level_manager);
    void ClearAll();
    void LoadGame(QString level_name);
    void LoadPlayer();
    bool SwitchScene(QString name);
    void GameOver();
    player::Player* GetPlayer();
    bool GetDeveloperModeStatus();

private:
    bool LoadGameLevels(QString level_name);
    int current_level = 0;
    int current_scene = 0;
    QMap<QString, GameLevel*> _gameLevels;
    savesManager::SavesManager * _saves_manager;
    LevelManager *_level_manager;
    player::Player* _player = nullptr;
    const QString GAMEOVER_PANEL_LINK = "gameOverPanel/";
    void ClearGameLevels();
    const QString STORY_PANEL_LINK = "gameLevels/";
    bool IsStoryPanel(QString link);
    void SetInitialPlayer();

};

#endif // GAME_LEVELS_MANAGER_H
