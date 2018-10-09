#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Stats.h"
#include "Appearance.h"

#include "Effect.h"
#include "AniEffect.h"

struct  EnemyAbility
{
	int m_userAni;
	int m_target;
	std::vector <std::shared_ptr<Effect>> m_effects;
	std::vector <std::shared_ptr<AniEffect>> m_aniEffects;
};

class Enemy
{
public:
	Enemy();
	~Enemy();

	void DrawBattle(SDL_Rect _pos, Uint8 _r = 255, Uint8 _g = 255, Uint8 _b = 255);
	void DrawBattle(Uint8 _r, Uint8 _g, Uint8 _b) { m_appearance->Draw(_r, _g, _b); DrawBattleBars(m_appearance->GetPos()); }
	void Update(float& _time) { m_appearance->Update(_time); }
	std::shared_ptr<Stats> GetStats() { return m_stats; }
	void TakeDamage(int _amount, int _type, int _element);

	bool IsDead() { return m_dead; }
	std::vector < std::shared_ptr<EnemyAbility>> GetAbilities() { return m_abilities; }
	std::vector < std::shared_ptr<Effect>> GetEffects() { return m_abilities[0]->m_effects; }
	std::vector <std::shared_ptr<AniEffect>> GetAniEffects() { return m_abilities[0]->m_aniEffects; }
	void MoveTo(SDL_Rect _moveTo) { m_appearance->MoveTo(_moveTo); }
	bool FinishMoving() { return m_appearance->FinishMoving(); }

	void SetAnimation(int _animation) { m_appearance->SetAnimation(_animation); }
private:
	bool m_dead;
	std::shared_ptr<Stats> m_stats;
	std::shared_ptr<Appearance> m_appearance;
	std::vector < std::shared_ptr<EnemyAbility>> m_abilities;
	void DrawBattleBars(SDL_Rect& _pos);
};

