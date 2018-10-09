#pragma once
#include "SpriteFactory.h"


class ParallaxBg
{
public:
	ParallaxBg(std::string _foreword, float _speed);
	~ParallaxBg();

	void Update(float& _deltaTime);
	void Draw();

private:
	std::string m_foreword;
	float m_parallaxPos;
	float m_speed;
};

