#pragma once
#include "SpriteFactory.h"

class Appearance
{
public:
	Appearance();
	~Appearance();
	void Draw(Uint8 _r, Uint8 _g, Uint8 _b, bool _flip = false);
	void Draw(SDL_Rect _pos, Uint8& _r, Uint8& _g, Uint8& _b, bool _flip = false) { m_pos = _pos; m_moveTo = _pos; Draw(_r, _g, _b, _flip); };
	void Update(float _time);

	void SetAnimation(int _animation) { m_animation = _animation; m_ani.y = 100 * _animation; m_frame = 0; }
	void SetOutfit(int _i, int _c = 0);
	void SetLegs(int _i, int _c = 0) { m_cLegsColour = _c; m_cLegs = _i; if (m_cLegs < 0) m_drawLegs = false; else m_drawLegs = true; }
	void MoveTo(SDL_Rect _moveTo) { m_moveTo = _moveTo; }
	void SetColour(int _c) { m_cBodyColour = _c;  m_cLegsColour = _c; }

	bool FinishMoving() { if (m_moveTo.x == m_pos.x && m_moveTo.y == m_pos.y) { return true; } else { return false; } }
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

