#include "saves_manager_enum.h"

#include <QList>

namespace savesManager {

QString GetMainSavesStringKey(MainSaves key)
{
    if (key == MainSaves::Health)
        return "health";
    else if (key == MainSaves::ArrowsCount)
        return "arrowsCount";
    else
        return "levelName";
}

QList<OptionsSaves> GetOptionsKeys()
{
    QList<OptionsSaves> keys = {OptionsSaves::StoryMode, OptionsSaves::GodMode,
                                OptionsSaves::MusicMode, OptionsSaves::Resolution,
                                OptionsSaves::FullScreen};
    return keys;
}

}
