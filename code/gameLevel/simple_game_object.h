#ifndef SIMPLE_GAME_OBJECT_H
#define SIMPLE_GAME_OBJECT_H

#include <QGraphicsPixmapItem>

#include "utils/file_manager.h"

class SimpleGameObject : public QGraphicsPixmapItem
{

public:
    SimpleGameObject(file::FileManager);
    SimpleGameObject(){};
    void SetSize(float, float);
    qreal GetWidth() const;
    qreal GetHeight() const;
    bool visible = true;
    bool right_representation = true;

protected:
   qreal _width;
   qreal _height;

   void SetPixmap(QString, float, float);
   void SetPixmap(QString);
};

#endif // SIMPLE_GAME_OBJECT_H
