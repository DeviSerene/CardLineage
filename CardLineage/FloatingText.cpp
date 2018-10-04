#include "FloatingText.h"

#define FINTIME 2.5f

FloatingText::FloatingText(SDL_Renderer* _renderer, std::string _text, int _x, int _y, int _r, int _g, int _b)
{
	m_totalTime = 0;
	m_x = _x;
	m_y = _y;
	m_text = _text;
	m_colour.r = (Uint8)_r;
	m_colour.g = (Uint8)_g;
	m_colour.b = (Uint8)_b;
	m_colour.a = (Uint8)255;
	m_a = 255.0f;
	m_renderer = _renderer;
	m_textbox = (std::shared_ptr<Text>)new Text(m_renderer, m_text, m_colour, 25, m_x, m_y);

}


FloatingText::~FloatingText()
{
	m_renderer = nullptr;
}

void FloatingText::Draw()
{
	m_textbox->DrawText();
}

bool FloatingText::Update(float& _deltaTime)
{
		m_totalTime += _deltaTime;
		if (m_totalTime <= FINTIME)
		{
			m_y -= ((100.0f / FINTIME) * _deltaTime);
			m_a -= ((255.0f / FINTIME) * _deltaTime);
			m_textbox->SetXY(m_x, m_y);
			m_textbox->SetAlpha(m_a);
			return false;
		}
		else
		{
			return true;
		}
}