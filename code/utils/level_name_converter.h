#ifndef LEVEL_NAME_CONVERTER_H
#define LEVEL_NAME_CONVERTER_H

#include <QString>

class LevelNameConverter
{
    QString level;
    QString card;

public:
    LevelNameConverter(QString level_name);
    bool LevelExists();
    QString GetStringLevel() { return level; }
    QString GetStringCard() { return card; }
    int GetIntLevel() { return level.toInt(); }
    int GetIntScene() { return card.toInt(); }
};

#endif // LEVEL_NAME_CONVERTER_H
