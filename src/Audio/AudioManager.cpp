#include "Audio/AudioManager.h"
#include <Audio/AudioSource.h>


namespace kte 
{
    namespace Sound 
    {
	float masterVolume = 1.0f;
	bool muted = false;
    }
    namespace Music 
    {
	float masterVolume = 1.0f;
	bool muted = false;
    }

    AudioManager::~AudioManager()
    {
	for(auto& source : audioSources)
	{
	    source.second->setAudioManager(nullptr);
	}
    }

    void AudioManager::update()
    {

    }

    void AudioManager::addAudioSource(AudioSource* audioSource)
    {
	audioSources[audioSource->getID()] = audioSource;
    }
    
    void AudioManager::removeAudioSource(AudioSource* audioSource)
    {
	audioSources.erase(audioSource->getID());
    }
	
    void AudioManager::muteMusic(bool mute)
    {

    }
    void AudioManager::muteSound(bool mute)
    {

    }
    void AudioManager::setMusicVolume(float volume)
    {

    }
    void AudioManager::setSoundVolume(float volume)
    {

    }

}








