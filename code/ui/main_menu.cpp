#include "main_menu.h"

#include <QCheckBox>
#include <task_manager.h>
#include "enums/buttons_names_enum.h"
#include "settings_menu.h"
#include "levels_menu.h"

/*!
 * \brief MainMenu::MainMenu
 * Constructor
 */
MainMenu::MainMenu() : Panel("menu/mainMenuPanel/")
{
    AddDeveloperModeBox();
    saves_manager = TaskManager::GetInstance().GetSavesManager();
}

void MainMenu::AddDeveloperModeBox()
{
    QCheckBox *dev_mod = new QCheckBox("Developer mode");
    TaskManager task = TaskManager::GetInstance();
    int x = 95*task.GetMainWindow()->width()/100 - dev_mod->sizeHint().width();
    int y = 90*task.GetMainWindow()->height()/100;
    dev_mod->move(x, y);
    dev_mod->setChecked(task.GetDeveloperModeStatus());
    addWidget(dev_mod);
    connect(dev_mod, SIGNAL(clicked(bool)), this, SLOT(ChangeDeveloperMode(bool)));
}

void MainMenu::ChangeDeveloperMode(bool status)
{
    TaskManager::GetInstance().SetDeveloperModeStatus(status);
}

void MainMenu::Update()
{
    Panel::Update();
    AddDeveloperModeBox();
}

void MainMenu::OnClick(QPushButton *but, QString switchTo)
{
    using namespace buttons;

    ButtonsNames name = GetName(but->objectName());

    switch (name)
    {
        case ButtonsNames::ContinueGame:
            _levelManager->LoadGameLevel(saves_manager->GetMainSaveValue(savesManager::MainSaves::LevelName));
            break;
        case ButtonsNames::ToSettingsMenu:
            _levelManager->AddPanel(new settingMenu::SettingsMenu("menu/settingsMenuPanel/", this));
            break;
        case ButtonsNames::ToLevelsMenu:
            _levelManager->AddPanel(new LevelsMenu());
            break;
        case ButtonsNames::StartNewGame:
            saves_manager->SetInitialMainSaves();
            _levelManager->LoadGameLevel();
            return;
        case ButtonsNames::DeleteSaves:
            saves_manager->SetInitialMainSaves();
            saves_manager->SaveMainSaves();
            return;
        case ButtonsNames::Exit:
            QApplication::exit();
            break;
        default:
            break;
    }
    Panel::OnClick(but, switchTo);
}
