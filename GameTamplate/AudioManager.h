#pragma once
#include <fmod.hpp>
#include <iostream>
#include "Dictionary.h"

static class AudioManager
{
private:
	static FMOD::System* _audioSystem;
	static Dictionary<string, FMOD::Sound*> _soundEffects;
	static Dictionary<string, FMOD::Sound*> _music;
	static FMOD::Channel* _musicChannel;
public:
	static void init();
	static void addSound(string sfxName, string sfxDirectory);
	static void playSound(string sfxName);
	static void playSound(string sfxName, float pitch);
	static void addSong(string songName, string songDirectory);
	static void playSong(string songName);
	static void stopMusic();
private:
	static void debugResult(FMOD_RESULT result);
};

