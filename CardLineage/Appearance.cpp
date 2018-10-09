#include "Appearance.h"



Appearance::Appearance()
{
	int rando = rand() % 3;
	m_race = 0;
	m_gender = 0;
	m_skin = 0;
	m_hair = 0;
	m_hairColour = 0;
	m_cBody = rando;
	m_cBodyColour = 0;
	m_cLegs = rando;
	m_cLegsColour = 0;

	m_drawLArm = true;
	m_drawRArm = true;
	m_drawBody = true; 
	m_drawLegs = true;

	m_pos.x = 0;
	m_pos.y = 0;
	m_pos.w = 200;
	m_pos.h = 200;
	m_moveTo = m_pos;

	m_animation = 0;
	m_frame = 0;
	m_currentTime = 0;
	m_ani.x = 0;
	m_ani.y = 0;
	m_ani.w = 100;
	m_ani.h = 100;
}


Appearance::~Appearance()
{
}


void Appearance::Draw(Uint8 _r, Uint8 _g, Uint8 _b, bool _flip)
{
	std::string draw;

	//BACKHAIR
	draw = "assets/" + std::to_string(m_race) + "_" + std::to_string(m_gender) + "/bhair_" + std::to_string(m_hair) + "_" + std::to_string(m_hairColour) + ".png";
	SpriteFactory::Draw(draw, m_pos, m_ani, _r, _g, _b, _flip);

	//BODY LAYER
	draw = "assets/" + std::to_string(m_race) + "_" + std::to_string(m_gender) + "/" + std::to_string(m_skin) + "_body.png";
	SpriteFactory::Draw(draw, m_pos, m_ani, _r, _g, _b, _flip);

	//LEG LAYER
	draw = "assets/" + std::to_string(m_race) + "_" + std::to_string(m_gender) + "/" + std::to_string(m_skin) + "_legs.png";
	SpriteFactory::Draw(draw, m_pos, m_ani, _r, _g, _b, _flip);
	if (m_drawLegs)
	{
		draw = "assets/" + std::to_string(m_race) + "_" + std::to_string(m_gender) + "/legs_" + std::to_string(m_cLegs) + "_" + std::to_string(m_cLegsColour) + ".png";
		SpriteFactory::Draw(draw, m_pos, m_ani, _r, _g, _b, _flip);
	}

	if (m_drawBody)
	{
		draw = "assets/" + std::to_string(m_race) + "_" + std::to_string(m_gender) + "/body_" + std::to_string(m_cBody) + "_" + std::to_string(m_cBodyColour) + ".png";
		SpriteFactory::Draw(draw, m_pos, m_ani, _r, _g, _b, _flip);
	}



	//HEAD
	draw = "assets/" + std::to_string(m_race) + "_" + std::to_string(m_gender) + "/" + std::to_string(m_skin) + "_head.png";
	SpriteFactory::Draw(draw, m_pos, m_ani, _r, _g, _b, _flip);

	draw = "assets/" + std::to_string(m_race) + "_" + std::to_string(m_gender) + "/fhair_" + std::to_string(m_hair) + "_" + std::to_string(m_hairColour) + ".png";
	SpriteFactory::Draw(draw, m_pos, m_ani, _r, _g, _b, _flip);

	//LEFT ARM
	draw = "assets/" + std::to_string(m_race) + "_" + std::to_string(m_gender) + "/" + std::to_string(m_skin) + "_larm.png";
	SpriteFactory::Draw(draw, m_pos, m_ani, _r, _g, _b, _flip);
	if (m_drawLArm)
	{
		draw = "assets/" + std::to_string(m_race) + "_" + std::to_string(m_gender) + "/larm_" + std::to_string(m_cBody) + "_" + std::to_string(m_cBodyColour) + ".png";
		SpriteFactory::Draw(draw, m_pos, m_ani, _r, _g, _b, _flip);
	}
	//RIGHT ARM
	draw = "assets/" + std::to_string(m_race) + "_" + std::to_string(m_gender) + "/" + std::to_string(m_skin) + "_rarm.png";
	SpriteFactory::Draw(draw, m_pos, m_ani, _r, _g, _b, _flip);
	if (m_drawRArm)
	{
		draw = "assets/" + std::to_string(m_race) + "_" + std::to_string(m_gender) + "/rarm_" + std::to_string(m_cBody) + "_" + std::to_string(m_cBodyColour) + ".png";
		SpriteFactory::Draw(draw, m_pos, m_ani, _r, _g, _b, _flip);
	}


}

void Appearance::Update(float _time)
{
	m_currentTime += _time;
	while (m_currentTime >= 0.25f)
	{
		m_frame += 1;
		if (m_frame >= 4)
		{
			m_frame = 0;
			if (m_animation == 1)
				m_animation = 0;
		}
		m_ani.x = m_frame * 100;
		m_ani.y = m_animation * 100;
		m_currentTime -= 0.25f;
	}

	if (m_moveTo.x < m_pos.x)
	{
		m_pos.x -= 1;
	}
	else if (m_moveTo.x > m_pos.x)
	{
		m_pos.x += 1;
	}
	if (m_moveTo.y < m_pos.y)
	{
		m_pos.y -= 1;
	}
	else if (m_moveTo.y > m_pos.y)
	{
		m_pos.y += 1;
	}

}


void Appearance::SetOutfit(int _i, int _c)
{
	m_cBody = _i;
	m_cBodyColour = _c;

	switch (m_cBody)
	{
	case 0:
		m_drawBody = true;
		m_drawLArm = false;
		m_drawRArm = false;
		break;
	case 1:
		m_drawBody = true;
		m_drawLArm = false;
		m_drawRArm = false;
		break;
	default:
		m_drawBody = false;
		m_drawLArm = false;
		m_drawRArm = false;
		break;
	}
}
