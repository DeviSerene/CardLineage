#include "AniEffect.h"



AniEffect::AniEffect(int _animationID, float _aniStart, float _effectStart)
{
	m_aniID = _animationID;
	m_currentTime = 0;
	m_startTime = _aniStart;
	m_effectTime = _effectStart;
	m_performedEffect = false;
	m_startedAni = false;
}


AniEffect::~AniEffect()
{
}
