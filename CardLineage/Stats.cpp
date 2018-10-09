#include "Stats.h"



Stats::Stats()
{
	m_hp = std::shared_ptr<Stat>(new Stat());
	m_atk = std::shared_ptr<Stat>(new Stat());
	m_mag = std::shared_ptr<Stat>(new Stat());
	m_ar = std::shared_ptr<Stat>(new Stat());
	m_mr = std::shared_ptr<Stat>(new Stat());
	m_mana = 3;
	m_maxMana = 3;
}


Stats::~Stats()
{
}

int Stats::GetCurrentStat(int _i)
{
	int ret = 0;

	switch (_i)
	{
	case 0: //HP
		return m_hp->GetCurrent();
		break;
	case 1: //ATK
		return m_atk->GetCurrent();
		break;
	case 2: //MAG
		return m_mag->GetCurrent();
		break;
	case 3: //AR
		return m_ar->GetCurrent();
		break;
	case 4: //MR
		return m_mr->GetCurrent();
		break;
	case 5: //AGI
		ret = 1;
		break;
	case 6: //MND
		ret = 1;
		break;
	}

	return ret;
}

int Stats::GetMaxStat(int _i)
{
	int ret = 0;

	switch (_i)
	{
	case 0: //HP
		return m_hp->GetMax();
		break;
	case 1: //ATK
		return m_atk->GetMax();
		break;
	case 2: //MAG
		return m_mag->GetMax();
		break;
	case 3: //AR
		return m_ar->GetMax();
		break;
	case 4: //MR
		return m_mr->GetMax();
		break;
	case 5: //AGI
		ret = 1;
		break;
	case 6: //MND
		ret = 1;
		break;
	}

	return ret;
}


void Stats::ModifyEffect(int _s, int _value)
{
	switch (_s)
	{
	case 0: //HP
		m_hp->ModEffect(_value);
		break;
	case 1: //ATK
		m_atk->ModEffect(_value);
		break;
	case 2: //MAG
		m_mag->ModEffect(_value);
		break;
	case 3: //AR
		m_ar->ModEffect(_value);
		break;
	case 4: //MR
		m_mr->ModEffect(_value);
		break;
	case 5: //AGI
		break;
	case 6: //MND
		break;
	}
}

bool Stats::TakeDamage(int _amount, int _type, int _element)
{
	// type: 0 = Pierce; 1 = Physical; 2 = Magical

	int damage = 0;

	switch (_type)
	{
	case 0:
		m_hp->ModEffect(-_amount);
		break;
	case 1:
		damage = _amount;
		if (damage > m_ar->GetCurrent())
		{
			damage -= m_ar->GetCurrent();
			//if the damage is greater than the armour, then some damage pierces through
			m_ar->SetToZero();
			m_hp->ModEffect(-damage);
		}
		else
		{
			m_ar->ModEffect(-_amount);
		}
		break;
	case 2: 
		damage = _amount;
		if (damage > m_mr->GetCurrent())
		{
			damage -= m_mr->GetCurrent();
			//if the damage is greater than the armour, then some damage pierces through
			m_mr->SetToZero();
			m_hp->ModEffect(-damage);
		}
		else
		{
			m_mr->ModEffect(-_amount);
		}
		break;
	default:
		break;
	}

	if (m_hp->GetCurrent() <= 0)
	{
		return true;
	}
	return false;
}

void Stats::Heal(int _amount)
{
	int heal = _amount;
	if (heal < m_hp->GetMax() - m_hp->GetCurrent()) //if the heal would not bring it above max hp
	{
		m_hp->ModEffect(heal);
	}
	else
	{
		m_hp->ModEffect(m_hp->GetMax() - m_hp->GetCurrent());
	}
}