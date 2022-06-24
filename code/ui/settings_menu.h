#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include "panel.h"

#include <QCheckBox>
#include <QComboBox>

#include "main_window.h"
#include "saves_manager.h"

class MainMenu;

namespace settingMenu {

class SettingsMenu : public Panel
{
    Q_OBJECT

public:
    SettingsMenu(QString path, MainMenu*, QWidget *parent = nullptr);
    void OnClick(QPushButton*, QString toPanel = "") override;

private:
    savesManager::SavesManager *saves_manager;
    void SwitchButtonStatus(QPushButton *but);
    void SetResolutionBox();
    void Update() override;
    MainWindow *window;
    MainMenu *_main_menu;
    QComboBox *_box;
    QCheckBox *_check_box;
    QString CONTROLS_PANEL_LINK = "menu/controlsMenuPanel/";
    void SetButtonsText();
    void SetButtonText(QPushButton*);

public slots:
    void CheckFullScreenStatus(bool);
    void ResolutionChange(QString resolution);

};

}

#endif // SETTINGS_MENU_H
