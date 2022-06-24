#include "levels_menu.h"

#include "task_manager.h"
#include "utils/level_name_converter.h"
#include "enums/file_keys_enum.h"
#include "utils/file_manager.h"
#include "enums/buttons_names_enum.h"

/*!
 * \brief LevelsMenu::LevelsMenu
 * Constructor
 */
LevelsMenu::LevelsMenu() : Panel("menu/levelsMenuPanel/")
{
    _saves_manager = TaskManager::GetInstance().GetSavesManager();
    SetLevels();
}

void LevelsMenu::SetLevels()
{
    QString current_level_name = _saves_manager->GetMainSaveValue(savesManager::MainSaves::LevelName);
    LevelNameConverter converter(current_level_name);
    int current_level = converter.GetIntLevel();
    file::FileManager file(_main_path + "exampleLevelButton.txt");
    for (int i = 1; i <= current_level; i++)
    {
        using namespace buttons;

        QPushButton *but = new QPushButton("Level " + QString::number(i));
        but->setObjectName("Level " + QString::number(i));
        but->setFixedSize(file.GetByWidthRatio(file::FileKeys::Width),
                          file.GetByHeightRatio(file::FileKeys::Height));
        qreal y = (i-1)*(file.GetByHeightRatio("buttonsDistance")) +
                         file.GetByHeightRatio(file::FileKeys::Y);
        but->move(file.GetByWidthRatio(file::FileKeys::X), y);
        but->setStyleSheet("background-color: #2B2B2B; color: white");
        but->setFont(file.GetFont());

        QString to_level = "gameLevel_" + QString::number(i) + "_1";
        connect(but, &QPushButton::clicked, this, [=](){ _levelManager->LoadGameLevel(to_level); });
        addWidget(but);
    }
}

