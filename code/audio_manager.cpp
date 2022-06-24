#include "audio_manager.h"
#include "task_manager.h"

#include "enums/saves_manager_enum.h"

namespace audioManager {

/*!
 * \brief AudioManager::AudioManager
 * Constructor
 */
AudioManager::AudioManager()
{
    Init();
}

/*!
 * \brief AudioManager::AudioManager
 * Constructor
 * \param name name of audio file
 */
AudioManager::AudioManager(AudioNames name)
{
    Init();
    SetMedia(name);
    Start();
}

void AudioManager::Init()
{
    media = new QMediaPlayer();
    media_url = "";
    _save_manager = TaskManager::GetInstance().GetSavesManager();
    connect(_save_manager, &savesManager::SavesManager::OptionsWasChanged, this, &AudioManager::CheckStatus);
}

void AudioManager::Stop()
{
    media->stop();
    isAudioPlaying = false;
}

/*!
 * \brief AudioManager::SetMedia
 * Sets current media file with name
 * \param name
 */
void AudioManager::SetMedia(AudioNames name)
{
    Stop();
    ConvertNameToUrl(name);
    media->setMedia(media_url);
    isAudioSetted = true;
}

void AudioManager::ConvertNameToUrl(AudioNames name)
{
    if (name == AudioNames::MainMenu)
        media_url = "../src/audio/main_menu_music.mp3";
    else if (name == AudioNames::GameLevel)
        media_url = "../src/audio/game_level_music.mp3";
    else if (name == AudioNames::Strike)
        media_url = "../src/audio/strike.mp3";
    else if (name == AudioNames::Gather)
        media_url = "../src/audio/gatherItem.wav";
}

void AudioManager::Start()
{
    if (!IsMusicAllowed())
        return;
    media->play();
    isAudioPlaying = true;
}

/*!
 * \brief AudioManager::CheckStatus
 * Checks if audio playing is allowed
 */
void AudioManager::CheckStatus()
{
    if (!IsMusicAllowed())
        Stop();
    else
        Start();
}

bool AudioManager::IsMusicAllowed()
{
    bool music_status;
    _save_manager->LoadOptionsSaveValue(savesManager::OptionsSaves::MusicMode, &music_status);
    return music_status;
}

}
