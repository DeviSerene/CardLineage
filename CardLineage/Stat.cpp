#include "Stat.h"



Stat::Stat()
{
	m_current = 15; //The integer used for calculations
	m_base = 15;// The level1 value of the stat
	m_cumulative = 0;// The cumulative value gained from level ups
	m_effects = 0;// The cumulative valued from status effects
	m_equipment = 0;// The cumulative valued from equipment

	m_levelUp = 25;
}


Stat::~Stat()
{
}
