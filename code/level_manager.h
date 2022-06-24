#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "main_window.h"
#include "audio_manager.h"

class GameLevel;
class Panel;

class LevelManager
{

public:
    LevelManager(MainWindow *main_window);
    void RemoveAllGameLevels();
    void AddPanel(Panel *panel);
    void RemovePanel();
    void LeaveMainMenu();
    void LoadGameLevel(QString level_name = "gameLevel_1_1");
    void LoadMainMenu();
    void RemoveAllScenes();
    void SwitchGameScene(QGraphicsScene *);
    void Start();

private:
    QVector<QGraphicsScene *> _scenes;
    MainWindow *main_window;
    audioManager::AudioManager *audio_manager;

};

#endif // LEVEL_MANAGER_H
