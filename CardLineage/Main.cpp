
#include <SDL.h> //SDL
#include <iostream> //debugging mainly
#include "SpriteFactory.h" //handles sprites
#include <ctime> //for random generation
#include <vector> //a very useful tool
#include <memory>
#include "GameData.h"
#include "GamestateManager.h"
#include "GameState.h"
#include "MenuState.h"

// function prototypes
void GameLoop(std::shared_ptr<GameData> _gameData);


int main(int, char**)
{
	srand(time(0));


	// try initialising SDL, log error and pause if fail
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
		system("pause");
		return 0;
	}

	// If the code reached here, everything is successful so far! :D
	std::shared_ptr<GameData> gameData = std::shared_ptr<GameData>(new GameData());
	if (gameData->Init(1600, 900) == 0)
	{
		return 0;
	}


	gameData->m_stateManager = std::shared_ptr<GamestateManager>(new GamestateManager());
	gameData->m_stateManager->AddState(std::shared_ptr<GameState>(new MenuState(gameData)));
	GameLoop(gameData); //start the game loop

	// clean up, free any memory we have used
	//delete gameData;
	gameData = nullptr;
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}

void GameLoop(std::shared_ptr<GameData> _gameData)
{
	srand(time(NULL)); //initialise the randomseed
	bool play = true;
	bool exit = false;

	//_gameData->GetAudio()->MusicPlay("assets/fft_trisection.mid");

	while (play) 
	{ // this is the main game loop

		unsigned int current = SDL_GetTicks();
		float deltaTs = (float)(current - _gameData->GetLastTime()) / 1000.0f;
		_gameData->SetLastTime(current);

		//handle all the SDL events like key presses etc
		if (!_gameData->m_stateManager->HandleSDLEvents())
		{
			exit = true;
		}

		//update our game
		if (!_gameData->m_stateManager->IsEmpty())
			_gameData->m_stateManager->Update(deltaTs);

		// Draw our game
		SDL_SetRenderDrawColor(_gameData->GetRenderer(), 0x0, 0x0, 0x0, 0xFF);
		SDL_RenderClear(_gameData->GetRenderer());
		if (!_gameData->m_stateManager->IsEmpty())
			_gameData->m_stateManager->Draw();

		SDL_RenderPresent(_gameData->GetRenderer());

		if (exit)
		{
			exit = false;
		//	_gameData->m_stateManager->RemoveLastState();
			if (_gameData->m_stateManager->IsEmpty())
				play = false;
		}
	}

}

