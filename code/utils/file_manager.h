#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include <QFile>
#include <QtDebug>
#include <QGraphicsItem>

#include "gameLevel/line_collider.h"
#include "enums/file_keys_enum.h"

class TaskManager;

namespace file {

class FileManager {

public:
    FileManager(QString _link);
    FileManager(){};
    bool SwitchOnNextData();
    QStringList GetDataList();
    QString GetStringValue(FileKeys key);
    QString GetStringValue(QString key);
    qreal GetRealValue(FileKeys key);
    qreal GetRealValue(QString key);
    float GetByWidthRatio(FileKeys key);
    float GetByHeightRatio(FileKeys key);
    float GetByWidthRatio(QString key);
    float GetByHeightRatio(QString key);
    QVector<lineCollider::LineCollider*> GetColliders();
    QFont GetFont();

private:
    QString _link;
    QStringList _dataList;
    QMap<QString, QString> _dataMap;
    QSize _window_size;
    int _reading_index = 0;
    void CreateDataList();
    bool IsRequestPossible(QString key);
    lineCollider::LineCollider* GetCollider(QString key);

};

}

#endif // FILE_MANAGER_H
