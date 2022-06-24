#ifndef ARROW_H
#define ARROW_H

#include "simple_game_object.h"

namespace arrow {

class Arrow : public QObject, public SimpleGameObject
{
    Q_OBJECT

public:
    Arrow(file::FileManager, qreal, qreal, qreal, qreal);
    ~Arrow();
    void Stop();
    int GetDemage() const;

private:
    void SetTrajectory();
    void SetTimer();
    void CheckVisibility();

    QTimer *_timer;
    int demage = 20;
    qreal target_x;
    qreal target_y;
    qreal speed_x;
    qreal speed_y;

private slots:
    void Update();
};

}

#endif // ARROW_H
