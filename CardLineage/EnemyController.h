#pragma once
#include "Enemy.h"
#include "Character.h"
#include "BattleEffect.h"
#include <memory>
#include <vector>

class EnemyController
{
public:
	EnemyController(int* _battleState, int* _target, int* _targetType, std::shared_ptr<BattleEffect>& _animan, std::vector<std::shared_ptr<Character>>& _partyPointer, std::vector<std::shared_ptr<Enemy>>& _enemyPointer, std::vector<SDL_Rect> _partyPos, std::vector<SDL_Rect> _enemyPos);
	~EnemyController();

	void Update(float& _deltaTime);

private:

	//functions
	bool MoveUp();
	bool MoveBack();
	bool PerformAbility();

	//variables
	int m_phase;
	int m_current; //the current enemy performing their attack
	std::shared_ptr<EnemyAbility> m_ability; //the ability to be performed

	//POINTERS from BATTLESTATE
	std::shared_ptr<BattleEffect> m_effman; //a pointer to the BattleEffect Manager
	std::vector<std::shared_ptr<Character>> m_party; //pointers to the parties and enemies and their locations
	std::vector<std::shared_ptr<Enemy>> m_enemies;
	std::vector<SDL_Rect> m_partyPos;
	std::vector<SDL_Rect> m_enemyPos;
	int* m_battleState; //a pointer to the state of the battle in 
	int* m_target; //a pointer to the target that the user chose
	int* m_targetType; //a pointer to the targettype that the user chose
};

