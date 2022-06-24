#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <QMediaPlayer>

#include "enums/audio_names_enum.h"
#include "saves_manager.h"

namespace audioManager {

class AudioManager : public QObject
{
    Q_OBJECT

public:
    AudioManager();
    AudioManager(AudioNames name);
    void Stop();
    void SetMedia(AudioNames name);
    void Start();
    void CheckStatus();

private:
    void Init();
    QMediaPlayer *media;
    QUrl media_url;
    savesManager::SavesManager *_save_manager;
    bool isAudioSetted = false;
    bool isAudioPlaying = false;
    void ConvertNameToUrl(AudioNames name);
    bool IsMusicAllowed();
};

}

#endif // AUDIO_MANAGER_H
