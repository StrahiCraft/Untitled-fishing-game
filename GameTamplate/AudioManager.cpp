#include "AudioManager.h"
#include "Dictionary.cpp"

FMOD::System* AudioManager::_audioSystem;
Dictionary<string, FMOD::Sound*> AudioManager::_soundEffects;
Dictionary<string, FMOD::Sound*> AudioManager::_music;
FMOD::Channel* AudioManager::_musicChannel;

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
	channel->setVolume(0.24f);

	debugResult(result);
}

void AudioManager::playSound(string sfxName, float pitch) {
	FMOD_RESULT result;
	FMOD::Sound* sound = _soundEffects.getValue(sfxName);
	FMOD::Channel* channel;

	result = _audioSystem->playSound(sound, nullptr, false, &channel);
	channel->setPitch(pitch);
	channel->setVolume(0.24f);

	debugResult(result);
}

void AudioManager::addSong(string songName, string songDirectory) {
	FMOD_RESULT result;
	FMOD::Sound* newSound;
	result = _audioSystem->createSound(songDirectory.c_str(), FMOD_LOOP_NORMAL | FMOD_2D, 0, &newSound);
	_music.addItem(songName, newSound);

	debugResult(result);
}

void AudioManager::playSong(string songName) {
	FMOD_RESULT result;
	_musicChannel->stop();
	FMOD::Sound* song = _music.getValue(songName);

	result = _audioSystem->playSound(song, nullptr, false, &_musicChannel);
	_musicChannel->setVolume(0.24f);

	debugResult(result);
}

void AudioManager::stopMusic() {
	_musicChannel->stop();
}

void AudioManager::debugResult(FMOD_RESULT result) {
	//std::cout << result << std::endl;
}
