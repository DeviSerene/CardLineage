#pragma once
#include <SDL.h>
#include "GameState.h"
#include "GamestateManager.h"
#include "Appearance.h"
#include "CardHolder.h"
#include "BattleDeck.h"
#include "Character.h"
#include "Enemy.h"
#include "Button.h"
#include "AnimationManager.h"
#include "BattleEffect.h"
#include <memory>
#include "FloatingTextManager.h"

class MenuState :
	public GameState
{
public:
	MenuState(std::shared_ptr<GameData> _gamedata);				//constructor
	~MenuState();								//destructor

	bool HandleSDLEvents();						//handle inputs
	void Update(float _deltaTime);				//update 
	void Draw();								//draw to renderer
private:

	struct Target
	{
		Target(SDL_Rect _p, int _id) { m_pos = _p; m_id = _id; }
		SDL_Rect m_pos;
		int m_id;
	};

	std::shared_ptr<FloatingTextManager> m_battleText;

	std::shared_ptr<AnimationManager> m_animations;
	std::shared_ptr<BattleEffect> m_effectManager;

	std::vector <std::shared_ptr<Character>> m_party;
	std::vector <std::shared_ptr<Enemy>> m_enemies;
	
	BattleDeck* deck;
	std::vector <std::shared_ptr<Card>> m_cards;
	std::vector <std::shared_ptr<Card>> m_combocards;
	std::vector <Button*> m_buttons;

	std::vector<int> m_characterHighlights;
	std::vector<SDL_Rect> m_partyPos;
	std::vector<SDL_Rect> m_enemyPos;
	std::vector<Target> m_targets;
	std::vector<SDL_Rect> m_highlightTargets;
	int m_target;
	int m_manaHighlight;

	int m_chosenCard;
	int m_targetType;
	int m_battleState;

	void InitTargets();
	void MouseOverTarget(int& x, int& y);
	void DrawTargets();
	void ResetAlliesPos();


};

