#ifndef BUTTONS_NAMES_ENUM_H
#define BUTTONS_NAMES_ENUM_H

#include <QString>

namespace buttons
{
    enum class ButtonsNames
    {
        SwitchPanel,
        StartNewGame,
        ContinueGame,
        ToBack,
        ToMainMenu,
        ToSettingsMenu,
        ToLevelsMenu,
        ToControlsMenu,
        Exit,
        DeleteSaves,
        StoryMode,
        MusicMode,
        GodMode,
        Nothing
    };

    ButtonsNames GetName(QString name);
}

#endif // BUTTONS_NAMES_ENUM_H
