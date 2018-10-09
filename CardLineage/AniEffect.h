#pragma once
#include <vector>
#include <string>
#include <memory>

class AniEffect
{
public:
	AniEffect( int _animationID, float _aniStart, float _effectStart);
	~AniEffect();

	void Update(float& _deltaTime) { m_currentTime += _deltaTime; };
	void Reset() { m_currentTime = 0;m_performedEffect = false;m_startedAni = false;}

	int GetAnimationID() { return m_aniID; }
	bool StartedAni() { return m_startedAni; }
	bool StartedEffect() { return m_performedEffect; }
	bool StartAnimation() { if (m_currentTime >= m_startTime) { m_startedAni = true; } return m_startedAni; }
	bool StartEffect() { if (m_currentTime >= m_effectTime) { m_performedEffect = true; } return m_performedEffect;}

private:
	float m_currentTime; //the total time this animation has been playing
	float m_startTime; //when the animation should start
	float m_effectTime; //when the effect of the card should start

	int m_userAni; //what animation the user should play

	int m_aniID; //the name of the animation to play
	std::string m_sound; //te name of the sound to play
	bool m_performedEffect;
	bool m_startedAni;
};

