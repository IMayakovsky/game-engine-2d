#ifndef SAVES_MANAGER_H
#define SAVES_MANAGER_H

#include <QMap>
#include <QObject>
#include <QString>

class FileManager;

#include "enums/saves_manager_enum.h"

namespace savesManager
{

class SavesManager : public QObject
{
    Q_OBJECT

public:
    void LoadSaves();
    bool UpdateOptionsSaves(OptionsSaves, QString value);
    bool UpdateOptionsSaves(OptionsSaves, bool value_status);
    bool UpdateMainSaves(savesManager::MainSaves, QString value);

    void SetInitialMainSaves();
    void LoadOptionsSaveValue(OptionsSaves key, bool *status);
    QString GetOptionsSaveValue(OptionsSaves key);
    QString GetMainSaveValue(savesManager::MainSaves);

    void SaveOptionsSaves();
    void SaveMainSaves();

signals:
    void OptionsWasChanged();

private:
    QMap<OptionsSaves, QString> _options;
    QMap<MainSaves, QString> _saves;
    const QString _OPTIONS_LINK = "../saves/options";
    const QString _MAIN_SAVES_LINK = "../saves/saves.txt";

    void SetInitialOptionsSaves();
    void LoadOptionsSaves();
    void LoadMainSaves();

};

}



#endif // SAVES_MANAGER_H
