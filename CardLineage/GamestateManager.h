#ifndef _GAMESTATEMANAGER_
#define _GAMESTATEMANAGER_

#include "GameState.h"
#include <vector>
#include <SDL.h>
#include <iostream>
#include <memory>

class GamestateManager {

public:
	//destructor
	~GamestateManager();

	//gamestate management
	void AddState(std::shared_ptr<GameState> gamestate);
	void ChangeState(std::shared_ptr<GameState> gamestate);
	void RemoveLastState();

	//used to update / draw whichever states need it
	bool HandleSDLEvents();
	void Update(float deltaTime);
	void Draw();
	bool IsEmpty() { return gameStates.empty(); }

private:
	//list of all gamestates currently in use
	std::vector<std::shared_ptr<GameState>> gameStates;
};

#endif