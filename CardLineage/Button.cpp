#include "Button.h"


Button::Button()
{
}

Button::Button(std::string _image, SDL_Rect _pos, bool _visible)
{
	m_image = _image;
	m_position = _pos;
	m_visible = _visible;
}

Button::~Button()
{
}

void Button::Draw()
{
	if(m_visible)
		SpriteFactory::Draw(m_image, m_position);
}

bool Button::MouseRect(int _x, int _y)
{
	if (m_visible)
	{
		if (_x >= m_position.x && _x <= (m_position.x + m_position.w) && _y >= m_position.y && _y <= (m_position.y + m_position.h))
		{
//			m_function();
			return true;
		}
	}
	return false;
}