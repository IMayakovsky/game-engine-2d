#ifndef SETTINGS_ENUM_H
#define SETTINGS_ENUM_H

#include <QStringList>

namespace settingMenu {

    enum class SettingKeys
    {
        Resolusion,
    };

    QStringList GetResolutionList();

}

#endif // SETTINGS_ENUM_H
