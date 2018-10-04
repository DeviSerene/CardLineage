#pragma once
#include "Text.h"
#include <vector>
#include <memory>

class TextBox
{
public:
	TextBox(std::string& _text, SDL_Renderer* _renderer, SDL_Color _colour, SDL_Rect _position, int _textsize);
	~TextBox();
	void Draw();
	void Draw(SDL_Rect _pos);
private:
	std::vector <std::shared_ptr<Text>> m_text;
};

