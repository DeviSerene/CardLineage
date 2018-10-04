#pragma once
#include "Music.h"
#include "SoundEffect.h"
#include <vector>
#include <memory>

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	static void MusicPlay(std::string _name); //Play a specific piece of music, will create the music if not there
	static void MusicToggle(); //toggles playing the current music
	static void MusicStop(); //stops playing the current music
	static void MusicLoad(std::string _name); //load a specific piece in memory
	static void MusicClean(); //clear all musics in memory

	static void SoundPlay(std::string _name, int _channel = -1); //play a sound clip

private:

	static std::shared_ptr<Music> GetMusic(std::string& _name);
	static std::shared_ptr<SoundEffect> GetSound(std::string& _name);
	static void SoundLoad(std::string _name);

	static std::vector <std::shared_ptr<SoundEffect>> m_soundList;
	static std::vector <std::shared_ptr<Music>> m_musicList;
};

