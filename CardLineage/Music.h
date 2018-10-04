#pragma once
#include <SDL_mixer.h>
#include <string>
#include <memory>

class Music
{
public:
	Music(std::string _name);
	~Music();
	void PlayMusic();
	std::string GetName() { return m_name; }
private:
	std::shared_ptr<Mix_Music> m_music = NULL;
	std::string m_name;
};

