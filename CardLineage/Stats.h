#pragma once
#include "Stat.h"
#include <memory>

class Stats
{
public:
	Stats();
	~Stats();
	int GetCurrentStat(int _i);
	int GetMaxStat(int _i);
	int GetMana() { return m_mana; }
	void ModifyEffect(int _s, int _value);
	void ModifyMana(int _i) { m_mana += _i; if (m_mana > m_maxMana)m_mana = m_maxMana; else if (m_mana < 0) m_mana = 0; }
	bool TakeDamage(int _amount, int _type, int _element);
	void Heal(int _amount);
private:
	std::shared_ptr<Stat> m_hp;
	std::shared_ptr<Stat> m_atk;
	std::shared_ptr<Stat> m_mag;
	std::shared_ptr<Stat> m_ar;
	std::shared_ptr<Stat> m_mr;
	int m_mana;
	int m_maxMana;

};

