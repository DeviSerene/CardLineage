#pragma once
#include "Effect.h"
#include "AniEffect.h"
#include "Character.h"
#include "Enemy.h"
#include "AnimationManager.h"
#include <vector>
#include <memory>
#include "FloatingTextManager.h"

class BattleEffect
{
public:
	BattleEffect(int* _battleState, int* _target, int* _targetType, std::shared_ptr<AnimationManager> _animan, std::vector<std::shared_ptr<Character>>& _partyPointer, std::vector<std::shared_ptr<Enemy>>& _enemyPointer, std::vector<SDL_Rect> _partyPos, std::vector<SDL_Rect> _enemyPos);
	~BattleEffect();

	void InitText(FloatingTextManager* _text) { m_texts = _text; }

	void SetUser(std::shared_ptr<Character> _u) { m_user = _u; m_comboer = NULL; }
	void SetComboer(std::shared_ptr<Character> _u) { m_comboer = _u; }
	void AddEffects(std::vector<std::shared_ptr<Effect>> _effects, std::vector<std::shared_ptr<AniEffect>> _aniEffects);
	void Update(float& _deltaTime);
	void DeInit();

	bool IsEffectEmpty() { return m_aniEffects.empty(); }

private:
	int m_randomTarget;
	std::shared_ptr<AnimationManager> m_animan; //a pointer to the Animation Manager
	std::vector<SDL_Rect> m_aniList; //the list of where the animations will be
	FloatingTextManager* m_texts;

	std::shared_ptr<Character> m_user; //a pointer to the character that we will use the stats to determine the damage
	std::shared_ptr<Character> m_comboer; //if this is a combo card, who is the other ccharacter?

	std::vector<std::shared_ptr<Character>> m_partyTargets; //who the cards are effecting
	std::vector<std::shared_ptr<Enemy>> m_enemyTargets; //who the cards are effecting - should have probably have Enemies and Characters share a class

	std::shared_ptr<int> m_battleState; //a pointer to the state of the battle in 
	std::shared_ptr<int> m_target; //a pointer to the target that the user chose
	std::shared_ptr<int> m_targetType; //a pointer to the target that the user chose

	std::vector<std::shared_ptr<Effect>> m_effects; //the effects that are currently playing
	std::vector<std::shared_ptr<AniEffect>> m_aniEffects;

	std::vector<std::shared_ptr<Character>> m_party; //pointers to the parties and enemies and their locations
	std::vector<std::shared_ptr<Enemy>> m_enemies;
	std::vector<SDL_Rect> m_partyPos;
	std::vector<SDL_Rect> m_enemyPos;

	void GetAniPlacement(std::shared_ptr<Effect> _effect);
	void GetTargets(std::shared_ptr<Effect> _effect);
	void ApplyEffect(std::shared_ptr<Effect> _effect);

	void DealDamageEffect(std::shared_ptr<Effect> _effect);
	void HealDamageEffect(std::shared_ptr<Effect> _effect);
};

