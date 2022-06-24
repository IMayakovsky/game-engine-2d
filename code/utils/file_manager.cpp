#include "file_manager.h"

#include <QRegularExpression>

#include "task_manager.h"
#include "enums/colliders_types_enum.h"

namespace file {

const static QRegularExpression MAIN_PATTERN("^_([\\w]*): (.*);$");

/*!
 * \brief FileManager::FileManager
 * Constructor
 * \param link file link
 */
FileManager::FileManager(QString link) {
    this->_link = link;
    MainWindow *window = TaskManager::GetInstance().GetMainWindow();
    _window_size.scale(window->width(), window->height(), Qt::IgnoreAspectRatio);
    CreateDataList();
    SwitchOnNextData();
}

/*!
 * \brief FileManager::SwitchOnNextData
 * Switches data on the next in the file
 * \return false if EOF, true otherwise
 */
bool FileManager::SwitchOnNextData()
{
    if (_reading_index >= _dataList.size()) {
        return false;
    }

    _dataMap.clear();

    for (int i = _reading_index; i < _dataList.size(); i++)
    {
        QRegularExpressionMatch match = MAIN_PATTERN.match(_dataList[i]);
        if(match.hasMatch())
        {
            _dataMap.insert(match.captured(1), match.captured(2));
        }
        else
        {
            _reading_index = i + 1;
            return true;
        }

    }
    return false;
}

/*!
 * \brief FileManager::GetDataList
 * \return all file data in the list format
 */
QStringList FileManager::GetDataList()
{
    return _dataList;
}

QString FileManager::GetStringValue(FileKeys key)
{
    QString str_key = GetStringKey(key);
    if (!IsRequestPossible(str_key))
        return "";
    return _dataMap[str_key];
}

QString FileManager::GetStringValue(QString key)
{
    if (!IsRequestPossible(key))
        return "";
    return _dataMap[key];
}

qreal FileManager::GetRealValue(FileKeys key)
{
    QString str_key = GetStringKey(key);
    if (IsRequestPossible(str_key))
    {
        bool isOk;
        qreal value = _dataMap[str_key].toFloat(&isOk);
        if (!isOk)
            qInfo() << "Value with key " << key << " is not number";

        return value;
    }

    return 0;
}

qreal FileManager::GetRealValue(QString key)
{
    if (IsRequestPossible(key))
    {
        bool isOk;
        qreal value = _dataMap[key].toFloat(&isOk);
        if (!isOk)
            qInfo() << "Value with key " << key << " is not number";

        return value;
    }

    return 0;
}

void FileManager::CreateDataList()
{
    QFile data_file(_link);
    if (!data_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qInfo() << "Impossible to open a file " << _link;
        return;
    }

    while (!data_file.atEnd()) {
         _dataList.push_back(data_file.readLine());
    }
    data_file.close();
}

bool FileManager::IsRequestPossible(QString key)
{
    return _dataMap.contains(key);
}

float FileManager::GetByWidthRatio(FileKeys key)
{
    return GetRealValue(GetStringKey(key)) * _window_size.width()/100;
}

float FileManager::GetByHeightRatio(FileKeys key)
{
    return GetRealValue(GetStringKey(key)) * _window_size.height()/100;
}

float FileManager::GetByWidthRatio(QString key)
{
    return GetRealValue(key) * _window_size.width()/100;
}

float FileManager::GetByHeightRatio(QString key)
{
    return GetRealValue(key) * _window_size.height()/100;
}

lineCollider::LineCollider* FileManager::GetCollider(QString key)
{

    using namespace lineCollider;

    if (!IsRequestPossible(key))
        return nullptr;

    const QRegularExpression COLLIDER_PATTERN("^(\\d*\\.?\\d+) (\\d*\\.?\\d+) (\\d*\\.?\\d+) (\\d*\\.?\\d+)$");

    QRegularExpressionMatch match = COLLIDER_PATTERN.match(GetStringValue(key));
    if(!match.hasMatch())
    {
        qInfo() << "Collider with key " << key << " is not collider";
        return nullptr;
    }

    CollidersTypes type = GetColliderType(GetStringValue(key + "_type"));

    int width = _window_size.width();
    int height = _window_size.height();
    QLineF line(match.captured(1).toFloat()*width/100, match.captured(2).toFloat()*height/100,
                match.captured(3).toFloat()*width/100, match.captured(4).toFloat()*height/100);

    return new LineCollider(line, type);

}

/*!
 * \brief FileManager::GetColliders
 * \return Vector of all colliders in the file
 */
QVector<lineCollider::LineCollider *> FileManager::GetColliders()
{
    using namespace lineCollider;
    QVector<LineCollider *> colliders;
    LineCollider *line_collider;
    for (int i = 1; ; i++)
    {
        QString coll_name = GetStringKey(FileKeys::Collider) + QString::number(i);
        if ((line_collider = GetCollider(coll_name)) != nullptr)
        {
            colliders.push_back(line_collider);
        }
        else
            break;
    }
    return colliders;
}

/*!
 * \brief FileManager::GetFont
 * \return Font with font family and font size from file
 */
QFont FileManager::GetFont()
{
    MainWindow *window = TaskManager::GetInstance().GetMainWindow();
    int font_size = ((int)(window->width() * GetRealValue("fontSize"))
                     / window->GetMaxWidth());
    if ((int)(window->width() * GetRealValue("fontSize")) % window->GetMaxWidth() != 0)
        font_size++;
    QFont font (GetStringValue("fontFamily"), font_size);

    return font;
}

}
