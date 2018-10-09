#include "ParallaxBg.h"



ParallaxBg::ParallaxBg(std::string _foreword, float _speed)
{
	m_foreword = _foreword;
	m_speed = _speed;
	m_parallaxPos = 0;
}


ParallaxBg::~ParallaxBg()
{
}

void ParallaxBg::Update(float& _deltaTime)
{
	m_parallaxPos += (m_speed * _deltaTime);
	if (m_parallaxPos >= 1800)
		m_parallaxPos = 0;
}

void ParallaxBg::Draw()
{
	SDL_Rect bkg = { 0,0,1600,900 };

	std::string draw = "assets/backgrounds/";
	draw += m_foreword;
	draw += "_background.png";
	SpriteFactory::Draw(draw, bkg);
	///
	draw = "assets/backgrounds/";
	draw += m_foreword;
	draw += "_parallax.png";
	bkg.x = m_parallaxPos;
	SpriteFactory::Draw(draw, bkg);
	bkg.x = -1800 + m_parallaxPos;
	SpriteFactory::Draw(draw, bkg);


	///
	bkg = { 0,0,1600,900 };
	draw = "assets/backgrounds/";
	draw += m_foreword;
	draw += "_foreground.png";
	SpriteFactory::Draw(draw, bkg);


	SpriteFactory::Draw("assets/backgrounds/card.png", bkg);
}