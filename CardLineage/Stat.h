#pragma once
class Stat
{
public:
	Stat();
	~Stat();
	int GetCurrent() { SetCurrent(); return m_current; }
	int GetMax() { return (m_base + m_cumulative + m_equipment); }
	void ModEffect(int _i) { m_effects += _i; }
	void SetToZero() { m_effects -= GetCurrent(); SetCurrent(); }
private:

	int m_current; //The integer used for calculations
	int m_base;// The level1 value of the stat
	int m_cumulative;// The cumulative value gained from level ups
	int m_effects;// The cumulative valued from status effects
	int m_equipment;// The cumulative valued from equipment

	int m_levelUp; //the chance for increasing the stat upon level up
	void SetCurrent() { m_current = m_base + m_cumulative + m_effects + m_equipment; if (m_current < 0)m_current = 0; }


};

