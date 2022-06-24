#include "level_name_converter.h"

#include <QtDebug>
#include <QRegularExpression>

const static QRegularExpression MAIN_PATTERN("^gameLevel_(\\d++)_(\\d++)$");

/*!
 * \brief LevelNameConverter::LevelNameConverter
 * Constructor
 * \param level_name
 */
LevelNameConverter::LevelNameConverter(QString level_name)
{
    QRegularExpressionMatch match = MAIN_PATTERN.match(level_name);
    if (match.hasMatch())
    {
        level = match.captured(1);
        card = match.captured(2);
    }
}

/*!
 * \brief LevelNameConverter::LevelExists
 * \return true if level's name,
 * which has passed to the constroctor was correct,
 * false otherwise
 */
bool LevelNameConverter::LevelExists()
{
    try {
        level.toInt();
        card.toInt();
        return true;
    } catch (int) {
        qInfo() << "Level not exists";
        return false;
    }
}
