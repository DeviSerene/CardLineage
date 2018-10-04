#include "Character.h"



Character::Character()
{
	m_appearance = (std::shared_ptr<Appearance>)new Appearance();
	m_stats = (std::shared_ptr<Stats>)new Stats();

	m_manaHighlight = 0;

	m_cards.push_back(0);
	m_cards.push_back(1);
	m_cards.push_back(2);
	m_cards.push_back(3);
	
	m_cards.push_back(4);
	m_cards.push_back(5);
	m_cards.push_back(0);
	m_cards.push_back(1);
	m_cards.push_back(2);
	m_cards.push_back(3);
	m_cards.push_back(4);
	m_cards.push_back(5);
	m_cards.push_back(0);
	m_cards.push_back(0);
	m_cards.push_back(0);
}


Character::~Character()
{
	//delete m_appearance;
	m_appearance = nullptr;
	//delete m_stats;
}

void Character::DrawBattle(SDL_Rect _pos, Uint8 _r, Uint8 _g, Uint8 _b)
{
	//draw character
	m_appearance->Draw(_pos, _r, _g, _b);

	DrawBattleBars(_pos);

}

void Character::DrawBattleBars(SDL_Rect& _pos)
{
	SDL_Rect rect;
	//draw hp bar
	rect.x = (_pos.x + (_pos.w / 2)) - 32;
	rect.y = _pos.y + _pos.h;
	rect.w = 64;
	rect.h = 5;
	//
	rect.w = (float)rect.w *((float)m_stats->GetCurrentStat(0) / (float)m_stats->GetMaxStat(0));
	if (rect.w > 64) rect.w = 64;
	SpriteFactory::Draw("assets/battle/hp.png", rect);

	rect.x = (_pos.x + (_pos.w / 2)) - 40;
	rect.w = 80;
	SpriteFactory::Draw("assets/battle/bar.png", rect);

	//draw ar/mr bar
	rect.y += 5;
	rect.w = 40;
	SpriteFactory::Draw("assets/battle/ar.png", rect);
	rect.x += 40;
	SpriteFactory::Draw("assets/battle/mr.png", rect);
	rect.x -= 40;
	rect.w = 80;
	SpriteFactory::Draw("assets/battle/armr.png", rect);

	//draw mana
	for (int i = 0; i < m_stats->GetMana(); i++)
	{
		rect.x = _pos.x + (_pos.w / 3) + (8 * i);
		rect.y = _pos.y + _pos.h - 8;
		rect.w = 7;
		rect.h = 7;
		SpriteFactory::Draw("assets/battle/mana.png", rect);
	}
	for (int m = 0; m < m_manaHighlight; m++)
	{
		//highlight mana cost of the spell
		SDL_Rect rect;
		rect.x = _pos.x + (200 / 3) + (8 * m);
		rect.y = _pos.y + 200 - 8;
		rect.w = 7;
		rect.h = 7;
		SpriteFactory::Draw("assets/battle/manaHighlight.png", rect);
	}
}

void Character::TakeDamage(int _amount, int _type, int _element)
{
	if (m_stats->TakeDamage(_amount, _type, _element))
	{
		//character is now dead
		m_dead = true;
		m_appearance->SetAnimation(3);
	}
}