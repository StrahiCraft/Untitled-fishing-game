#pragma once
#include <fmod.hpp>
#include <iostream>
#include "Dictionary.h"

static class AudioManager
{
private:
	static FMOD::System* _audioSystem;
	static Dictionary<string, FMOD::Sound*> _soundEffects;
	static Dictionary<string, FMOD::Channel*> _soundEffectChannels;
	static Dictionary<string, FMOD::Sound*> _music;
	static Dictionary<string, FMOD::Channel*> _musicChannels;
public:
	static void init();
	static void addSound(string sfxName, string sfxDirectory);
	static void playSound(string sfxName);
	static void addSong(string songName, string songDirectory);
	static void playSong(string songName);
};

