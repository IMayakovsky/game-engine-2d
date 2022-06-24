#include "file_keys_enum.h"

namespace file {

QString GetStringKey(FileKeys key)
{
    switch (key)
    {
    case Name:
        return "name";
    case Text:
        return "text";
    case Width:
        return "width";
    case Height:
        return "height";
    case SwitchTo:
        return "switchTo";
    case Image:
        return "image";
    case Health:
        return "health";
    case ZValue:
        return "zValue";
    case X:
        return "x";
    case Y:
        return "y";
    case BackgroundImage:
        return "backgroundImage";
    case MainLink:
        return "mainLink";
    case Collider:
        return "collider_";
    case Type:
        return "type";
    case Function:
        return "function";
    case NextCard:
        return "nextCard";
    case PrevCard:
        return "prevCard";
    default:
        return "none";
    }
}

}
