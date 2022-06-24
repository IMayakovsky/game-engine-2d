#include "settings_menu.h"

#include <QTimer>
#include <QLineEdit>

#include "main_menu.h"
#include "task_manager.h"
#include "enums/buttons_names_enum.h"
#include "panel.h"

namespace settingMenu {

/*!
 * \brief SettingsMenu::SettingsMenu
 * Constructor
 * \param path resource link
 * \param main_menu
 * \param parent
 */
SettingsMenu::SettingsMenu(QString path, MainMenu *main_menu, QWidget *parent) : Panel(path, parent)
{
    saves_manager = TaskManager::GetInstance().GetSavesManager();
    _main_menu = main_menu;
    SetResolutionBox();
    SetButtonsText();
}

/*!
 * \brief SettingsMenu::SwitchButtonStatus
 * Switches of the \param but status
 * \param but the button
 */
void SettingsMenu::SwitchButtonStatus(QPushButton *but)
{
    if (but->text().compare("on") == 0)
    {
        but->setText("off");
    }
    else
    {
        but->setText("on");
    }
}

/*!
 * \brief SettingsMenu::SetResolutionBox
 * Sets a box with resolutions settings
 */
void SettingsMenu::SetResolutionBox()
{
    window = TaskManager::GetInstance().GetMainWindow();
    file::FileManager file(_main_path + "resolutions.txt");

    _check_box = new QCheckBox("Full Screen");
    _check_box->move(file.GetByWidthRatio("full_screen_x"), file.GetByHeightRatio("full_screen_y"));
    _check_box->setChecked(window->IsFullScreen());
    connect(_check_box, &QCheckBox::clicked, this, &SettingsMenu::CheckFullScreenStatus);

    addWidget(_check_box);

    _box = new QComboBox();
    for (QString res : window->GetAllResolutions())
    {
        _box->addItem(res);
    }
    _box->setEditable(true);
    _box->lineEdit()->setReadOnly(true);

    _box->setCurrentText(window->GetCurrentResolution());

    connect(_box, &QComboBox::currentTextChanged, this, &SettingsMenu::ResolutionChange);

    _box->move(file.GetByWidthRatio("box_x"), file.GetByHeightRatio("box_y"));
    _box->setFixedSize(file.GetByWidthRatio("box_width"),
                               file.GetByHeightRatio("box_height"));
    _box->setStyleSheet("background-color: #2B2B2B; color: white");
    _box->lineEdit()->setAlignment(Qt::AlignCenter);

    addWidget(_box);

}

void SettingsMenu::Update()
{
    Panel::Update();
    SetResolutionBox();
    SetButtonsText();
}

void SettingsMenu::SetButtonsText()
{
    for (QPushButton *but : _buttons)
    {
        SetButtonText(but);
    }
}

/*!
 * \brief SettingsMenu::CheckFullScreenStatus
 * Checks window on the full screen mode
 * \param status true if full screen is, false otherwise
 */
void SettingsMenu::CheckFullScreenStatus(bool status)
{
    window->ChangeFullScreenMode(status);
    if (status)
        _box->setCurrentText(window->GetCurrentResolution());

    QTimer::singleShot(100, [&](){Update(); _main_menu->Update(); });
}

/*!
 * \brief SettingsMenu::ResolutionChange
 * Changes the screen resolution
 * \param resolution resolution of the screen
 */
void SettingsMenu::ResolutionChange(QString resolution)
{
    window->SetResolution(resolution);
    _check_box->setChecked(window->IsFullScreen());
    QTimer::singleShot(100, [&](){Update(); _main_menu->Update(); });
}

void SettingsMenu::SetButtonText(QPushButton* but)
{
    using namespace buttons;
    ButtonsNames name = GetName(but->objectName());

    switch (name)
    {
        case ButtonsNames::StoryMode:
            but->setText(saves_manager->GetOptionsSaveValue(savesManager::OptionsSaves::StoryMode));
            break;
        case ButtonsNames::MusicMode:
            but->setText(saves_manager->GetOptionsSaveValue(savesManager::OptionsSaves::MusicMode));
            break;
        case ButtonsNames::GodMode:
            but->setText(saves_manager->GetOptionsSaveValue(savesManager::OptionsSaves::GodMode));
            break;
        default:
            break;
    }
}

void SettingsMenu::OnClick(QPushButton* but, QString toPanel)
{
    using namespace buttons;

    ButtonsNames name = GetName(but->objectName());

    switch (name)
    {
        case ButtonsNames::StoryMode:
            SwitchButtonStatus(but);
            saves_manager->UpdateOptionsSaves(savesManager::OptionsSaves::StoryMode, but->text());
            break;
        case ButtonsNames::MusicMode:
            SwitchButtonStatus(but);
            saves_manager->UpdateOptionsSaves(savesManager::OptionsSaves::MusicMode, but->text());
            break;
        case ButtonsNames::GodMode:
            SwitchButtonStatus(but);
            saves_manager->UpdateOptionsSaves(savesManager::OptionsSaves::GodMode, but->text());
            break;
        case ButtonsNames::ToControlsMenu:
            _levelManager->AddPanel(new Panel(CONTROLS_PANEL_LINK));
            break;
        case ButtonsNames::ToBack:
            saves_manager->SaveOptionsSaves();
            break;
        default:
            break;
    }
    Panel::OnClick(but, toPanel);
}

}
