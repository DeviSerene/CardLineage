#include "Effect.h"



Effect::Effect(int _ID, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8)
{
	m_variables.push_back(_ID);
	m_variables.push_back(v1);
	m_variables.push_back(v2);
	m_variables.push_back(v3);
	m_variables.push_back(v4);
	m_variables.push_back(v5);
	m_variables.push_back(v6);
	m_variables.push_back(v7);
	m_variables.push_back(v8);
}


Effect::~Effect()
{
}

std::string Effect::GetDescription(std::shared_ptr<Stats> _user, std::shared_ptr<Stats> _combo)
{
	//The ID corresponds to the EfectType
	// https://docs.google.com/spreadsheets/d/1cQ076us0Dbew5Igi8dzAbV9QqYpK-8Y1rUrlyyjo_10/edit?usp=sharing
	// Has a full list of the Effects and what variables effect them

	std::string ret;

	switch (m_variables[0])
	{
	case 0:
		//Deal x + (r *[stat]) { elemental } {type} damage to[Target].
		ret = "Deal ";
		if(_combo == NULL)
			ret += std::to_string(int(m_variables[1] + (float)((float)m_variables[2]*0.01)*_user->GetCurrentStat(m_variables[3])));
		else
			ret += std::to_string(int(m_variables[1] + (float)((float)m_variables[2] * 0.01)* (_user->GetCurrentStat(m_variables[3])+ _combo->GetCurrentStat(m_variables[3]))));
		ret += " ";
		ret += GetElement(m_variables[4]);
		ret += GetDamageType(m_variables[5]);
		ret += " damage to ";
		ret += GetTargetType(m_variables[6]);
		ret += ". ";
		break;
	case 1:
		//Restore x + (r *[stat]) hp to[Target].
		ret = "Restore ";
		if (_combo == NULL)
			ret += std::to_string(int(m_variables[1] + (float)((float)m_variables[2] * 0.01)*_user->GetCurrentStat(m_variables[3])));
		else
			ret += std::to_string(int(m_variables[1] + (float)((float)m_variables[2] * 0.01)* (_user->GetCurrentStat(m_variables[3]) + _combo->GetCurrentStat(m_variables[3]))));
		ret += " HP to ";
		ret += GetTargetType(m_variables[4]);
		ret += ". ";
		break;
	default:
		break;
	}

	return ret;
}

int Effect::GetDamage(std::shared_ptr<Stats> _user, std::shared_ptr<Stats> _combo)
{
	int ret = 0;

	switch (m_variables[0])
	{
	case 0:
		//Deal x + (r *[stat]) { elemental } {type} damage to[Target].
		if (_combo == NULL)
			ret += int(m_variables[1] + (float)((float)m_variables[2] * 0.01)*_user->GetCurrentStat(m_variables[3]));
		else
			ret += int(m_variables[1] + (float)((float)m_variables[2] * 0.01)* (_user->GetCurrentStat(m_variables[3]) + _combo->GetCurrentStat(m_variables[3])));
		break;
	case 1:
		//Restore x + (r *[stat]) hp to[Target].
		if (_combo == NULL)
			ret += int(m_variables[1] + (float)((float)m_variables[2] * 0.01)*_user->GetCurrentStat(m_variables[3]));
		else
			ret += int(m_variables[1] + (float)((float)m_variables[2] * 0.01)* (_user->GetCurrentStat(m_variables[3]) + _combo->GetCurrentStat(m_variables[3])));
		break;
	default:
		break;
	}

	return ret;
}


std::string Effect::GetElement(int _i)
{
	std::string ret;

	switch (_i)
	{
	case 0:
		ret = "";
		break;
	case 1:
		ret = "Fire ";
		break;
	case 2:
		ret = "Ice ";
		break;
	case 3:
		ret = "Lightning ";
		break;
	case 4:
		ret = "Earth ";
		break;
	case 5:
		ret = "Holy ";
		break;
	case 6:
		ret = "Darkness ";
		break;
	}

	return ret;
}

std::string Effect::GetDamageType(int _i)
{
	std::string ret;

	switch (_i)
	{
	case 0:
		ret = "Piercing";
		break;
	case 1:
		ret = "Physical";
		break;
	case 2:
		ret = "Magical";
		break;
	}

	return ret;
}

std::string Effect::GetTargetType(int _i)
{
	std::string ret;

	switch (_i)
	{
	case 0:
		ret = "Self";
		break;
	case 1:
		ret = "One Enemy";
		break;
	case 2:
		ret = "All Enemies";
		break;
	case 3:
		ret = "a Random Enemy";
		break;
	case 4:
		ret = "One Ally";
		break;
	case 5:
		ret = "All Allies";
		break;
	case 6:
		ret = "a Random Ally";
		break;
	case 7:
		ret = "all other Enemies";
		break;
	case 8:
		ret = "all other Allies";
		break;
	}

	return ret;
}

int Effect::GetTargetInfo()
{
	//returns the target identifier
	switch (m_variables[0])
	{
	case 0:
		return m_variables[6];
		break;
	case 1:
		return m_variables[4];
		break;
	case 2:
		return m_variables[4];
		break;
	case 3:
		return m_variables[4];
		break;
	case 4:
		return m_variables[6];
		break;
	case 5:
		return m_variables[5];
		break;
	case 13:
		return m_variables[6];
		break;
	case 14:
		return m_variables[6];
		break;

	default:
		return 0;
		break;
	}
}