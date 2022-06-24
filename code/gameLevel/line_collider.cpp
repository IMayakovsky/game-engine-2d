#include "line_collider.h"

namespace lineCollider {

/*!
 * \brief LineCollider::LineCollider
 * Constructor
 * \param line QLineF Object
 * \param type type of the collider
 */
LineCollider::LineCollider(QLineF line, CollidersTypes type)
    : QGraphicsLineItem (line)
{
    _line = line;
    setPos(_line.p1());
    this->setLine(0, 0, _line.p2().x() - _line.p1().x(),
                  _line.p2().y() - _line.p1().y());
    _type = type;
}

qreal LineCollider::GetWidth()
{
    return this->boundingRect().height();
}

CollidersTypes LineCollider::GetType()
{
    return _type;
}

QLineF LineCollider::GetLine()
{
    return _line;
}

}
