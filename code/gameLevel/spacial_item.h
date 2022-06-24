#ifndef SPACIAL_ITEMS_H
#define SPACIAL_ITEMS_H

#include "simple_game_object.h"
#include "enums/spacial_item_enum.h"
#include "utils/file_manager.h"

namespace spacialItem
{

    class SpacialItem : public SimpleGameObject
    {

    public:
        SpacialItem(file::FileManager);
        spacialItem::Types GetType();

    protected:
        spacialItem::Types type;

    };

}



#endif // SPACIAL_ITEMS_H
