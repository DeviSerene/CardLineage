#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Stats.h"
#include "Appearance.h"


class Enemy
{
public:
	Enemy();
	~Enemy();

	void DrawBattle(SDL_Rect _pos, Uint8 _r = 255, Uint8 _g = 255, Uint8 _b = 255);
	void Update(float& _time) { m_appearance->Update(_time); }
	std::shared_ptr<Stats> GetStats() { return m_stats; }
	void TakeDamage(int _amount, int _type, int _element);

	bool IsDead() { return m_dead; }

private:
	bool m_dead;
	std::shared_ptr<Stats> m_stats;
	std::shared_ptr<Appearance> m_appearance;
};

