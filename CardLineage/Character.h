#pragma once
#include <string>
#include <vector>
#include "Stats.h"
#include "Appearance.h"
#include <memory>

class Character
{
public:
	Character();
	~Character();
	void Draw() { m_appearance->Draw(255, 255, 255); }
	void DrawChara(SDL_Rect _pos) { m_appearance->Draw(255,255,255); };
	void DrawBattle(Uint8 _r, Uint8 _g, Uint8 _b) { m_appearance->Draw(_r, _g, _b, true); DrawBattleBars(m_appearance->GetPos()); }
	void DrawBattle(SDL_Rect _pos, Uint8 _r = 255, Uint8 _g = 255, Uint8 _b = 255);
	void MoveTo(SDL_Rect _moveTo) { m_appearance->MoveTo(_moveTo); }
	void SetColour(int _c) { m_appearance->SetColour(_c); }

	void Update(float& _time) { m_appearance->Update(_time);}

	void SetManaHighlight(int _set) { m_manaHighlight = _set; }
	std::shared_ptr<Stats> GetStats() { return m_stats; }
	std::vector<int> GetCards() {return m_cards;}

	void TakeDamage(int _amount, int _type, int _element);
	bool IsDead() { return m_dead; }
	void SetAnimation(int _animation) { m_appearance->SetAnimation(_animation); }


private:
	std::string m_name;
	bool m_dead;
	std::shared_ptr<Stats> m_stats;
	std::shared_ptr<Appearance> m_appearance;
	std::vector<int> m_cards;
	int m_manaHighlight;
	//Personality* m_personality;
	//Relationships
	void DrawBattleBars(SDL_Rect& _pos);
};

