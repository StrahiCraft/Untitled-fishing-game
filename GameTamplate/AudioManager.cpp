#include "AudioManager.h"
#include "Dictionary.cpp"

FMOD::System* AudioManager::_audioSystem;
Dictionary<string, FMOD::Sound*> AudioManager::_soundEffects;
Dictionary<string, FMOD::Channel*> AudioManager::_soundEffectChannels;
Dictionary<string, FMOD::Channel*> AudioManager::_musicChannels;
Dictionary<string, FMOD::Sound*> AudioManager::_music;

void AudioManager::init() {
	FMOD_RESULT result;
	FMOD::System_Create(&_audioSystem);
	result = _audioSystem->init(50, FMOD_INIT_NORMAL, NULL);

	std::cout << result << std::endl;
}

void AudioManager::addSound(string sfxName, string sfxDirectory) {
	FMOD_RESULT result;
	FMOD::Sound* newSound;
	result = _audioSystem->createSound(sfxDirectory.c_str(), FMOD_DEFAULT, 0, &newSound);
	_soundEffects.addItem(sfxName, newSound);

	std::cout << result << std::endl;
}

void AudioManager::playSound(string sfxName) {
	FMOD_RESULT result;
	FMOD::Sound* sound = _soundEffects.getValue(sfxName);
	FMOD::Channel* channel;

	result = _audioSystem->playSound(sound, nullptr, false, &channel);

	std::cout << result << std::endl;
}

void AudioManager::addSong(string songName, string songDirectory) {

}

void AudioManager::playSong(string songName) {

}
