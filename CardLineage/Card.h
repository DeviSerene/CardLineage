#pragma once
#include <string>
#include <vector>
#include "TextBox.h"
#include "SpriteFactory.h"
#include "Effect.h"
#include "AniEffect.h"
#include <memory>

class Card
{
public:
	Card();
	Card(std::shared_ptr<Card> _cc);
	Card(std::string _name);
	~Card(); 
	int GetImage() { return m_image; }
	std::string GetName() { return m_name; }
	std::vector <std::shared_ptr<Effect>> GetEffects() { return m_effects;}
	std::vector <std::shared_ptr<AniEffect>> GetAniEffects() { return m_aniEffects; }
	int GetMana() { return m_manaCost; }
	int GetTarget() { return m_target; }
	bool IsCC() { return m_comboCard; }

	std::vector<std::shared_ptr<Card>> GetCCNeeded() { return m_CCneeded; }

private:
		std::string m_name;

		int m_colour;
		int m_image;
		int m_manaCost;
		int m_target;
		std::vector <std::shared_ptr<Effect>> m_effects;
		std::vector <std::shared_ptr<AniEffect>> m_aniEffects;
//		TargetType m_target;
		int m_animation;

		bool m_comboCard;
		std::vector<std::shared_ptr<Card>> m_CCneeded;
};

