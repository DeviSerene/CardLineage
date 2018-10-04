#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_mixer.h>
#include <SDL_ttf.h> //text
#include <SDL_image.h> //images
#include "SpriteFactory.h"
#include "AudioManager.h"
#include <memory>

class GamestateManager;

class GameData
{
public:
	GameData();
	~GameData();

	int Init(int _windowX, int _windowY);
	std::shared_ptr<GamestateManager> m_stateManager;
	unsigned int GetLastTime() { return m_lastTime; }
	void SetLastTime(unsigned int _f) { m_lastTime = _f; }

	SDL_Window* GetWindow() { return m_window; }
	SDL_Renderer* GetRenderer() { return m_renderer; }


private:

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	unsigned int m_lastTime;
};

