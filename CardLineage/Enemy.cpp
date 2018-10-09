#include "Enemy.h"



Enemy::Enemy()
{
	m_appearance = std::shared_ptr<Appearance>(new Appearance());
	m_stats = std::shared_ptr<Stats>(new Stats());

	m_abilities.push_back(std::shared_ptr<EnemyAbility>(new EnemyAbility()));
	m_abilities[0]->m_target = 1;
	m_abilities[0]->m_userAni = 1;
	m_abilities[0]->m_effects.push_back(std::shared_ptr<Effect>(new Effect(0, 3, 20, 2, 1, 2, 1)));
	m_abilities[0]->m_aniEffects.push_back(std::shared_ptr<AniEffect>(new AniEffect(1, 0, 1.0f)));
}


Enemy::~Enemy()
{
}

void Enemy::DrawBattle(SDL_Rect _pos, Uint8 _r, Uint8 _g, Uint8 _b)
{
	//draw character
	m_appearance->Draw(_pos, _r, _g, _b);

	
	DrawBattleBars(_pos);
	
}

void Enemy::TakeDamage(int _amount, int _type, int _element)
{
	if (m_stats->TakeDamage(_amount, _type, _element))
	{
		//character is now dead
		m_dead = true;
		m_appearance->SetAnimation(3);
	}
}

void Enemy::DrawBattleBars(SDL_Rect& _pos)
{
	if (!m_dead)
	{
		SDL_Rect rect;
		//draw hp bar
		rect.x = (_pos.x + (_pos.w / 2)) - 32;
		rect.y = _pos.y + _pos.h;
		rect.w = 64;
		rect.h = 10;

		//helthbar
		rect.w = (float)rect.w *((float)m_stats->GetCurrentStat(0) / (float)m_stats->GetMaxStat(0));
		if (rect.w > 64) rect.w = 64;
		SpriteFactory::Draw("assets/battle/hp.png", rect);

		rect.x = (_pos.x + (_pos.w / 2)) - 40;
		rect.w = 80;
		SpriteFactory::Draw("assets/battle/bar.png", rect);

		//draw ar/mr bar
		rect.y += rect.h;
		rect.w = 40;
		rect.w = (float)rect.w *((float)m_stats->GetCurrentStat(3) / (float)m_stats->GetMaxStat(3));
		if (rect.w > 40) rect.w = 40;
		SpriteFactory::Draw("assets/battle/ar.png", rect);

		rect.w = 40;
		rect.x += 40;
		rect.w = (float)rect.w *((float)m_stats->GetCurrentStat(4) / (float)m_stats->GetMaxStat(4));
		if (rect.w > 40) rect.w = 40;
		SpriteFactory::Draw("assets/battle/mr.png", rect);

		rect.x -= 40;
		rect.w = 80;
		SpriteFactory::Draw("assets/battle/armr.png", rect);
	}
}
