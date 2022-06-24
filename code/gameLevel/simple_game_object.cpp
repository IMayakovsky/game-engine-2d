#include "simple_game_object.h"
#include "enums/file_keys_enum.h"

/*!
 * \brief SimpleGameObject::SimpleGameObject
 * Constructor
 * \param file file with the object's data
 */
SimpleGameObject::SimpleGameObject(file::FileManager file) : QGraphicsPixmapItem()
{
    using namespace file;
    setPos(file.GetByWidthRatio(FileKeys::X), file.GetByHeightRatio(FileKeys::Y));
    setPixmap("../" + file.GetStringValue(FileKeys::Image));
    SetSize(file.GetByWidthRatio(FileKeys::Width), file.GetByHeightRatio(FileKeys::Height));
    setZValue(file.GetRealValue(FileKeys::ZValue));

}

void SimpleGameObject::SetSize(float x, float y)
{
    _width = x;
    _height = y;
    setPixmap(pixmap().scaled(x, y));
}

qreal SimpleGameObject::GetWidth() const
{
    return _width;
}

qreal SimpleGameObject::GetHeight() const
{
    return _height;
}

/*!
 * \brief SimpleGameObject::SetPixmap
 * Sets pixmap with link \param link
 * \param x scaled x
 * \param y scaled y
 */
void SimpleGameObject::SetPixmap(QString link, float x, float y)
{
    setPixmap(QPixmap(link).scaled(x, y));
}

/*!
 * \brief SimpleGameObject::SetPixmap
 * Sets pixmap with link
 * \param link
 * and width heaight scaled
 */
void SimpleGameObject::SetPixmap(QString link)
{
    setPixmap(QPixmap(link).scaled(_width, _height));
}

