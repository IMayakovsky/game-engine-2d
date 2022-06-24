#ifndef FILE_KEYS_ENUM_H
#define FILE_KEYS_ENUM_H

#include <QString>

namespace file
{
    enum FileKeys
    {
        Name,
        Width,
        Height,
        Text,
        Collider,
        SwitchTo,
        Image,
        Health,
        BackgroundImage,
        MainLink,
        ZValue,
        Type,
        Function,
        X,
        Y,
        NextCard,
        PrevCard
    };

    QString GetStringKey(FileKeys key);
}



#endif // FILE_KEYS_ENUM_H
