#include "Card.h"



Card::Card()
{
	m_name = "FireBall";
	m_colour = 0;
	m_image = 0;
	m_manaCost = 1;
	m_target = 1;
	m_userAni = 1;
	// (ID, Base, Ratio, Stat, Element, DamageT, Target)
	m_effects.push_back(std::shared_ptr<Effect>(new Effect(0, 2, 50, 2, 1, 2, 1)));
	m_aniEffects.push_back(std::shared_ptr<AniEffect>(new AniEffect(1, 0, 0)));
	m_effects.push_back(std::shared_ptr<Effect>(new Effect(1, 1, 50, 2, 0)));
	m_aniEffects.push_back(std::shared_ptr<AniEffect>(new AniEffect(2, 1.0f, 1.0f)));
	m_effects.push_back(std::shared_ptr<Effect>(new Effect(1, 1, 25, 2, 8)));
	m_aniEffects.push_back(std::shared_ptr<AniEffect>(new AniEffect(2, 1.3f, 1.3f)));
}

Card::Card(std::shared_ptr<Card> _cc)
{
	m_name = "Combo FireBall";
	m_colour = 0;
	m_image = 0;
	m_target = 2;
	m_manaCost = 1;
	m_userAni = 1;
	// (ID, Base, Ratio, Stat, Element, DamageT, Target)
	m_effects.push_back(std::shared_ptr<Effect>(new Effect(0, 10, 50, 2, 1, 2, 2)));
	m_aniEffects.push_back(std::shared_ptr<AniEffect>(new AniEffect(1, 0, 1.0f)));
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
	m_userAni = 1;
	// (ID, Base, Ratio, Stat, Target)
	m_effects.push_back(std::shared_ptr<Effect>(new Effect(1, 10, 50, 2, 4)));
	m_aniEffects.push_back(std::shared_ptr<AniEffect>(new AniEffect(2, 1.0f, 2.0f)));
	//m_effects.push_back((std::shared_ptr<Effect>)new Effect(1, 1, 100, 2, 0));
	//m_effects.push_back((std::shared_ptr<Effect>)new Effect(1, 1, 50, 2, 8));
}

Card::Card(std::string _name, int _image, int _mana, int _target, int _userAni, std::vector <std::shared_ptr<Effect>> _effects, std::vector <std::shared_ptr<AniEffect>> _animations)
{
	m_name = _name;
	m_colour = 0;
	m_image = _image;
	m_target = _target;
	m_manaCost = _mana;
	m_userAni = _userAni;
	m_effects = _effects;
	m_aniEffects = _animations;
}

Card::~Card()
{
	//for each (Effect* var in m_effects)
	//{
	//	delete var;
	//}
	m_effects.clear();
}