#include "saves_manager.h"

#include <utils/file_manager.h>

#include <QGuiApplication>
#include <QScreen>

namespace savesManager
{

/*!
 * \brief SavesManager::LoadSaves
 * Loads all saves from files
 */
void SavesManager::LoadSaves()
{
    LoadOptionsSaves();
    LoadMainSaves();
}

void SavesManager::SetInitialOptionsSaves()
{
    _options.clear();
    _options.insert(OptionsSaves::StoryMode, "on");
    _options.insert(OptionsSaves::GodMode, "off");
    _options.insert(OptionsSaves::MusicMode, "on");
    _options.insert(OptionsSaves::FullScreen, "off");
    _options.insert(OptionsSaves::Resolution, "-");
}

void SavesManager::SetInitialMainSaves()
{
    _saves.clear();
    _saves.insert(MainSaves::Health, "100");
    _saves.insert(MainSaves::ArrowsCount, "10");
    _saves.insert(MainSaves::LevelName, "gameLevel_1_1");
}

void SavesManager::LoadOptionsSaves()
{
    QFile file(_OPTIONS_LINK);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        SetInitialOptionsSaves();
        SaveOptionsSaves();
    }
    else
    {
        QDataStream in(&file);
        QList<OptionsSaves> keys = GetOptionsKeys();
        for (OptionsSaves key : keys)
        {
            QString s;
            in >> s;
            if (!UpdateOptionsSaves(key, s))
            {
                SetInitialOptionsSaves();
                SaveOptionsSaves();
                break;
            }
        }
    }
    file.close();
}

void SavesManager::LoadMainSaves()
{
    file::FileManager file(_MAIN_SAVES_LINK);
    bool isOk;
    QList<MainSaves> keys = {MainSaves::Health, MainSaves::ArrowsCount, MainSaves::LevelName};
    for (MainSaves key : keys)
    {
        isOk = UpdateMainSaves(key, file.GetStringValue(GetMainSavesStringKey(key)));
        if (!isOk)
        {
            SetInitialMainSaves();
            SaveMainSaves();
            return;
        }
    }

}

/*!
 * \brief SavesManager::UpdateOptionsSaves
 * Updates option saves value with true/false values
 * \param key key of save value
 * \param value_status new value
 * \return true if update was successful, false otherwise
 */
bool SavesManager::UpdateOptionsSaves(OptionsSaves key, bool value_status)
{
    if (key == OptionsSaves::Resolution)
    {
        return false;
    }
    _options.insert(key, value_status ? "on" : "off");
    return true;
}

/*!
 * \brief SavesManager::UpdateOptionsSaves
 * Updates option saves value
 * \param key key of save value
 * \param value new value
 * \return true if update was successful, false otherwise
 */
bool SavesManager::UpdateOptionsSaves(OptionsSaves key, QString value)
{
    if (key == OptionsSaves::Resolution || value.compare("on") == 0
            || value.compare("off") == 0)
    {
        _options.insert(key, value);
        return true;
    }
    return false;
}

/*!
 * \brief SavesManager::UpdateOptionsSaves
 * Updates main saves value
 * \param key key of save value
 * \param value new value
 * \return true if update was successful, false otherwise
 */
bool SavesManager::UpdateMainSaves(MainSaves key, QString value)
{
    bool isOk = false;
    if (key == MainSaves::Health || key == MainSaves::ArrowsCount)
    {
        int v = value.toInt(&isOk);
        if (!isOk || v < 0 || (key == MainSaves::Health && (v > 100 || v == 0)))
        {
            return false;
        }
    }
    _saves.insert(key, value);
    return true;
}

/*!
 * \brief SavesManager::LoadOptionsSaveValue
 * Loads options saves with value \param key
 * to \param status
 */
void SavesManager::LoadOptionsSaveValue(OptionsSaves key, bool *status)
{
    *status = _options[key] == "on";
}

/*!
 * \brief SavesManager::GetOptionsSaveValue
 * \param key key of options saves
 * \return value of options saves
 */
QString SavesManager::GetOptionsSaveValue(OptionsSaves key)
{
    return _options[key];
}

QString SavesManager::GetMainSaveValue(MainSaves key)
{
    return _saves[key];
}

void SavesManager::SaveOptionsSaves()
{
    QFile file(_OPTIONS_LINK);
    if (!file.open(QFile::WriteOnly))
    {
        return;
    }
    QDataStream out(&file);
    for (OptionsSaves key : _options.keys())
    {
        out << _options[key];
    }
    file.close();
    OptionsWasChanged();
}

void SavesManager::SaveMainSaves()
{
    QFile file(_MAIN_SAVES_LINK);
    if (!file.open(QFile::WriteOnly))
    {
        return;
    }
    QTextStream out(&file);
    int  i = 0;
    for (MainSaves key : _saves.keys())
    {
        out << "_" + GetMainSavesStringKey(key) << ": " << _saves[key] << ";\n";
        i++;
    }
    file.close();
}

}
