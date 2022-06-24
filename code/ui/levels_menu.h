#ifndef LEVEL_MENU_H
#define LEVEL_MENU_H

#include "panel.h"
#include "saves_manager.h"
#include "game_levels_manager.h"

class LevelsMenu : public Panel
{
public:
    LevelsMenu();

private:
    savesManager::SavesManager *_saves_manager;
    void SetLevels();
};


#endif // LEVEL_MENU_H
