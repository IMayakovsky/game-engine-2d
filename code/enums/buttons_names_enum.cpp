#include "buttons_names_enum.h"

namespace buttons
{
    ButtonsNames GetName(QString name)
    {
        if (name == "SwitchPanel")
            return ButtonsNames::SwitchPanel;
        else if (name == "ToBack")
            return ButtonsNames::ToBack;
        else if (name == "Exit")
            return ButtonsNames::Exit;
        else if (name == "ContinueGame")
            return ButtonsNames::ContinueGame;
        else if (name == "StartNewGame")
            return ButtonsNames::StartNewGame;
        else if (name == "ToMainMenu")
            return ButtonsNames::ToMainMenu;
        else if (name == "StoryMode")
            return ButtonsNames::StoryMode;
        else if (name == "MusicMode")
            return ButtonsNames::MusicMode;
        else if (name == "GodMode")
            return ButtonsNames::GodMode;
        else if (name == "ToSettingsMenu")
            return ButtonsNames::ToSettingsMenu;
        else if (name == "DeleteSaves")
            return ButtonsNames::DeleteSaves;
        else if (name == "ToLevelsMenu")
            return ButtonsNames::ToLevelsMenu;
        else if (name == "ToControlsMenu") {
            return ButtonsNames::ToControlsMenu;
        }
        else
            return ButtonsNames::Nothing;
    }
}

