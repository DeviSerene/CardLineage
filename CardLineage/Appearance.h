#pragma once
#include "SpriteFactory.h"

class Appearance
{
public:
	Appearance();
	~Appearance();
	void Draw(Uint8 _r, Uint8 _g, Uint8 _b);
	void Draw(SDL_Rect _pos, Uint8& _r, Uint8& _g, Uint8& _b) { m_pos = _pos; m_moveTo = _pos; Draw(_r, _g, _b); };
	void Update(float _time);

	void SetAnimation(int _animation) { m_animation = _animation; m_ani.y = 100 * _animation;}
	void SetOutfit(int _i, int _c = 0);
	void SetLegs(int _i, int _c = 0) { m_cLegsColour = _c; m_cLegs = _i; if (m_cLegs < 0) m_drawLegs = false; else m_drawLegs = true; }
	void MoveTo(SDL_Rect _moveTo) { m_moveTo = _moveTo; }

	SDL_Rect GetPos() { return m_pos; }

private:
	int m_race, m_gender, m_skin, m_hair, m_hairColour, m_cBody, m_cBodyColour, m_cLegs, m_cLegsColour;
	int m_animation, m_frame;
	SDL_Rect m_pos;
	SDL_Rect m_moveTo;
	SDL_Rect m_ani;
	float m_currentTime;

	bool m_drawLArm, m_drawRArm, m_drawBody, m_drawLegs;

};

