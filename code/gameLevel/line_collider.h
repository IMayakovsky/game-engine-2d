#ifndef LINE_COLLIDER_H
#define LINE_COLLIDER_H

#include <QGraphicsLineItem>

#include "enums/colliders_types_enum.h"

namespace lineCollider {

class LineCollider : public QGraphicsLineItem
{

public:
    LineCollider(QLineF line, CollidersTypes);
    qreal GetWidth();
    CollidersTypes GetType();
    QLineF GetLine();

private:
    CollidersTypes _type;
    QLineF _line;

};

}

#endif // LINE_COLLIDER_H
