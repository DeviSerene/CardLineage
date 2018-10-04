#include "Card.h"



Card::Card()
{
	m_name = "FireBall";
	m_colour = 0;
	m_image = 0;
	m_manaCost = 1;
	m_target = 1;
	// (ID, Base, Ratio, Stat, Element, DamageT, Target)
	m_effects.push_back((std::shared_ptr<Effect>)new Effect(0, 3, 100, 2, 1, 2, 1));
	m_aniEffects.push_back((std::shared_ptr<AniEffect>)new AniEffect(1, 0, 0));
	m_effects.push_back((std::shared_ptr<Effect>)new Effect(1, 1, 100, 2, 0));
	m_aniEffects.push_back((std::shared_ptr<AniEffect>)new AniEffect(2, 1.0f, 1.0f));
	m_effects.push_back((std::shared_ptr<Effect>)new Effect(1, 1, 50, 2, 8));
	m_aniEffects.push_back((std::shared_ptr<AniEffect>)new AniEffect(2, 1.3f, 1.3f));
}

Card::Card(std::shared_ptr<Card> _cc)
{
	m_name = "Combo FireBall";
	m_colour = 0;
	m_image = 0;
	m_target = 2;
	m_manaCost = 1;
	// (ID, Base, Ratio, Stat, Element, DamageT, Target)
	m_effects.push_back((std::shared_ptr<Effect>)new Effect(0, 10, 50, 2, 1, 2, 2));
	m_aniEffects.push_back((std::shared_ptr<AniEffect>)new AniEffect(1, 0, 1.0f));
	m_comboCard = true;
	m_CCneeded.push_back(_cc);
	m_CCneeded.push_back(_cc);
}

Card::Card(std::string _name)
{
	m_name = _name;
	m_colour = 0;
	m_image = 0;
	m_target = 4;
	m_manaCost = 1;
	// (ID, Base, Ratio, Stat, Target)
	m_effects.push_back((std::shared_ptr<Effect>)new Effect(1, 10, 50, 2, 4));
	m_aniEffects.push_back((std::shared_ptr<AniEffect>)new AniEffect(2, 1.0f, 2.0f));
	//m_effects.push_back((std::shared_ptr<Effect>)new Effect(1, 1, 100, 2, 0));
	//m_effects.push_back((std::shared_ptr<Effect>)new Effect(1, 1, 50, 2, 8));
}


Card::~Card()
{
	//for each (Effect* var in m_effects)
	//{
	//	delete var;
	//}
	m_effects.clear();
}