#include "spacial_item.h"

#include "enums/file_keys_enum.h"

namespace spacialItem
{

SpacialItem::SpacialItem(file::FileManager file) : SimpleGameObject(file)
{
    QString type_string = file.GetStringValue(file::FileKeys::Type);
    type = GetTypeFromString(type_string);
}

Types SpacialItem::GetType()
{
    return type;
}

}
