#include "arrow.h"

#include <QTimer>
#include <QtMath>

#include "enums/file_keys_enum.h"
#include "task_manager.h"

namespace arrow {

static const qreal SPEED = 8;

Arrow::Arrow(file::FileManager file, qreal start_x, qreal start_y,
             qreal target_x, qreal target_y)
    : SimpleGameObject()
{
    using namespace file;

    setPixmap(QPixmap("../" + file.GetStringValue(FileKeys::Image)));

    SetSize(file.GetByWidthRatio(FileKeys::Width),
                              file.GetByHeightRatio(FileKeys::Height));
    setPos(start_x, start_y);

    this->target_x = target_x;
    this->target_y = target_y;

    SetTrajectory();
    SetTimer();
    setZValue(100);
}

Arrow::~Arrow()
{
    _timer->deleteLater();
}

/*!
 * \brief Arrow::Stop
 * Hides arrow visibility
 */
void Arrow::Stop()
{
    visible = false;
}

void Arrow::SetTrajectory()
{
    qreal sin = (target_y - pos().y() ) /
                    sqrt(pow(target_x - pos().x(), 2) + pow(target_y - pos().y(), 2));

    int x_orienation = (target_x >= pos().x()) ? 1 : -1;
    int y_orienation = (target_y >= pos().y()) ? 1 : -1;

    if (x_orienation == -1)
        setTransform(QTransform::fromScale(-1, 1));

    qreal rotationAngle = qSin(sin);
    setTransform(transform().rotateRadians(rotationAngle));
    setRotation(sin);

    int x_dist = abs(target_x - pos().x());
    int y_dist = abs(target_y - pos().y());

    if (x_dist > y_dist)
    {
        speed_x = SPEED;
        speed_y = y_dist / (x_dist / speed_x);
    }
    else
    {
        speed_y = SPEED;
        speed_x = x_dist / (y_dist / speed_y);
    }
    speed_x *= x_orienation;
    speed_y *= y_orienation;
}

void Arrow::SetTimer()
{
    _timer = new QTimer();
    _timer->setInterval(7);
    connect(_timer, &QTimer::timeout, this, &Arrow::Update);
    _timer->start();
}

void Arrow::CheckVisibility()
{
    MainWindow *win = TaskManager::GetInstance().GetMainWindow();
    if (pos().x() > win->width() || pos().x() < win->x()
            || pos().y() > win->height() || pos().y() < win->y())
    {
        visible = false;
    }
}

int Arrow::GetDemage() const
{
    return demage;
}

void Arrow::Update()
{
    moveBy(speed_x, speed_y);
    CheckVisibility();
}

}
