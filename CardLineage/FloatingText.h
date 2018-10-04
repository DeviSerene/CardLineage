#pragma once
#include "Text.h"
#include <memory>

class FloatingText
{
public:
	FloatingText(SDL_Renderer* _renderer, std::string _text, int _x, int _y, int _r, int _g, int _b);
	~FloatingText();

	bool Update(float& _deltaTime);
	void Draw();

private:
	std::shared_ptr<Text> m_textbox;
	std::string m_text;
	float m_x;
	float m_y;
	float m_a;
	float m_totalTime;
	SDL_Color m_colour;
	SDL_Renderer* m_renderer;
};

