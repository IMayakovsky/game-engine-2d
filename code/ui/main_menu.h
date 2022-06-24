#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "panel.h"

#include <QCheckBox>

#include "saves_manager.h"

class MainMenu : Panel
{
    Q_OBJECT

public:
    MainMenu();
    void Update() override;

private:
    void AddDeveloperModeBox();
    void OnClick(QPushButton*, QString toPanel = "") override;
    savesManager::SavesManager *saves_manager;

private slots:
    void ChangeDeveloperMode(bool);

};

#endif // MAIN_MENU_H
