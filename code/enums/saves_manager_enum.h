#ifndef SAVES_MANAGER_ENUM_H
#define SAVES_MANAGER_ENUM_H

#include <QString>

namespace savesManager
{
    enum class MainSaves
    {
        ArrowsCount,
        Health,
        LevelName
    };

    QString GetMainSavesStringKey(MainSaves);

    enum class OptionsSaves
    {
        StoryMode,
        GodMode,
        MusicMode,
        Sounds,
        Resolution,
        FullScreen
    };

    QList<OptionsSaves> GetOptionsKeys();
}

#endif // SAVES_MANAGER_ENUM_H
