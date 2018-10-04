#include "GameData.h"


GameData::GameData()
{
	m_lastTime = 0;
}


GameData::~GameData()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_renderer = nullptr;
	m_window = nullptr;
}

int GameData::Init(int _windowX, int _windowY)
{

	// try to create the window, log error and pause if fail
	m_window = SDL_CreateWindow("Window", 125, 100, _windowX, _windowY, SDL_WINDOW_SHOWN);
	if (m_window == NULL)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("pause");
		return 0;
	}

	// try to create the renderer, log error and pause if fail
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == NULL)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		system("pause");
		return 0;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_TTF could not initialize!";
		system("pause");
		return 0;
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError();
		system("pause");
		return 0;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return 0;
	}

	SpriteFactory::SetRenderer(GetRenderer());

	return 1;
}